#ifndef BLUR_H
#define BLUR_H

#include "interface/operation.h"
#include "interface/kernelsize.h"
#include "interface/operationtype.h"
#include "interface/anchorpoint.h"

enum BLUR_TYPE : OperationType::type_t
{
    BLUR_ORIGINAL,
    BLUR_GAUSSIAN,
    BLUR_MEDIAN,
    BLUR_BILATERAL
};

class Blur : public Operation, public KernelSize, public OperationType, public AnchorPoint
{
public:
    explicit Blur(COMMON_CLASS_TYPE t, cv::Mat&& src);
public:
    void run() final;
private:
    OT_VARIABLES
};

#endif
