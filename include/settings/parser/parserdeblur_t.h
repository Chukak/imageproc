#ifndef PARSERDEBLUR_T_H
#define PARSERDEBLUR_T_H

#include "settings/parser/internal/parser.h"

class ParserDeblur_t : public Parser
{
public:
	explicit ParserDeblur_t(int argc, char** argv, Wrapper* w);
	void parse() noexcept final;
};

#endif // PARSERDEBLUR_T_H
