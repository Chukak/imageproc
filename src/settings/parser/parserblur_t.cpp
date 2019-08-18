#include "settings/parser/parserblur_t.h"
#include "base/blur.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"

namespace opts = command_line::options::blur_opt;

ParserBlur_t::ParserBlur_t(int argc, char** argv, Wrapper* w) : Parser(argc, argv, w)
{}

void ParserBlur_t::parse() noexcept
{
	COMMON_CLASS_TYPE type(BLUR_ORIGINAL);
	int8_t kernel_size = -1;
	int x = -1, y = -1;
	while(++index < argc) {
		if(argv[index] == opts::BLUR_POINT) {
			if(argc - index > 2) {
				x = atoi(argv[++index]);
				y = atoi(argv[++index]);
				continue;
			}
			add_error(msg::blur::SET_X_Y_MSG);
		} else if(argv[index] == opts::BLUR_TYPE) {
			if(argc - index++ > 1) {
				if(find_in(opts::BLUR_TYPE_VALUES)) {
					type = Blur::parse_type(argv[index]);
				} else {
					add_error(msg::blur::BLUR_TYPE_MSG);
					break;
				}
				continue;
			}
			add_error(msg::blur::SET_BLUR_TYPE_MSG);
		} else if(argv[index] == opts::BLUR_KERNEL_SIZE) {
			if(argc - index > 1) {
				kernel_size = atoi(argv[++index]);
				if(!Blur::ks_check(kernel_size)) {
					add_error(msg::linear_filter::SET_LINEAR_FILTER_KERNEL_SIZE_MSG);
					break;
				}
				continue;
			}
			add_error(msg::linear_filter::LINEAR_FILTER_KERNEL_SIZE_MSG);
		}
		break;
	}
	set_save_path();
	cv::Mat frame;
	set_image(frame);
	if(!bad) {
		auto blur = new Blur(type, std::move(frame));
		if(kernel_size > 0) {
			blur->ks_set(kernel_size);
		}
		if(x > -1 && y > -1) {
			blur->ap_set(cv::Point(x, y));
		}
		set_process(blur);
	}
}
