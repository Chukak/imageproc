#include "execute/wrapper.h"

Wrapper::Wrapper(Process *p) :
    process(p)
{
}

void Wrapper::set(Process *p) noexcept
{
    process.reset(p);
}

bool Wrapper::exec() noexcept
{
    if (process) {
        process->exec();
        result = process->get()->result;
        return process->get()->good();
    }
    return false;
}

