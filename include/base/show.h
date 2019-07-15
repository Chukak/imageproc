#ifndef SHOW_H
#define SHOW_H

#include <opencv2/core/mat.hpp>

class Show
{
public:
    explicit Show(const char * path);
    inline bool good() const noexcept { return ok; }
    void run() noexcept {}
public:
    cv::Mat result;
private:
    bool ok{true};
};

#endif // SHOW_H
