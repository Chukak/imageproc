#ifndef HISTOGRAMEQUALIZATION_H
#define HISTOGRAMEQUALIZATION_H

#include "interface/operation.h"

class HistogramEqualization : public Operation
{
public:
	explicit HistogramEqualization(cv::Mat&& src);

public:
	void run() final;
};

#endif // HISTOGRAMEQUALIZATION_H
