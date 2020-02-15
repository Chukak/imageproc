#include "settings/parser/parserthreshold_t.h"
#include "base/threshold.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"

namespace opts = command_line::options::threshold_opt;

ParserThreshold_t::ParserThreshold_t(int argc, char **argv, Wrapper *w) :
    Parser(argc, argv, w)
{}

void ParserThreshold_t::parse() noexcept
{
	COMMON_CLASS_TYPE type(THRESHOLD_BINARY);
	int16_t value = -1;
	bool is_gray = false;
	while(++index < argc) {
		if(argv[index] == opts::THRESHOLD_VALUE) {
			if(argc - index > 1) {
				value = atoi(argv[++index]);
				if(Threshold::thr_check_value(value)) {
					continue;
				}
			}
			add_error(msg::threshold::THRESHOLD_VALUE_MSG);
		} else if(argv[index] == opts::THRESHOLD_TYPE) {
			if(argc - index++ > 1) {
				if(find_in(opts::THRESHOLD_TYPE_VALUES)) {
					type = Threshold::parse_type(argv[index]);
				} else {
					add_error(msg::threshold::THRESHOLD_TYPE_MSG);
					break;
				}
				continue;
			}
			add_error(msg::threshold::SET_THRESHOLD_TYPE_MSG);
		} else if(argv[index] == opts::THRESHOLD_GRAY) {
			is_gray = true;
			continue;
		}
		break;
	}
	set_save_path();
	cv::Mat frame;
	set_image(frame);
	if(!bad) {
		auto threshold = new Threshold(type, std::move(frame), is_gray);
		if(value > -1) {
			threshold->thr_set_value(value);
		}
		set_process(threshold);
	}
}
