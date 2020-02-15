#include "base/drawcontours.h"
#include <opencv2/imgproc.hpp>

static constexpr float AVOID_DIVISION_BY_ZERO = 1e-5;
static const cv::Scalar CONTOURS_COLOR(255, 255, 255);
static constexpr int THICKNESS = 2;

DrawContours::DrawContours(cv::Mat &&src) : Operation(std::forward<cv::Mat>(src))
{}

void DrawContours::run()
{
	cv::Mat copy;
	cv::cvtColor(source, copy, cv::COLOR_BGR2GRAY);
	cv::blur(copy, copy, cv::Size(kernel_size, kernel_size));

	cv::Mat cannyOut;
	cv::Canny(copy, cannyOut, current_threshold_value, max_threshold_value);

	std::vector<std::vector<cv::Point>> foundContours;
	cv::findContours(cannyOut, foundContours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

	std::vector<cv::Point2f> points(foundContours.size());
	for(size_t i = 0; i < points.size(); ++i) {
		cv::Moments m = cv::moments(foundContours[i]);
		points[i] = cv::Point2f(static_cast<float>(m.m10 / (m.m00 + AVOID_DIVISION_BY_ZERO)),
														static_cast<float>(m.m01 / (m.m00 + AVOID_DIVISION_BY_ZERO)));
	}

	result = cv::Mat::zeros(cannyOut.size(), CV_8UC3);
	for(size_t i = 0; i < foundContours.size(); ++i) {
		cv::drawContours(
				result, foundContours, static_cast<int>(i), CONTOURS_COLOR, THICKNESS);
	}
}
