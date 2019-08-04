#include "settings/arguments.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"
#include "execute/wrapper.h"
#include "settings/parser/parserblur_t.h"
#include "settings/parser/parserlinearfilter_t.h"
#include "settings/parser/parsershow_t.h"
#include "settings/parser/parserthreshold_t.h"
#include "settings/parser/detectbrightedge_t.h"

using namespace command_line;

Arguments::Arguments(int argc, char** argv, Wrapper *w)
{
    using namespace options;

    valid = argc > 1;
    if (valid) {
        for (auto c = 1; c < argc; ++c) {
            if (!strcmp(argv[c], HELP_OPTION)) {
                show_help();
                finish = true;
            } else if (!strcmp(argv[c], BLUR_OPTION)) {
                save_path = run_parser_by_default<ParserBlur_t>(finish, argc, argv, w);
            } else if (!strcmp(argv[c], THRESHOLD_OPTION)) {
                save_path = run_parser_by_default<ParserThreshold_t>(finish, argc, argv, w);
            } else if (!strcmp(argv[c], LINEAR_FILTER_OPTION)) {
                save_path = run_parser_by_default<ParserLinearFilter_t>(finish, argc, argv, w);
            } else if (!strcmp(argv[c], BRIGHT_EDGE_OPTION)) {
                save_path = run_parser_by_default<DetectBrightEdge_t>(finish, argc, argv, w);
            } else {
                save_path = run_parser_by_default<ParserShow_t>(finish, argc, argv, w);
            }
            break;
        }
    } else {
        show_help();
    }
}

void command_line::show_help() noexcept
{
    printm(msg::HELP_MSG);
}
