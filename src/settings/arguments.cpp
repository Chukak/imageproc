#include "settings/arguments.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"
#include "execute/process.h"
#include "execute/wrapper.h"
#include "base/blur.h"
#include "base/show.h"
#include "base/threshold.h"
#include "base/linearfilter.h"
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
            // blur
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
                        if (argc - c++ > 1) {
                            // todo
                            if (find_if(begin(blur_opt::BLUR_TYPE_VALUES),
                                        end(blur_opt::BLUR_TYPE_VALUES),
                                        [argv, c](const char * a) -> bool { return !strcmp(a, argv[c]); })
                                    != end(blur_opt::BLUR_TYPE_VALUES)) {
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
                if (!(argc - c > 0)) {
                    printe(IMG_NOT_FOUND_MSG);
                    finish = true;
                    return;
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

            // threshold
            if (!strcmp(argv[c], THRESHOLD_OPTION)) {
                THRESHOLD_TYPE type(THRESHOLD_BINARY);
                int16_t value = -1;
                bool is_gray = false;
                while (++c < argc) {
                    if (!strcmp(argv[c], threshold_opt::THRESHOLD_VALUE)) {
                        if (argc - c > 1) {
                            value = atoi(argv[++c]);
                            if (!Threshold::precheck_value(value)) {
                                printe(threshold::THRESHOLD_VALUE_MSG);
                                finish = true;
                                return;
                            }
                            continue;
                        }
                        printe(threshold::THRESHOLD_VALUE_MSG);
                        finish = true;
                        return;
                    }
                    if (!strcmp(argv[c], threshold_opt::THRESHOLD_TYPE)) {
                        if (argc - c++ > 1) {
                            if (find_if(begin(threshold_opt::THRESHOLD_TYPE_VALUES),
                                        end(threshold_opt::THRESHOLD_TYPE_VALUES),
                                        [argv, c](const char * a) -> bool { return !strcmp(a, argv[c]); })
                                    != end(threshold_opt::THRESHOLD_TYPE_VALUES)) {
                                type = Threshold::parse_type(argv[c]);
                            } else  {
                                printe(threshold::THRESHOLD_TYPE_MSG);
                                finish = true;
                                return;
                            }
                            continue;
                        }
                        printe(threshold::SET_THRESHOLD_TYPE_MSG);
                        finish = true;
                        return;
                    }
                    if (!strcmp(argv[c], threshold_opt::THRESHOLD_GRAY)) {
                        is_gray = true;
                        continue;
                    }
                    break;
                }
                if (!(argc - c > 0)) {
                    printe(IMG_NOT_FOUND_MSG);
                    finish = true;
                    return;
                }
                cv::Mat frame = cv::imread(argv[c]);
                if (frame.empty()) {
                    printe(IMG_NOT_FOUND_MSG);
                    finish = true;
                    return;
                }
                auto threshold = new Threshold(type, move(frame), value, is_gray);
                auto process = make_process(threshold, &Threshold::run);
                w->set(process);
                return;
            }
            // linear filter
            if (!strcmp(argv[c], LINEAR_FILTER_OPTION)) {
                int8_t kernel_size = 3;
                int x = -1, y = -1;
                int delta = 0;
                while (++c < argc) {
                    if (!strcmp(argv[c], linear_filter_opt::LINEAR_FILTER_ANCHOR)) {
                        if (argc - c > 2) {
                            x = atoi(argv[++c]);
                            y = atoi(argv[++c]);
                            continue;
                        }
                        printe(linear_filter::SET_X_Y_MSG);
                        finish = true;
                        return;
                    }
                    if (!strcmp(argv[c], linear_filter_opt::LINEAR_FILTER_KERNEL_SIZE)) {
                        if (argc - c > 1) {
                            kernel_size = atoi(argv[++c]);
                            if (!LinearFilter::precheck_kernel_size(kernel_size)) {
                                printe(linear_filter::SET_LINEAR_FILTER_KERNEL_SIZE_MSG);
                                finish = true;
                                return;
                            }
                            continue;
                        }
                        printe(linear_filter::LINEAR_FILTER_KERNEL_SIZE_MSG);
                        finish = true;
                        return;
                    }
                    if (!strcmp(argv[c], linear_filter_opt::LINEAR_FILTER_DELTA)) {
                        if (argc - c > 1) {
                            delta = atoi(argv[++c]);
                            continue;
                        }
                        printe(linear_filter::SET_LINEAR_FILTER_DELTA_MSG);
                        finish = true;
                        return;
                    }
                    break;
                }

                if (!(argc - c > 0)) {
                    printe(IMG_NOT_FOUND_MSG);
                    finish = true;
                    return;
                }
                cv::Mat frame = cv::imread(argv[c]);
                if (frame.empty()) {
                    printe(IMG_NOT_FOUND_MSG);
                    finish = true;
                    return;
                }
                auto filter = new LinearFilter(move(frame), kernel_size);
                if (x > 0 && y > 0) {
                    filter->set_anchor(x, y);
                }
                if (delta != 0) {
                    filter->set_delta(delta);
                }
                auto process = make_process(filter, &LinearFilter::run);
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
