#include "functions/default.h"
#include <opencv2/core.hpp>

namespace functions
{
void fft_shift(const cv::Mat& input, cv::Mat& output)
{
	output = input.clone();
	int32_t cx = output.cols / 2;
	int32_t cy = output.rows / 2;

	cv::Mat q0, q1, q2, q3, tmp;
	q0 = cv::Mat(output, cv::Rect(0, 0, cx, cy));
	q1 = cv::Mat(output, cv::Rect(cx, 0, cx, cy));
	q2 = cv::Mat(output, cv::Rect(0, cy, cx, cy));
	q3 = cv::Mat(output, cv::Rect(cx, cy, cx, cy));
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}
} // namespace functions
