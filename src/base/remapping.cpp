#include "base/remapping.h"
#include "settings/cmdoptions.h"
#include <opencv2/imgproc.hpp>

OperationType::options_t Remapping::options = {
    command_line::options::remapping_opt::REMAPPING_TYPE_VALUES[0],
    command_line::options::remapping_opt::REMAPPING_TYPE_VALUES[1],
    command_line::options::remapping_opt::REMAPPING_TYPE_VALUES[2]
};

OperationType::types_t Remapping::types = {
    REMAPPING_UPSIDE_DOWN,
    REMAPPING_X_DIRECTION,
    REMAPPING_BOTH_DIRECTION
};

OperationType::type_t Remapping::default_type = REMAPPING_UPSIDE_DOWN;

Remapping::Remapping(COMMON_CLASS_TYPE t, cv::Mat&& src) :
    Operation(std::forward<cv::Mat>(src)),
    OperationType(t)
{
}

void Remapping::run()
{
    cv::Mat mapX(source.size(), CV_32FC1), mapY(source.size(), CV_32FC1);
    for (auto row = 0; row < mapX.rows; ++row) {
        for (auto col = 0; col < mapX.cols; ++col) {
            switch (static_cast<REMAPPING_TYPE>(type))
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
