#ifndef DETECTBRIGTHEDGE_H
#define DETECTBRIGTHEDGE_H

#include "interface/operation.h"
#include "interface/kernelsize.h"

class DetectBrigthEdge
    : public Operation
    , public KernelSize
{
public:
	explicit DetectBrigthEdge(cv::Mat&& src);

public:
	void run() final;

private:
	double scale{1};
	const int delta{0};
	const double alpha{0.5};
};

#endif // DETECTBRIGTHEDGE_H
