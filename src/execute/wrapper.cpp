#include "execute/wrapper.h"
#include "execute/process.h"
#include "base/blur.h"
#include "base/show.h"
#include "base/threshold.h"

Wrapper::Wrapper(BaseProcess *p) :
    process(p)
{
}

Wrapper::~Wrapper()
{
    // todo
    delete process;
}

void Wrapper::set(BaseProcess *p) noexcept
{
    process = p;
}

bool Wrapper::run_exec() noexcept
{
    switch (process->type()) {
    case BaseProcess::Blur_t: {
        auto p = dynamic_cast<Process<Blur> *>(process);
        return run_as_default(p);
    }
    case BaseProcess::Show_t: {
        auto p = dynamic_cast<Process<Show> *>(process);
        return run_as_default(p);
    }
    case BaseProcess::Threshold_t: {
        auto p = dynamic_cast<Process<Threshold> *>(process);
        return run_as_default(p);
    }
    default:
        return false;
    }
    return false;
}

