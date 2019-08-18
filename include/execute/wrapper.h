#ifndef WRAPPER_H
#define WRAPPER_H

#include "execute/process.h"

class Wrapper
{
public:
    Wrapper() = default;
    Wrapper(Process *p);
    ~Wrapper() = default;
    Wrapper(Wrapper&&) = delete;
    Wrapper(const Wrapper&) = delete;

    Wrapper& operator=(Wrapper&&) = delete;
    Wrapper& operator=(const Wrapper&) = delete;

    void set(Process *p) noexcept;
    bool exec() noexcept;
    inline cv::Mat get() const noexcept { return result; }
private:
    std::unique_ptr<Process> process{nullptr};
    cv::Mat result{};
};

#endif // WRAPPER_H
