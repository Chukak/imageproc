#ifndef LINEARFILTER_H
#define LINEARFILTER_H

#include "interface/operation.h"
#include <opencv2/core/types.hpp>

class LinearFilter : public Operation
{
public:
    explicit LinearFilter(cv::Mat&& src, int8_t ker_size = 3);

    inline void set_anchor(int x, int y) noexcept
    { anchor = cv::Point(x, y); }
    inline void set_delta(int d) noexcept
    { delta = d; }
    static bool precheck_kernel_size(int8_t k) noexcept;
public:
    void run() final;
private:
    cv::Mat source;
    int delta{0};
    int8_t kernel_size{3};
    cv::Point anchor{-1, -1};
};

#endif // LINEARFILTER_H
