#include "settings/parser/parserremapping_t.h"
#include "base/remapping.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"

namespace opts = command_line::options::remapping_opt;

ParserRemapping_t::ParserRemapping_t(int argc, char** argv, Wrapper* w) :
    Parser(argc, argv, w)
{
}

void ParserRemapping_t::parse() noexcept
{
    COMMON_CLASS_TYPE type(REMAPPING_UPSIDE_DOWN);
    while (++index < argc) {
        if (argv[index] == opts::REMAPPING_TYPE) {
            if (argc - index++ > 1) {
                if (find_in(opts::REMAPPING_TYPE_VALUES)) {
                    type = Remapping::parse_type(argv[index]);
                } else {
                    add_error(msg::remapping::REMAPPING_TYPE_MSG);
                    break;
                }
                continue;
            }
            add_error(msg::remapping::SET_REMAPPING_TYPE_MSG);
        }
        break;
    }
    set_save_path();
    cv::Mat frame;
    set_image(frame);
    if (!bad) {
        auto remapping = new Remapping(type, std::move(frame));
        set_process(remapping);
    }
}


