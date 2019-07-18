#ifndef OPERATION_H
#define OPERATION_H

#include <opencv2/core/mat.hpp>

class Operation
{
public:
    inline bool good() const noexcept { return ok; };
    virtual void run() = 0;
public:
    cv::Mat result;
protected:
    bool ok{true};
};

#endif // OPERATION_H
