#include "execute/wrapper.h"
#include "execute/process.h"
#include "base/blur.h"
#include "base/show.h"
#include "base/threshold.h"
#include "base/linearfilter.h"
#include "base/detectbrigthedge.h"

Wrapper::Wrapper(BaseProcess *p) :
    process(p)
{
}

void Wrapper::set(BaseProcess *p) noexcept
{
    process.reset(p);
}

bool Wrapper::run_exec() noexcept
{
    if (process) {
        switch (process->type()) {
        case BaseProcess::Blur_t: {
            auto p = dynamic_cast<Process<Blur> *>(process.get());
            return run_as_default(p);
        }
        case BaseProcess::Show_t: {
            auto p = dynamic_cast<Process<Show> *>(process.get());
            return run_as_default(p);
        }
        case BaseProcess::Threshold_t: {
            auto p = dynamic_cast<Process<Threshold> *>(process.get());
            return run_as_default(p);
        }
        case BaseProcess::LinearFilter_t: {
            auto p = dynamic_cast<Process<LinearFilter> *>(process.get());
            return run_as_default(p);
        }
        case BaseProcess::DetectBrightEdge_t: {
            auto p = dynamic_cast<Process<DetectBrigthEdge> *>(process.get());
            return run_as_default(p);
        }
        default:
            return false;
        }
    }
    return false;
}

