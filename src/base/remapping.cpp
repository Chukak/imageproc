#include "base/remapping.h"
#include "settings/cmdoptions.h"
#include <map>
#include <string>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace command_line;

// check cmdoptions
static std::map<string, REMAPPING_TYPE> OPTIONS_VALUE = {
    {string{options::remapping_opt::REMAPPING_TYPE_VALUES[0]}, REMAPPING_UPSIDE_DOWN},
    {string{options::remapping_opt::REMAPPING_TYPE_VALUES[1]}, REMAPPING_X_DIRECTION},
    {string{options::remapping_opt::REMAPPING_TYPE_VALUES[2]}, REMAPPING_BOTH_DIRECTION},
};

Remapping::Remapping(REMAPPING_TYPE t, cv::Mat&& src) :
    type(t),
    source(std::forward<cv::Mat>(src))
{
}

void Remapping::run()
{
    cv::Mat mapX(source.size(), CV_32FC1), mapY(source.size(), CV_32FC1);
    for (auto row = 0; row < mapX.rows; ++row) {
        for (auto col = 0; col < mapX.cols; ++col) {
            switch (type)
            {
            case REMAPPING_UPSIDE_DOWN:
                mapX.at<float>(row, col) = static_cast<float>(col);
                mapY.at<float>(row, col) = static_cast<float>(mapY.rows - row);
                break;
            case REMAPPING_X_DIRECTION:
                mapX.at<float>(row, col) = static_cast<float>(mapX.cols - col);
                mapY.at<float>(row, col) = static_cast<float>(row);
                break;
            case REMAPPING_BOTH_DIRECTION:
                mapX.at<float>(row, col) = static_cast<float>(mapY.cols - col);
                mapY.at<float>(row, col) = static_cast<float>(mapX.rows - row);
                break;
            }
        }
    }
    cv::remap(source, result, mapX, mapY, cv::INTER_LINEAR);
    ok = !result.empty();
}

REMAPPING_TYPE Remapping::parse_type(const char *flag) noexcept
{
    return OPTIONS_VALUE.count(flag) ? OPTIONS_VALUE[flag] : REMAPPING_UPSIDE_DOWN;
}
