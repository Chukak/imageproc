#ifndef PARSERBLUR_T_H
#define PARSERBLUR_T_H

#include "settings/parser/internal/parser.h"

class ParserBlur_t : public Parser
{
public:
    explicit ParserBlur_t(int argc, char** argv, Wrapper* w);
    void parse() noexcept final;
};

#endif // PARSERBLUR_T_H
