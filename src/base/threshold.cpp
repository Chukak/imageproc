#include "base/threshold.h"
#include "settings/cmdoptions.h"
#include <map>
#include <string>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace command_line;

// check cmdoptions;
static std::map<string, THRESHOLD_TYPE> OPTIONS_VALUE = {
    {string{options::threshold_opt::THRESHOLD_TYPE_VALUES[0]}, THRESHOLD_BINARY},
    {string{options::threshold_opt::THRESHOLD_TYPE_VALUES[1]}, THRESHOLD_BINARY_INVERTED},
    {string{options::threshold_opt::THRESHOLD_TYPE_VALUES[2]}, THRESHOLD_TRUNCATED},
    {string{options::threshold_opt::THRESHOLD_TYPE_VALUES[3]}, THRESHOLD_TO_ZERO},
    {string{options::threshold_opt::THRESHOLD_TYPE_VALUES[4]}, THRESHOLD_TO_ZERO_INVERTED},
};

const int16_t& Threshold::max_threshold_value{255};

Threshold::Threshold(THRESHOLD_TYPE t, cv::Mat&& src, int16_t v, bool gray) :
    type(t),
    is_gray(gray),
    source(std::forward<cv::Mat>(src)),
    value(v)
{
}

void Threshold::run()
{
    cv::Mat copy;
    if (is_gray) {
        cv::cvtColor(source, copy, cv::COLOR_BGR2GRAY);
    } else {
        source.copyTo(copy);
    }

    cv::threshold(copy, result, value, max_threshold_value, type);
    ok = !result.empty();
}

THRESHOLD_TYPE Threshold::parse_type(const char *flag) noexcept
{
    if (OPTIONS_VALUE.count(flag)) {
        return OPTIONS_VALUE[flag];
    }
    return THRESHOLD_BINARY;
}

bool Threshold::precheck_value(int16_t v) noexcept
{
    return v > -1 && v <= max_threshold_value;
}
