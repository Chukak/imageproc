#ifndef REMAPPING_H
#define REMAPPING_H

#include "interface/operation.h"

enum REMAPPING_TYPE
{
    REMAPPING_UPSIDE_DOWN,
    REMAPPING_X_DIRECTION,
    REMAPPING_BOTH_DIRECTION
};

class Remapping : public Operation
{
public:
    Remapping(REMAPPING_TYPE t, cv::Mat&& src);
    static REMAPPING_TYPE parse_type(const char* flag) noexcept;
public:
    void run() final;
private:
    REMAPPING_TYPE type;
    cv::Mat source;
};

#endif // REMAPPING_H
