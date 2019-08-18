#include "base/detectbrigthedge.h"
#include <opencv2/imgproc.hpp>

DetectBrigthEdge::DetectBrigthEdge(cv::Mat&& src) : Operation(std::forward<cv::Mat>(src))
{}

void DetectBrigthEdge::run()
{
	cv::GaussianBlur(source, source, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);

	cv::Mat copy, Gx, Gy;
	cv::cvtColor(source, copy, cv::COLOR_BGR2GRAY);

	cv::Sobel(copy, Gx, CV_16S, 1, 0, kernel_size, scale, delta, cv::BORDER_DEFAULT);
	cv::Sobel(copy, Gy, CV_16S, 0, 1, kernel_size, scale, delta, cv::BORDER_DEFAULT);

	cv::convertScaleAbs(Gx, Gx);
	cv::convertScaleAbs(Gy, Gy);

	result = Gx * alpha + Gy * alpha;
	ok = !result.empty();
}
