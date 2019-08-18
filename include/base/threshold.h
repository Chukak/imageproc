#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "interface/operation.h"
#include "interface/operationtype.h"

enum THRESHOLD_TYPE : OperationType::type_t
{
    THRESHOLD_BINARY = 0,
    THRESHOLD_BINARY_INVERTED = 1,
    THRESHOLD_TRUNCATED = 2,
    THRESHOLD_TO_ZERO = 3,
    THRESHOLD_TO_ZERO_INVERTED = 4
};

class Threshold : public Operation, public OperationType
{
public:
    explicit Threshold(COMMON_CLASS_TYPE t, cv::Mat&& src, bool gray = false);
    void set_value(int v) noexcept;
    static bool check_value(int16_t v) noexcept;
public:
    void run() final;
private:
    bool is_gray{false};
    static const int16_t max_threshold_value{255};
    int16_t value{static_cast<int16_t>(max_threshold_value / 2)};
    OT_VARIABLES
};

#endif // THRESHOLD_H
