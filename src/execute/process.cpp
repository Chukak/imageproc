#include "execute/process.h"

Process::Process(std::unique_ptr<Operation>&& obj) :
    object(std::forward<decltype(obj)>(obj))
{}

Process::Process(Process&& p) noexcept
{
	object.reset(p.object.get());
	p.object.reset();
}

Process::Process(const Process& p) noexcept
{
	object.reset(p.object.get());
}

Process& Process::operator=(Process&& p) noexcept
{
	object.reset(p.object.get());
	p.object.reset();
	return *this;
}

Process& Process::operator=(const Process& p) noexcept
{
	object.reset(p.object.get());
	return *this;
}

void Process::set(Operation* obj) noexcept
{
	object.reset(obj);
}

void Process::exec() noexcept
{
	object->run();
}

const Operation* Process::get() const noexcept
{
	return const_cast<decltype(object.get())>(object.get());
}
