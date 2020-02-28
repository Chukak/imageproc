#include "base/blur.h"
#include "settings/cmdoptions.h"
#include <opencv2/imgproc.hpp>

DECL_OT_PARAMS(Blur,
               CTOR_OPTIONS({command_line::options::blur_opt::BLUR_TYPE_VALUES[0],
                             command_line::options::blur_opt::BLUR_TYPE_VALUES[1],
                             command_line::options::blur_opt::BLUR_TYPE_VALUES[2]}),
               CTOR_TYPES({BLUR_GAUSSIAN, BLUR_MEDIAN, BLUR_BILATERAL}),
               CTOR_TYPE(BLUR_ORIGINAL));

Blur::Blur(COMMON_CLASS_TYPE t, cv::Mat&& src) :
    Operation(std::forward<cv::Mat>(src)), KernelSize(27), OperationType(t)
{}

void Blur::run()
{
	switch(static_cast<BLUR_TYPE>(type)) {
	case BLUR_ORIGINAL:
		cv::blur(source, result, cv::Size(kernel_size, kernel_size), anchor, 0);
		break;
	case BLUR_GAUSSIAN:
		cv::GaussianBlur(source, result, cv::Size(kernel_size, kernel_size), 0, 0, 0);
		break;
	case BLUR_MEDIAN:
		cv::medianBlur(source, result, kernel_size);
		break;
	case BLUR_BILATERAL:
		// todo
		cv::bilateralFilter(
		    source, result, kernel_size, kernel_size * 2, (kernel_size * 1.0) / 2);
		break;
	}
	ok = !result.empty();
}
