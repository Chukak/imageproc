#ifndef LINEARFILTER_H
#define LINEARFILTER_H

#include "interface/operation.h"
#include "interface/kernelsize.h"
#include "interface/anchorpoint.h"

class LinearFilter
    : public Operation
    , public KernelSize
    , public AnchorPoint
{
public:
	explicit LinearFilter(cv::Mat&& src);
	void set_delta(int d) noexcept;

public:
	void run() final;

private:
	int delta{0};
};

#endif // LINEARFILTER_H
