#include "settings/parser/parserblur_t.h"
#include "base/blur.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"
#include <string>

using namespace msg;
using namespace command_line;

ParserBlur_t::ParserBlur_t(int argc, char** argv, Wrapper* w) :
    Parser(argc, argv, w)
{
}

void ParserBlur_t::parse() noexcept
{
    using namespace options;

    BLUR_TYPE type(BLUR_ORIGINAL);
    int x = -1, y = -1;
    while (++index < argc) {
        if (!strcmp(argv[index], blur_opt::BLUR_POINT)) {
            if (argc - index > 2) {
                x = atoi(argv[++index]);
                y = atoi(argv[++index]);
                continue;
            }
            add_error(blur::SET_X_Y_MSG);
        } else if (!strcmp(argv[index], blur_opt::BLUR_TYPE)) {
            if (argc - index++ > 1) {
                if (find_value()) {
                    type = Blur::parse_type(argv[index]);
                } else {
                    add_error(blur::BLUR_TYPE_MSG);
                    break;
                }
                continue;
            }
            add_error(blur::SET_BLUR_TYPE_MSG);
        }
        break;
    }
    check_save_path();
    cv::Mat frame;
    bool ok;
    set_image(frame, ok);
    if (ok) {
        auto blur = new Blur(type, std::move(frame));
        if (x > -1 && y > -1) {
            blur->set_anchor(cv::Point(x, y));
        }
        set_process(blur, &Blur::run);
    }
}

bool ParserBlur_t::find_value() const noexcept
{
    return std::find_if(std::begin(options::blur_opt::BLUR_TYPE_VALUES),
                        std::end(options::blur_opt::BLUR_TYPE_VALUES),
                        [this](const char * a) -> bool { return !strcmp(a, argv[index]); })
            != std::end(options::blur_opt::BLUR_TYPE_VALUES);
}
