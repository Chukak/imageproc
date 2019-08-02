#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>

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
    inline bool has_save_path() const noexcept { return save_path.length(); }
    inline const std::string saved_image_name() const noexcept { return save_path; }

private:
    bool valid{true};
    bool finish{false};
    std::string save_path{""};
};

void show_help() noexcept;

}

#endif // ARGUMENTS_H
