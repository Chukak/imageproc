#include "settings/parser/parserlinearfilter_t.h"
#include "base/linearfilter.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"

using namespace msg;
using namespace command_line;

ParserLinearFilter_t::ParserLinearFilter_t(int argc, char** argv, Wrapper* w) :
    Parser(argc, argv, w)
{
}

void ParserLinearFilter_t::parse() noexcept
{
    using namespace options;

    int8_t kernel_size = -1;
    int x = -1, y = -1;
    int delta = 0;
    while (++index < argc) {
        if (!strcmp(argv[index], linear_filter_opt::LINEAR_FILTER_ANCHOR)) {
            if (argc - index > 2) {
                x = atoi(argv[++index]);
                y = atoi(argv[++index]);
                continue;
            }
            add_error(linear_filter::SET_X_Y_MSG);
        } else if (!strcmp(argv[index], linear_filter_opt::LINEAR_FILTER_KERNEL_SIZE)) {
            if (argc - index > 1) {
                kernel_size = atoi(argv[++index]);
                if (!LinearFilter::precheck_kernel_size(kernel_size)) {
                    add_error(linear_filter::SET_LINEAR_FILTER_KERNEL_SIZE_MSG);
                    break;
                }
                continue;
            }
            add_error(linear_filter::LINEAR_FILTER_KERNEL_SIZE_MSG);
        } else if (!strcmp(argv[index], linear_filter_opt::LINEAR_FILTER_DELTA)) {
            if (argc - index > 1) {
                delta = atoi(argv[++index]);
                continue;
            }
            add_error(linear_filter::SET_LINEAR_FILTER_DELTA_MSG);
        }
        break;
    }
    cv::Mat frame;
    bool ok;
    set_image(frame, ok);
    if (ok) {
        auto filter = new LinearFilter(std::move(frame));
        if (kernel_size > 0) {
            filter->set_kernel_size(kernel_size);
        }
        if (x > 0 && y > 0) {
            filter->set_anchor(x, y);
        }
        if (delta != 0) {
            filter->set_delta(delta);
        }
        set_process(filter, &LinearFilter::run);
    }
}
