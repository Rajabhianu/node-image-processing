#include "imageprocessor.h"

cv::Mat ImageProcessor::applyBrightnessContrast(cv::Mat image, double alpha, int beta) {
    cv::Mat result;
    image.convertTo(result, -1, alpha, beta);
    return result;
}

cv::Mat ImageProcessor::applyGaussianBlur(cv::Mat image, int kernelSize) {
    if (kernelSize <= 0 || kernelSize % 2 == 0)
        return image.clone();
    cv::Mat result;
    cv::GaussianBlur(image, result, cv::Size(kernelSize, kernelSize), 0);
    return result;
}

cv::Mat ImageProcessor::applyThreshold(cv::Mat image, double threshValue) {
    cv::Mat gray, binary;
    if (image.channels() == 3)
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    else
        gray = image.clone();
    cv::threshold(gray, binary, threshValue, 255, cv::THRESH_BINARY);
    return binary;
}

cv::Mat ImageProcessor::addGaussianNoise(cv::Mat image, double stddev) {
    if (stddev <= 0.0) return image.clone();

    cv::Mat noise(image.size(), image.type());
    cv::RNG rng(cv::getTickCount());

    rng.fill(noise, cv::RNG::NORMAL, 0, stddev);

    cv::Mat result;
    cv::add(image, noise, result, cv::noArray(), image.type());
    return result;
}

cv::Mat ImageProcessor::loadImage(const QString& path) {
    cv::Mat image = cv::imread(path.toStdString(), cv::IMREAD_COLOR);
    if (image.empty()) {
        return cv::Mat();
    }
    return image;
}

bool ImageProcessor::saveImage(const cv::Mat& image, const QString& path) {
    return cv::imwrite(path.toStdString(), image);
}
