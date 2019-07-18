#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "interface/operation.h"

enum THRESHOLD_TYPE
{
    THRESHOLD_BINARY = 0,
    THRESHOLD_BINARY_INVERTED = 1,
    THRESHOLD_TRUNCATED = 2,
    THRESHOLD_TO_ZERO = 3,
    THRESHOLD_TO_ZERO_INVERTED = 4
};

class Threshold : public Operation
{
public:
    explicit Threshold(THRESHOLD_TYPE t, cv::Mat&& src, int16_t v, bool gray = false);

    static THRESHOLD_TYPE parse_type(const char* flag) noexcept;
    static bool precheck_value(int16_t v) noexcept;
public:
    void run() final;
private:
    THRESHOLD_TYPE type{THRESHOLD_BINARY};
    bool is_gray{false};
    cv::Mat source;
    int16_t value{static_cast<int16_t>(2 / max_threshold_value)};
    static const int16_t& max_threshold_value;
};

#endif // THRESHOLD_H
