#ifndef WRAPPER_H
#define WRAPPER_H

#include "execute/internal/baseprocess.h"
#include <opencv2/core/mat.hpp>

class Wrapper
{
public:
    Wrapper() = default;
    Wrapper(BaseProcess *p);
    ~Wrapper();
    Wrapper(Wrapper&&) = delete;
    Wrapper(const Wrapper&) = delete;

    Wrapper& operator=(Wrapper&&) = delete;
    Wrapper& operator=(const Wrapper&) = delete;

    void set(BaseProcess *p) noexcept;
    bool run_exec() noexcept;
    inline auto get_result() const noexcept { return result; }

private:
    template<typename P>
    bool run_as_default(P p) noexcept
    {
        if (p) {
            p->exec();
            result = p->obj()->result;
            return p->obj()->good();
        }
        return false;
    }
private:
    BaseProcess *process{nullptr};
    cv::Mat result{};
};

#endif // WRAPPER_H
