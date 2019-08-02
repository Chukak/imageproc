#include "settings/parser/internal/parser.h"
#include "execute/internal/baseprocess.h"
#include "settings/messages.h"
#include "base/blur.h"
#include "base/linearfilter.h"
#include "base/show.h"
#include "base/threshold.h"
#include <opencv2/imgcodecs.hpp>

using namespace msg;

bool Parser::default_ok_val{true};


Parser::Parser(int _argc, char ** _argv, Wrapper* w) :
    argc(_argc),
    argv(_argv),
    wrapper(w)
{
}

void Parser::set_image(cv::Mat& frame, bool& ok) noexcept
{
    has_errors = !argc - index > 0;
    if (!has_errors) {
        frame = cv::imread(argv[index]);
        has_errors = frame.empty();
    }
    ok = !has_errors;
    if (!ok) {
        printe(IMG_NOT_FOUND_MSG);
    }
}

void Parser::add_error(const char * e) noexcept
{
    has_errors = true;
    printe(e);
}
