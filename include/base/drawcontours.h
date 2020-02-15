#ifndef DRAWCONTOURS_H
#define DRAWCONTOURS_H

#include "interface/operation.h"
#include "interface/kernelsize.h"
#include "interface/thresholdinterface.h"

class DrawContours
    : public Operation
    , public KernelSize
    , public ThresholdInterface
{
public:
	explicit DrawContours(cv::Mat&& src);
	void run() final;
};

#endif // DRAWCONTOURS_H
