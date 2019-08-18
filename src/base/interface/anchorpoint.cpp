#include "base/interface/anchorpoint.h"

AnchorPoint::AnchorPoint(int64_t x, int64_t y) : anchor(x, y)
{}

void AnchorPoint::ap_set(int64_t x, int64_t y) noexcept
{
	anchor = cv::Point(x, y);
}

void AnchorPoint::ap_set(cv::Point &&anch) noexcept
{
	anchor = std::forward<cv::Point>(anch);
}

void AnchorPoint::ap_set(const cv::Point &anch) noexcept
{
	anchor = anch;
}
