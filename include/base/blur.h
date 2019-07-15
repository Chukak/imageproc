#ifndef BLUR_H
#define BLUR_H

#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>

enum BLUR_TYPE
{
    BLUR_ORIGINAL,
    BLUR_GAUSSIAN,
    BLUR_MEDIAN,
    BLUR_BILATERAL
};

class Blur
{
public:
    explicit Blur(BLUR_TYPE t, cv::Mat&& src);

    inline bool good() const noexcept { return ok; }
    inline void set_anchor(cv::Point&& anch) noexcept { anchor = std::forward<cv::Point>(anch); }
    static BLUR_TYPE parse_type(const char* flag) noexcept;
public:
    cv::Mat result;
public:
    void run();
private:
    BLUR_TYPE type;
    cv::Mat source;
    cv::Point anchor{-1, -1};
    bool ok{true};
    short max_kernel_length{27};
};


#endif
