#ifndef DETECTBRIGTHEDGE_H
#define DETECTBRIGTHEDGE_H

#include "interface/operation.h"

class DetectBrigthEdge : public Operation
{
public:
   explicit DetectBrigthEdge(cv::Mat&& src);

public:
    void run() final;
private:
    cv::Mat source;
    int delta{0};
    double scale{1};
    int8_t kernel_size{3};
    static const double alpha;
};

#endif // DETECTBRIGTHEDGE_H
