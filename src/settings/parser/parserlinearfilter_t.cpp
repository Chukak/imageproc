#include "settings/parser/parserlinearfilter_t.h"
#include "base/linearfilter.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"

namespace opts = command_line::options::linear_filter_opt;

ParserLinearFilter_t::ParserLinearFilter_t(int argc, char** argv, Wrapper* w) :
    Parser(argc, argv, w)
{
}

void ParserLinearFilter_t::parse() noexcept
{
    int8_t kernel_size = -1;
    int x = -1, y = -1;
    int delta = 0;
    while (++index < argc) {
        if (argv[index] == opts::LINEAR_FILTER_ANCHOR) {
            if (argc - index > 2) {
                x = atoi(argv[++index]);
                y = atoi(argv[++index]);
                continue;
            }
            add_error(msg::linear_filter::SET_X_Y_MSG);
        } else if (argv[index] == opts::LINEAR_FILTER_KERNEL_SIZE) {
            if (argc - index > 1) {
                kernel_size = atoi(argv[++index]);
                if (!LinearFilter::ks_check(kernel_size)) {
                    add_error(msg::linear_filter::SET_LINEAR_FILTER_KERNEL_SIZE_MSG);
                    break;
                }
                continue;
            }
            add_error(msg::linear_filter::LINEAR_FILTER_KERNEL_SIZE_MSG);
        } else if (argv[index] == opts::LINEAR_FILTER_DELTA) {
            if (argc - index > 1) {
                delta = atoi(argv[++index]);
                continue;
            }
            add_error(msg::linear_filter::SET_LINEAR_FILTER_DELTA_MSG);
        }
        break;
    }
    set_save_path();
    cv::Mat frame;
    set_image(frame);
    if (!bad) {
        auto filter = new LinearFilter(std::move(frame));
        if (kernel_size > 0) {
            filter->ks_set(kernel_size);
        }
        if (x > 0 && y > 0) {
            filter->ap_set(x, y);
        }
        if (delta != 0) {
            filter->set_delta(delta);
        }
        set_process(filter);
    }
}
