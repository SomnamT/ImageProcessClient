#ifndef CVKITS_H
#define CVKITS_H

#include "opencv2/opencv.hpp"

class CVKits
{
public:
    CVKits();

    static void testOpenCV();
    static void denoise(cv::Mat src, cv::Mat &dst);
    static void enhance(cv::Mat src, cv::Mat &dst);
};

#endif // CVKITS_H
