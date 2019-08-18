#include "base/threshold.h"
#include "settings/cmdoptions.h"
#include <opencv2/imgproc.hpp>

OperationType::options_t Threshold::options = {
    command_line::options::threshold_opt::THRESHOLD_TYPE_VALUES[0],
    command_line::options::threshold_opt::THRESHOLD_TYPE_VALUES[1],
    command_line::options::threshold_opt::THRESHOLD_TYPE_VALUES[2],
    command_line::options::threshold_opt::THRESHOLD_TYPE_VALUES[3],
    command_line::options::threshold_opt::THRESHOLD_TYPE_VALUES[4]};

OperationType::types_t Threshold::types = {THRESHOLD_BINARY,
                                           THRESHOLD_BINARY_INVERTED,
                                           THRESHOLD_TRUNCATED,
                                           THRESHOLD_TO_ZERO,
                                           THRESHOLD_TO_ZERO_INVERTED};

OperationType::type_t Threshold::default_type = THRESHOLD_BINARY;

Threshold::Threshold(COMMON_CLASS_TYPE t, cv::Mat &&src, bool gray) :
    Operation(std::forward<cv::Mat>(src)), OperationType(t), is_gray(gray)
{}

void Threshold::run()
{
	cv::Mat copy;
	if(is_gray) {
		cv::cvtColor(source, copy, cv::COLOR_BGR2GRAY);
	} else {
		source.copyTo(copy);
	}

	cv::threshold(
	    copy, result, value, max_threshold_value, static_cast<THRESHOLD_TYPE>(type));
	ok = !result.empty();
}

void Threshold::set_value(int v) noexcept
{
	value = v;
}

bool Threshold::check_value(int16_t v) noexcept
{
	return v > -1 && v <= max_threshold_value;
}
