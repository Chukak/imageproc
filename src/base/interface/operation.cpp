#include "base/interface/operation.h"

Operation::Operation(cv::Mat&& src) :
    source(std::forward<cv::Mat>(src))
{
}
