#ifndef PARSER_H
#define PARSER_H

#include "execute/wrapper.h"
#include "execute/process.h"

class Parser
{
public:
    explicit Parser(int _argc, char** _argv, Wrapper* w);
    void set_image(cv::Mat& frame, bool& ok = Parser::default_ok_val) noexcept;
    void check_save_path() noexcept;
    template<typename ... Args>
    void set_process(Args ... args) noexcept
    {
        if (wrapper) {
            auto process = make_process(args ...);
            wrapper->set(process);
        }
    }
    void add_error(const char * e) noexcept;
    virtual void parse() noexcept = 0;

    inline bool has_error() const noexcept
    { return has_errors; }
    inline std::string saved_image_name() const noexcept
    { return path_to_save; }
protected:
    int argc;
    char** argv;
    int index{1};
    bool has_errors{false};
    std::string path_to_save{""};
private:
    static bool default_ok_val;
    Wrapper* wrapper{nullptr};
};

template<class C, typename ... Args>
std::string run_parser_by_default(bool& finish, Args ... args) noexcept
{
    if (std::is_base_of_v<Parser, C>) {
        C p(args ...);
        p.parse(); 
        finish = p.has_error();
        return std::move(p.saved_image_name());
    }
    return "";
}

#endif // PARSER_H
