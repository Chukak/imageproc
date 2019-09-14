#include "../../include/base/histogramequalization.h"
#include <opencv2/imgproc.hpp>
#include <iostream>
HistogramEqualization::HistogramEqualization(cv::Mat&& src) :
		Operation(std::forward<cv::Mat>(src))
{}

void HistogramEqualization::run()
{
	cv::Mat copy;
	cv::cvtColor(source, copy, cv::COLOR_BGR2GRAY);
	cv::equalizeHist(copy, result);
	ok = !result.empty();
}
