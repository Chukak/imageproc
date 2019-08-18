#ifndef PARSEREMAPPING_T_H
#define PARSEREMAPPING_T_H

#include "settings/parser/internal/parser.h"

class ParserRemapping_t : public Parser
{
public:
    explicit ParserRemapping_t(int argc, char** argv, Wrapper* w);
    void parse() noexcept final;
};

#endif // PARSEREMAPPING_T_H
