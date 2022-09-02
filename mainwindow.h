#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cvkits.h"

#include <QMainWindow>
#include <QLabel>
#include <QMediaPlayer>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openReceiveDialog();
    void setPreviewImage(QString);
    void clearPreviewImage(QLabel *);
    void initMoviePlayer();

public slots:
    void pickImage();
    void pickMovie();

    void detectImage();
    void detectMovie();

    void denoiseClicked();
    void enhanceClicked();
    void cropClicked();
private:
    QString processImage(QString path, void (*func)(cv::Mat, cv::Mat&));

    QMediaPlayer *m_player = nullptr;
    QVideoWidget *m_videoWidget = nullptr;
    Ui::MainWindow *ui;

    void hidePlayer(QLabel *, QWidget *);
    void showPlayer(QLabel *, QWidget *);

    QString currentPreviewImagePath = "";
    QString currentImagePath = "";
    QString currentMoviePath = "";
};
#endif // MAINWINDOW_H
