#include "settings/parser/internal/parser.h"
#include "settings/messages.h"
#include "settings/cmdoptions.h"
#include <opencv2/imgcodecs.hpp>

Parser::Parser(int _argc, char ** _argv, Wrapper* w) :
    argc(_argc),
    argv(_argv)
{
    wrapper.reset(w);
}

void Parser::set_image(cv::Mat& frame) noexcept
{
    bad = !argc - index > 0;
    if (!bad) {
        frame = cv::imread(argv[index]);
        bad = frame.empty();
    }
    if (bad) {
        add_error(msg::IMG_NOT_FOUND_MSG);
    }
}

void Parser::set_save_path() noexcept
{
    if (argv[index] == command_line::options::SAVE_OPTION) {
        if (argc - index++ > 1) {
            save = argv[index];
            index++;
        } else {
            add_error(msg::SET_SAVE_PATH_MSG);
        }
    }
}

void Parser::add_error(message_t e) noexcept
{
    bad = true;
    errors.emplace_back(e);
}

void Parser::executed_data(std::string &save, bool &finish, errors_t &errors)
{
    save = this->save;
    finish = bad;
    errors = this->errors;
}

ParserWrapper::ParserWrapper(std::string& s, bool& f, errors_t& e) :
    save(s),
    finish(f),
    errors(e)
{
}

void ParserWrapper::set_args(int _argc, char** _argv, Wrapper* _w)
{
    argc = _argc;
    argv = _argv;
    w = _w;
}
