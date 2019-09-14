#ifndef PARSERHISTOGRAMEQUALIZATION_T_H
#define PARSERHISTOGRAMEQUALIZATION_T_H

#include "settings/parser/internal/parser.h"

class ParserHistogramEqualization_t : public Parser
{
public:
	explicit ParserHistogramEqualization_t(int argc, char** argv, Wrapper* w);
	void parse() noexcept final;
};

#endif // PARSERHISTOGRAMEQUALIZATION_T_H
