#include "settings/arguments.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"
#include "execute/process.h"
#include "execute/wrapper.h"
#include "base/blur.h"
#include "base/show.h"
#include <iostream>
#include <string>
#include <cstring>
#include <opencv2/imgcodecs.hpp>

using namespace command_line;
using namespace std;
using namespace msg;

Arguments::Arguments(int argc, char** argv, Wrapper *w)
{
    using namespace options;

    valid = argc > 1;
    if (valid) {
        for (auto c = 1; c < argc; ++c) {
            if (!strcmp(argv[c], HELP_OPTION)) {
                show_help();
                finish = true;
                return;
            }

            if (!strcmp(argv[c], BLUR_OPTION)) {
                BLUR_TYPE type(BLUR_ORIGINAL);
                int x = -1, y = -1;
                while (++c < argc) {
                    if (!strcmp(argv[c], blur_opt::BLUR_POINT)) {
                        if (argc - c > 2) {
                            x = atoi(argv[++c]);
                            y = atoi(argv[++c]);
                            continue;
                        }
                        printe(blur::SET_X_Y_MSG);
                        finish = true;
                        return;
                    }
                    if (!strcmp(argv[c], blur_opt::BLUR_TYPE)) {
                        if (argc - c > 1) {
                            // todo
                            if (find_if(begin(blur_opt::BLUR_TYPES),
                                     end(blur_opt::BLUR_TYPES),
                                     [&argv, &c](const char * a) -> bool { return !strcmp(a, argv[++c]); }) != end(blur_opt::BLUR_TYPES)) {
                                type = Blur::parse_type(argv[c]);
                            } else {
                                printe(blur::BLUR_TYPE_MSG);
                                finish = true;
                                return;
                            }
                            continue;
                        }
                        printe(blur::SET_BLUR_TYPE_MSG);
                        finish = true;
                        return;
                    }
                    break;
                }
                cv::Mat frame = cv::imread(argv[c]);
                if (frame.empty()) {
                    printe(IMG_NOT_FOUND_MSG);
                    finish = true;
                    return;
                }
                auto blur = new Blur(type, move(frame));
                if (x > -1 && y > -1) {
                    blur->set_anchor(cv::Point(x, y));
                }
                auto process = make_process(blur, &Blur::run);
                w->set(process);
                return;
            }
            // only image, just show it
            auto show = new Show(argv[c]);
            auto process = make_process(show, &Show::run);
            w->set(process);
            return;
        }
    } else {
        show_help();
    }
}

void command_line::show_help() noexcept
{
    printm(HELP_MSG);
}
