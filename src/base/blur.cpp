#include "base/blur.h"
#include "settings/cmdoptions.h"
#include <map>
#include <string>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace command_line;

// check cmdoptions;
static std::map<string, BLUR_TYPE> OPTIONS_VALUE = {
    {string{options::blur_opt::BLUR_TYPE_VALUES[0]}, BLUR_GAUSSIAN},
    {string{options::blur_opt::BLUR_TYPE_VALUES[1]}, BLUR_MEDIAN},
    {string{options::blur_opt::BLUR_TYPE_VALUES[2]}, BLUR_BILATERAL},
};

// todo
Blur::Blur(BLUR_TYPE t, cv::Mat&& src) :
    type(t),
    source(std::forward<cv::Mat>(src))
{
}

void Blur::run()
{
    for (auto i = 1; i < max_kernel_length; i += 2) {
        switch (type)
        {
        case BLUR_ORIGINAL:
            cv::blur(source, result, cv::Size(i, i), anchor, 0);
            break;
        case BLUR_GAUSSIAN:
            cv::GaussianBlur(source, result, cv::Size(i, i), 0, 0, 0);
            break;
        case BLUR_MEDIAN:
            cv::medianBlur(source, result, i);
            break;
        case BLUR_BILATERAL:
            // todo
            cv::bilateralFilter(source, result, i, i * 2, (i * 1.0) / 2);
            break;
        }
        ok = !result.empty();
    }
}

BLUR_TYPE Blur::parse_type(const char* flag) noexcept
{
    if (OPTIONS_VALUE.count(flag)) {
        return OPTIONS_VALUE[flag];
    }
    return BLUR_ORIGINAL;
}
