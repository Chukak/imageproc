#ifndef PROCESS_H
#define PROCESS_H

#include "base/interface/operation.h"

class Process
{
	template<typename T>
	friend auto make_process(T*) noexcept;

public:
	Process() = default;
	Process(std::unique_ptr<Operation>&& obj);
	~Process() = default;
	Process(Process&&) noexcept;
	Process(const Process&) noexcept;

	Process& operator=(Process&&) noexcept;
	Process& operator=(const Process&) noexcept;

	void set(Operation* obj) noexcept;
	void exec() noexcept;
	const Operation* get() const noexcept;

private:
	std::unique_ptr<Operation> object{nullptr};
};

template<typename T>
auto make_process(T* obj) noexcept
{
	return new Process(std::unique_ptr<T>(obj));
}

#endif // PROCESS_H
