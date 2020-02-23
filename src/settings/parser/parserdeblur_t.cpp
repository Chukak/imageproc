#include "settings/parser/parserdeblur_t.h"
#include "base/deblur.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"

namespace opts = command_line::options::deblur_opt;

ParserDeblur_t::ParserDeblur_t(int argc, char** argv, Wrapper* w) : Parser(argc, argv, w)
{}

void ParserDeblur_t::parse() noexcept
{
	COMMON_CLASS_TYPE type(DEBLUR_OUT_OF_FOCUS);
	int r = 0, snr = 0;
	while(++index < argc) {
		if(argv[index] == opts::DEBLUR_RADIUS) {
			if(argc - index > 1) {
				r = std::atoi(argv[++index]);
				continue;
			}
			add_error(msg::deblur::DEBLUR_RADIUS_MSG);
		} else if(argv[index] == opts::DEBLUR_SNR) {
			if(argc - index > 1) {
				snr = std::atoi(argv[++index]);
				continue;
			}
			add_error(msg::deblur::DEBLUR_SNR_MSG);
		} else if(argv[index] == opts::DEBLUR_TYPE) {
			if(argc - index++ > 1) {
				if(find_in(opts::DEBLUR_TYPE_VALUES)) {
					type = Deblur::parse_type(argv[index]);
				} else {
					add_error(msg::deblur::DEBLUR_TYPE_MSG);
					break;
				}
				continue;
			}
			add_error(msg::deblur::SET_DEBLUR_TYPE_MSG);
		}
		break;
	}
	set_save_path();
	cv::Mat frame;
	set_image(frame);
	if(!bad) {
		auto deblur = new Deblur(type, std::move(frame));
		if(r > 0) {
			deblur->snr_set_radius(r);
		}
		if(snr > 0) {
			deblur->snr_set(snr);
		}
		set_process(deblur);
	}
}
