#ifndef PARSERSHOW_T_H
#define PARSERSHOW_T_H

#include "settings/parser/internal/parser.h"

class ParserShow_t : public Parser
{
public:
    explicit ParserShow_t(int argc, char** argv, Wrapper* w);
    void parse() noexcept final;
};

#endif // PARSERSHOW_T_H
