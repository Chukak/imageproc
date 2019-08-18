#ifndef ANCHORPOINT_H
#define ANCHORPOINT_H

#include <opencv2/core/types.hpp>

class AnchorPoint
{
public:
	void ap_set(int64_t x, int64_t y) noexcept;
	void ap_set(cv::Point&& anch) noexcept;
	void ap_set(const cv::Point& anch) noexcept;

protected:
	explicit AnchorPoint() = default;
	explicit AnchorPoint(int64_t x, int64_t y);

protected:
	cv::Point anchor{-1, -1};
};

#endif // ANCHORPOINT_H
