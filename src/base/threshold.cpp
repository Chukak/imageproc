#include "base/threshold.h"
#include "settings/cmdoptions.h"
#include <opencv2/imgproc.hpp>

DECL_OT_PARAMS(
    Threshold,
    CTOR_OPTIONS({command_line::options::threshold_opt::THRESHOLD_TYPE_VALUES[0],
                  command_line::options::threshold_opt::THRESHOLD_TYPE_VALUES[1],
                  command_line::options::threshold_opt::THRESHOLD_TYPE_VALUES[2],
                  command_line::options::threshold_opt::THRESHOLD_TYPE_VALUES[3],
                  command_line::options::threshold_opt::THRESHOLD_TYPE_VALUES[4]}),
    CTOR_TYPES({THRESHOLD_BINARY,
                THRESHOLD_BINARY_INVERTED,
                THRESHOLD_TRUNCATED,
                THRESHOLD_TO_ZERO,
                THRESHOLD_TO_ZERO_INVERTED}),
    CTOR_TYPE(THRESHOLD_BINARY));

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

	cv::threshold(copy,
								result,
								current_threshold_value,
								max_threshold_value,
								static_cast<THRESHOLD_TYPE>(type));
	ok = !result.empty();
}
