#include "settings/parser/parserthreshold_t.h"
#include "base/threshold.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"
#include <string>

using namespace msg;
using namespace command_line;

ParserThreshold_t::ParserThreshold_t(int argc, char** argv, Wrapper* w) :
    Parser(argc, argv, w)
{
}

void ParserThreshold_t::parse() noexcept
{
    using namespace options;

    THRESHOLD_TYPE type(THRESHOLD_BINARY);
    int16_t value = -1;
    bool is_gray = false;
    while (++index < argc) {
        if (!strcmp(argv[index], threshold_opt::THRESHOLD_VALUE)) {
            if (argc - index > 1) {
                value = atoi(argv[++index]);
                if (Threshold::precheck_value(value)) {
                    continue;
                }
                add_error(threshold::THRESHOLD_VALUE_MSG);
            }
            add_error(threshold::THRESHOLD_VALUE_MSG);
        } else if (!strcmp(argv[index], threshold_opt::THRESHOLD_TYPE)) {
            if (argc - index++ > 1) {
                if (find_value()) {
                    type = Threshold::parse_type(argv[index]);
                } else  {
                    add_error(threshold::THRESHOLD_TYPE_MSG);
                    break;
                }
                continue;
            }
            add_error(threshold::SET_THRESHOLD_TYPE_MSG);
        } else if (!strcmp(argv[index], threshold_opt::THRESHOLD_GRAY)) {
            is_gray = true;
            continue;
        }
        break;
    }
    check_save_path();
    cv::Mat frame;
    bool ok;
    set_image(frame, ok);
    if (ok) {
        auto threshold = new Threshold(type, std::move(frame), is_gray);
        if (value > -1) {
            threshold->set_value(value);
        }
        set_process(threshold, &Threshold::run);
    }
}

bool ParserThreshold_t::find_value() const noexcept
{
    return std::find_if(std::begin(options::threshold_opt::THRESHOLD_TYPE_VALUES),
                        std::end(options::threshold_opt::THRESHOLD_TYPE_VALUES),
                        [this](const char * a) -> bool { return !strcmp(a, argv[index]); })
            != std::end(options::threshold_opt::THRESHOLD_TYPE_VALUES);
}
