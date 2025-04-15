#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <QString>

class ImageProcessor
{
public:
    static cv::Mat applyBrightnessContrast(cv::Mat image, double alpha, int beta);
    static cv::Mat applyGaussianBlur(cv::Mat image, int kernelSize);
    static cv::Mat applyThreshold(cv::Mat image, double threshValue);
    static cv::Mat addGaussianNoise(cv::Mat image, double stddev);
    static cv::Mat loadImage(const QString& path);
    static bool saveImage(const cv::Mat& image, const QString& path);
};

#endif // IMAGEPROCESSOR_H
