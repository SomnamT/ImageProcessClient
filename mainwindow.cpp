#include <QFileDialog>
#include <QMessageBox>
#include <QAudioOutput>
#include <QDebug>
#include <QUuid>

#include "config.h"
#include "core/mat.hpp"
#include "mainwindow.h"
#include "tempmanager.h"
#include "ui_mainwindow.h"
#include "receivedialog.h"
#include "ucsbengine/clientservicemanager.h"
#include "ucsbengine/clientservicemanagerfactory.h"
#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->receiveImageButton, SIGNAL(clicked()), this, SLOT(pickImage()));
    connect(ui->receiveMovieButton, SIGNAL(clicked()), this, SLOT(pickMovie()));

    connect(ui->imageTargetDetectButton, SIGNAL(clicked()), this, SLOT(detectImage()));
    connect(ui->traceTargetButton, SIGNAL(clicked()), this, SLOT(detectMovie()));

    connect(ui->imageDenoiseButton, SIGNAL(clicked()), this, SLOT(denoiseClicked()));
    connect(ui->imageEnhanceButton, SIGNAL(clicked()), this, SLOT(enhanceClicked()));

    openReceiveDialog();

    setPreviewImage("C:/Users/26286/Desktop/ImageProcess/ipc_5_9/image-processing-client/test.png");
    hidePlayer(ui->noImagePrompt, ui->imageField);

    // is opencv working?
    CVKits::testOpenCV();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hidePlayer(QLabel *label, QWidget *widget) {
    label->show();
    widget->hide();
}

void MainWindow::showPlayer(QLabel *label, QWidget *widget) {
    label->hide();
    widget->show();
}

void MainWindow::initMoviePlayer() {
    m_player = new QMediaPlayer;
    m_videoWidget = new QVideoWidget;
    m_videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->movieDisplay->addWidget(m_videoWidget);
    hidePlayer(ui->noMoviePrompt, m_videoWidget);
    m_player->setVideoOutput(m_videoWidget);
//    m_player->setAudioOutput(new QAudioOutput());
}

QString MainWindow::processImage(QString path, void (*func)(cv::Mat, cv::Mat&)) {
    cv::Mat src = cv::imread(path.toStdString());
    cv::Mat dst;

    func(src, dst);


    QString output_file = TempManager::get_cv_tempfile();
    QString str("SJTU");
    qDebug() << str;
    qDebug() << output_file;
    //cv::imshow(, dst);
    cv::imwrite(output_file.toStdString(), dst);

    //Deleted for win platform
    return output_file;
}

void MainWindow::pickImage() {
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("选择目标图片文件"),
        "",
        tr("支持的图片格式 (*.png *.jpg *.jpeg *.gif);;All files(*.*)"));
    if (fileName.isEmpty()) {
        hidePlayer(ui->noImagePrompt, ui->imageField);
    }
    else {
        QImage image(fileName);
        ui->imageField->setPixmap(QPixmap::fromImage(image));
        ui->imageField->setScaledContents( true );
        showPlayer(ui->noImagePrompt, ui->imageField);
        currentImagePath = fileName;
    }
}

void MainWindow::pickMovie() {
    if (m_player == nullptr || m_videoWidget == nullptr) {
        initMoviePlayer();
    }
    \
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("选择目标视频文件"),
        "",
        tr("支持的视频格式 (*.mp4 *.avi *.wmv);;All files(*.*)"));
    if (fileName.isEmpty()) {
        hidePlayer(ui->noMoviePrompt, m_videoWidget);
    }
    else {
        QUrl url = QUrl::fromLocalFile(fileName);
        m_player->setMedia(url);
//        m_player->setLoops(QMediaPlayer::Infinite);
        showPlayer(ui->noMoviePrompt, m_videoWidget);
        m_player->play();
        currentMoviePath = fileName;
    }
}

void MainWindow::openReceiveDialog() {
    ReceiveDialog *dialog = new ReceiveDialog;
    dialog->setModal(true);
    dialog->show();
}

void MainWindow::setPreviewImage(QString path) {
    QLabel *field = this->ui->receiveImageField;
    try {
        QImage image(path);
        field->setPixmap(QPixmap::fromImage(image));
        field->setScaledContents( true );
        field->setText("");
        currentPreviewImagePath = path;
    } catch (std::exception) {
        clearPreviewImage(field);
    }
}

void MainWindow::clearPreviewImage(QLabel *field) {
    field->setPixmap(QPixmap());
    field->setText("无图像");
}

void MainWindow::detectImage() {
    if (currentImagePath.isEmpty()) {
        QMessageBox::warning(this, "无图片", "没有可以识别的图片。");
        return;
    }
    try {
        ClientServiceManager *manager = ClientServiceManagerFactory::GetInstance()->CreateClientServiceManager();
        QString output = manager->CallService(Config::imageDetectionService.appId, Config::imageDetectionService.serviceId, currentImagePath, TempManager::get_response_tempfile());
        qDebug() << "output is: " << output;
        if (output.isEmpty()) {
            throw std::runtime_error("empty response");
        }
        ui->imageField->setPixmap(QPixmap(output));
        showPlayer(ui->noImagePrompt, ui->imageField);
    } catch (std::exception &e) {
        QMessageBox::critical(this, "失败", QString("无法识别这张图片。\n%1: %2").arg(typeid(e).name(),e.what()));
    }
}

void MainWindow::detectMovie() {
    if (currentMoviePath.isEmpty()) {
        QMessageBox::warning(this, "无影片", "没有可以识别的影片。");
        return;
    }
    try {
        ClientServiceManager *manager = ClientServiceManagerFactory::GetInstance()->CreateClientServiceManager();
        QString output = manager->CallService(Config::movieDetectionService.appId, Config::movieDetectionService.serviceId, currentImagePath, TempManager::get_response_tempfile());
        qDebug() << "output is: " << output;
            throw std::runtime_error("empty response");
        if (output.isEmpty()) {
        }
        QUrl url = QUrl::fromLocalFile(output);
        m_player->setMedia(url);
//        m_player->setLoops(QMediaPlayer::Infinite);
        showPlayer(ui->noMoviePrompt, m_videoWidget);
        m_player->play();
    } catch (std::exception &e) {
        QMessageBox::critical(this, "失败", QString("无法识别这段影片。\n%1: %2").arg(typeid(e).name(),e.what()));
    }
}

void MainWindow::denoiseClicked() {
    if (currentPreviewImagePath.isEmpty()) {
        QMessageBox::warning(this, "无图片", "没有可以去噪的图片。");
        return;
    }
    QString output = processImage(currentPreviewImagePath, &CVKits::denoise);
    setPreviewImage(output);
}

void MainWindow::enhanceClicked() {
    if (currentPreviewImagePath.isEmpty()) {
        QMessageBox::warning(this, "无图片", "没有可以增强的图片。");
        return;
    }
    QString output = processImage(currentPreviewImagePath, &CVKits::enhance);
    setPreviewImage(output);
}

