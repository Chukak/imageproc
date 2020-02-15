#ifndef THRESHOLDINTERFACE_H
#define THRESHOLDINTERFACE_H

#include <cstdint>

class ThresholdInterface
{
public:
	explicit ThresholdInterface() = default;
	void thr_set_value(int v) noexcept;
	static bool thr_check_value(int16_t v) noexcept;

protected:
	static const int16_t max_threshold_value{255};
	int16_t current_threshold_value{static_cast<int16_t>(max_threshold_value / 2)};
};

#endif // THRESHOLD_H
