#ifndef PARSERTHRESHOLD_T_H
#define PARSERTHRESHOLD_T_H

#include "settings/parser/internal/parser.h"

class ParserThreshold_t : public Parser
{
public:
    explicit ParserThreshold_t(int argc, char** argv, Wrapper* w);
    void parse() noexcept final;

private:
   bool find_value() const noexcept;
};

#endif // PARSERTHRESHOLD_T_H