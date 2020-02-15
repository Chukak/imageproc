#include "settings/parser/parserdrawcontours_t.h"
#include "base/drawcontours.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"

namespace opts = command_line::options::draw_contours_opt;

ParserDrawContours_t::ParserDrawContours_t(int argc, char** argv, Wrapper* w) :
		Parser(argc, argv, w)
{}

void ParserDrawContours_t::parse() noexcept
{
	int8_t kernel_size = -1;
	int threshold_value = -1;
	while(++index < argc) {
		if(argv[index] == opts::DRAW_CONTOURS_THRESHOLD) {
			if(argc - index > 1) {
				threshold_value = atoi(argv[++index]);
				if(DrawContours::thr_check_value(threshold_value)) {
					continue;
				}
			}
			add_error(msg::draw_contours::DRAW_CONTOURS_THRESHOLD_VALUE_MSG);
		} else if(argv[index] == opts::DRAW_CONTOURS_KERNEL_SIZE) {
			if(argc - index > 1) {
				kernel_size = atoi(argv[++index]);
				if(!DrawContours::ks_check(kernel_size)) {
					add_error(msg::draw_contours::DRAW_CONTOURS_KERNEL_SIZE_MSG);
					break;
				}
				continue;
			}
			add_error(msg::draw_contours::DRAW_CONTOURS_KERNEL_SIZE_MSG);
		}
		break;
	}
	set_save_path();
	cv::Mat frame;
	set_image(frame);
	if(!bad) {
		auto contours = new DrawContours(std::move(frame));
		if(kernel_size > 0) {
			contours->ks_set(kernel_size);
		}
		if(threshold_value > 0) {
			contours->thr_set_value(threshold_value);
		}
		set_process(contours);
	}
}
