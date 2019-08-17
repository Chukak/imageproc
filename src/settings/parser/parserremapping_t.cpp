#include "settings/parser/parserremapping_t.h"
#include "base/remapping.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"
#include <string>

using namespace msg;
using namespace command_line;

ParserRemapping_t::ParserRemapping_t(int argc, char** argv, Wrapper* w) :
    Parser(argc, argv, w)
{
}

void ParserRemapping_t::parse() noexcept
{
    using namespace options;

    REMAPPING_TYPE type(REMAPPING_UPSIDE_DOWN);
    while (++index < argc) {
        if (!strcmp(argv[index], remapping_opt::REMAPPING_TYPE)) {
            if (argc - index++ > 1) {
                if (find_value()) {
                    type = Remapping::parse_type(argv[index]);
                } else {
                    add_error(remapping::REMAPPING_TYPE_MSG);
                    break;
                }
                continue;
            }
            add_error(remapping::SET_REMAPPING_TYPE_MSG);
        }
        break;
    }
    check_save_path();
    cv::Mat frame;
    bool ok;
    set_image(frame, ok);
    if (ok) {
        auto remapping = new Remapping(type, std::move(frame));
        set_process(remapping, &Remapping::run);
    }
}

bool ParserRemapping_t::find_value() const noexcept
{
    return std::find_if(std::begin(options::remapping_opt::REMAPPING_TYPE_VALUES),
                        std::end(options::remapping_opt::REMAPPING_TYPE_VALUES),
                        [this](const char * a) -> bool { return !strcmp(a, argv[index]); })
            != std::end(options::remapping_opt::REMAPPING_TYPE_VALUES);
}

