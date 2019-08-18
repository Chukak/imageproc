#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "settings/internal/types.h"

class Wrapper;

namespace command_line
{
class Arguments
{
public:
	explicit Arguments(int argc, char** argv, Wrapper* w);
	~Arguments() = default;
	Arguments(Arguments&&) = delete;
	Arguments(const Arguments&) = delete;

	Arguments& operator=(Arguments&&) = delete;
	Arguments& operator=(const Arguments&) = delete;

private:
	void print_errors() const noexcept;

public:
	bool finish{false};
	bool valid{true};
	std::string save_path{""};
	errors_t errors;
};

void show_help() noexcept;

} // namespace command_line

#endif // ARGUMENTS_H
