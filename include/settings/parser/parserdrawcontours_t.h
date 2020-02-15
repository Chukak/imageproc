#ifndef PARSERDRAWCONTOURS_T
#define PARSERDRAWCONTOURS_T

#include "settings/parser/internal/parser.h"

class ParserDrawContours_t : public Parser
{
public:
	explicit ParserDrawContours_t(int argc, char** argv, Wrapper* w);
	void parse() noexcept final;
};

#endif // PARSERDRAWCONTOURS_T
