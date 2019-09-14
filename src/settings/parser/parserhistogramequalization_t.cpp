#include "../../../include/settings/parser/parserhistogramequalization_t.h"
#include "base/histogramequalization.h"

ParserHistogramEqualization_t::ParserHistogramEqualization_t(int argc,
                                                             char **argv,
                                                             Wrapper *w) :
    Parser(argc, argv, w)
{}

void ParserHistogramEqualization_t::parse() noexcept
{
	++index;
	set_save_path();
	cv::Mat frame;
	set_image(frame);
	if(!bad) {
		auto histogram_equalization = new HistogramEqualization(std::move(frame));
		set_process(histogram_equalization);
	}
}
