#include "base/linearfilter.h"
#include <opencv2/imgproc.hpp>

LinearFilter::LinearFilter(cv::Mat&& src) :
    source(std::forward<cv::Mat>(src))
{
}

void LinearFilter::run()
{
    cv::Mat kernel = cv::Mat::ones(kernel_size, kernel_size, CV_32F)
            / static_cast<double>(kernel_size * kernel_size);
    cv::filter2D(source, result, -1, kernel, anchor, delta, cv::BORDER_DEFAULT);
    ok = !result.empty();
}

bool LinearFilter::precheck_kernel_size(int8_t k) noexcept
{
    bool result = k > 0;
    for (auto j = 1; j <= 127; ++j) {
        if (k == j) {
            result = true;
            break;
        }
    }
    return result;
}
