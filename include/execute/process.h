#ifndef PROCESS_H
#define PROCESS_H

#include <memory>
#include <functional>
#include "execute/internal/baseprocess.h"

template<class C>
class Process : public BaseProcess
{
public:
    Process();
    Process(C * obj, void (C::*fn)());
    ~Process() final = default;
    Process(Process&&) noexcept = default;
    Process(const Process&) = default;

    Process& operator=(Process&&) noexcept = default;
    Process& operator=(const Process&) = default;

    void set_data(C * obj, void (C::*fn)()) noexcept;
    void exec() noexcept;
    auto obj() const noexcept { return object; }
private:
    std::shared_ptr<C> object{nullptr};
    std::function<void(C*)> method{nullptr};
};

template<typename T>
inline auto make_process(T* obj, void (T::*fn)()) noexcept
{
    return new Process<T>(obj, fn);
}

#endif // PROCESS_H
