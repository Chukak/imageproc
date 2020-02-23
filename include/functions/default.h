#ifndef FUNCTIONS_DEFAULT_H
#define FUNCTIONS_DEFAULT_H

#include <opencv2/core/mat.hpp>

namespace functions
{
void fft_shift(const cv::Mat& input, cv::Mat& output);
};

#endif // FUNCTIONS_DEFAULT_H
