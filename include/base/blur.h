#ifndef BLUR_H
#define BLUR_H

#include "interface/operation.h"
#include <opencv2/core/types.hpp>

enum BLUR_TYPE
{
    BLUR_ORIGINAL,
    BLUR_GAUSSIAN,
    BLUR_MEDIAN,
    BLUR_BILATERAL
};

class Blur : public Operation
{
public:
    explicit Blur(BLUR_TYPE t, cv::Mat&& src);

    inline void set_anchor(cv::Point&& anch) noexcept { anchor = std::forward<cv::Point>(anch); }
    static BLUR_TYPE parse_type(const char* flag) noexcept;
public:
    void run() final;
private:
    BLUR_TYPE type;
    cv::Mat source;
    cv::Point anchor{-1, -1};
    short max_kernel_length{27};
};


#endif
