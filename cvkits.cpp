#include "cvkits.h"
#include <QDebug>
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
