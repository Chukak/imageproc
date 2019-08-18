#ifndef PARSERLINEARFILTER_T_H
#define PARSERLINEARFILTER_T_H

#include "settings/parser/internal/parser.h"

class ParserLinearFilter_t : public Parser
{
public:
	explicit ParserLinearFilter_t(int argc, char** argv, Wrapper* w);
	void parse() noexcept final;
};

#endif // PARSERLINEARFILTER_T_H
