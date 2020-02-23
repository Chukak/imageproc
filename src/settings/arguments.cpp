#include "settings/arguments.h"
#include "settings/cmdoptions.h"
#include "settings/messages.h"
#include "execute/wrapper.h"
#include "settings/parser/parserblur_t.h"
#include "settings/parser/parserlinearfilter_t.h"
#include "settings/parser/parsershow_t.h"
#include "settings/parser/parserthreshold_t.h"
#include "settings/parser/parserdetectbrightedge_t.h"
#include "settings/parser/parserremapping_t.h"
#include "settings/parser/parserhistogramequalization_t.h"
#include "settings/parser/parserdrawcontours_t.h"
#include "settings/parser/parserdeblur_t.h"

using namespace command_line;

Arguments::Arguments(int argc, char** argv, Wrapper* w)
{
	valid = argc > 1;
	if(valid) {
		for(auto c = 1; c < argc; ++c) {
			if(argv[c] == options::HELP_OPTION) {
				show_help();
				finish = true;
			} else {
				ParserWrapper pw(save_path, finish, errors);
				pw.set_args(argc, argv, w);
				if(argv[c] == options::BLUR_OPTION) {
					pw.run<ParserBlur_t>();
				} else if(argv[c] == options::THRESHOLD_OPTION) {
					pw.run<ParserThreshold_t>();
				} else if(argv[c] == options::LINEAR_FILTER_OPTION) {
					pw.run<ParserLinearFilter_t>();
				} else if(argv[c] == options::BRIGHT_EDGE_OPTION) {
					pw.run<ParserDetectBrightEdge_t>();
				} else if(argv[c] == options::REMAPPING_OPTION) {
					pw.run<ParserRemapping_t>();
				} else if(argv[c] == options::HISTOGRAM_EQUALIZATION_OPTION) {
					pw.run<ParserHistogramEqualization_t>();
				} else if(argv[c] == options::DRAW_CONTOURS_OPTION) {
					pw.run<ParserDrawContours_t>();
				} else if(argv[c] == options::DEBLUR_OPTION) {
					pw.run<ParserDeblur_t>();
				} else {
					pw.run<ParserShow_t>();
				}
				if(finish) {
					print_errors();
				}
			}
			break;
		}
	} else {
		show_help();
	}
}

void Arguments::print_errors() const noexcept
{
	for(const std::string& e : errors) {
		printe(e.c_str());
	}
}

void command_line::show_help() noexcept
{
	printm(msg::HELP_MSG);
}
