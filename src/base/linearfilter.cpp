#include "base/linearfilter.h"
#include <opencv2/imgproc.hpp>

LinearFilter::LinearFilter(cv::Mat &&src) : Operation(std::forward<cv::Mat>(src))
{}

void LinearFilter::run()
{
	cv::Mat kernel = cv::Mat::ones(kernel_size, kernel_size, CV_32F) /
									 static_cast<double>(kernel_size * kernel_size);
	cv::filter2D(source, result, -1, kernel, anchor, delta, cv::BORDER_DEFAULT);
	ok = !result.empty();
}

void LinearFilter::set_delta(int d) noexcept
{
	delta = d;
}
