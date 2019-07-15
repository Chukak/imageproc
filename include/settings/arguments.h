#ifndef ARGUMENTS_H
#define ARGUMENTS_H

class Wrapper;

namespace command_line
{

class Arguments
{
public:
    explicit Arguments(int argc, char** argv, Wrapper *w);
    ~Arguments() = default;
    Arguments(Arguments&&) = delete;
    Arguments(const Arguments&) = delete;

    Arguments& operator=(Arguments&&) = delete;
    Arguments& operator=(const Arguments&) = delete;

    inline bool is_valid() const noexcept { return valid; }
    inline bool is_finish() const noexcept { return finish; }

private:
    bool valid{true};
    bool finish{false};
};

void show_help() noexcept;

}

#endif // ARGUMENTS_H
