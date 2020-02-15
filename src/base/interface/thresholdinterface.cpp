#include "base/interface/thresholdinterface.h"

void ThresholdInterface::thr_set_value(int v) noexcept
{
	current_threshold_value = v;
}

bool ThresholdInterface::thr_check_value(int16_t v) noexcept
{
	return v > -1 && v <= max_threshold_value;
}
