#include "settings/parser/parsershow_t.h"
#include "base/show.h"

ParserShow_t::ParserShow_t(int argc, char** argv, Wrapper* w) : Parser(argc, argv, w)
{}

void ParserShow_t::parse() noexcept
{
	set_save_path();
	auto show = new Show(argv[index]);
	set_process(show);
}
