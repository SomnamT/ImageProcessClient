#include "cvkits.h"
#include "cutimage.h"
#include "qdialog.h"
#include "qdir.h"
#include "qfileinfo.h"
#include "qpixmap.h"
#include <QDebug>
#include <QUuid>
#include <QString>
CVKits::CVKits()
{

}

void CVKits::testOpenCV() {
    using namespace cv;
    Mat image = imread("C:/Users/26286/Desktop/ImageProcess/ipc_5_9/image-processing-client/test.png", IMREAD_UNCHANGED);
    namedWindow("CVKits::testOpenCV Window", WINDOW_AUTOSIZE);
    imshow("CVKits::testOpenCV Window", image);
}

void CVKits::denoise(cv::Mat src, cv::Mat &dst) {
    using namespace cv;
    //Mat image1 = src;
    dst = src;
    //fastNlMeansDenoising(src, dst);

}

void CVKits::enhance(cv::Mat src, cv::Mat &dst) {
    using namespace cv;
    Mat chan[256];
    split(src, chan);
    for (int i = 0; i < 3; ++i) {
        equalizeHist(chan[i], chan[i]);
    }
    merge(chan, 3, dst);
}

void CVKits::crop(cv::Mat src, cv::Mat &dst) {
    using namespace cv;
    QString str = "C:\\Users\\26286\\Desktop\\ImageProcess\\testImageProcess\\tmp\\" + QUuid::createUuid().toString() + ".tmp.png";
    cv::String tmpDir = str.toStdString();
    cv::imwrite(tmpDir, src);
    CutImage dialog{str};
    QFileInfo fileinfo{str};

    if ( dialog.exec() == QDialog::Accepted ) {
        QPixmap cropImage = dialog.getCropImage();

        QString filename = fileinfo.baseName();
        QString new_filename = filename + "_croped." + fileinfo.completeSuffix();

        QString dir = "C:\\Users\\26286\\Desktop\\ImageProcess\\testImageProcess\\tmp";
        QFileInfo new_file {dir, new_filename};

        qDebug() << new_file.absoluteFilePath();
        cropImage.save(new_file.absoluteFilePath());
        dst = cv::imread(new_file.absoluteFilePath().toStdString());
    }
    else dst = src;
}
