#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <opencv2/core/mat.hpp>

enum THRESHOLD_TYPE
{
    THRESHOLD_BINARY = 0,
    THRESHOLD_BINARY_INVERTED = 1,
    THRESHOLD_TRUNCATED = 2,
    THRESHOLD_TO_ZERO = 3,
    THRESHOLD_TO_ZERO_INVERTED = 4
};

class Threshold
{
public:
    explicit Threshold(THRESHOLD_TYPE t, cv::Mat&& src, int16_t v, bool gray = false);

    inline bool good() const noexcept { return ok; }
    static THRESHOLD_TYPE parse_type(const char* flag) noexcept;
    static bool precheck_value(int16_t v) noexcept;
public:
    cv::Mat result;
public:
    void run();
private:
    THRESHOLD_TYPE type{THRESHOLD_BINARY};
    bool is_gray{false};
    cv::Mat source;
    int16_t value{static_cast<int16_t>(2 / max_threshold_value)};
    bool ok{true};
    static const int16_t& max_threshold_value;
};

#endif // THRESHOLD_H
