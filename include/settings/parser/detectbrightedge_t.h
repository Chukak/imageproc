#ifndef DETECTBRIGHTEDGE_T_H
#define DETECTBRIGHTEDGE_T_H

#include "settings/parser/internal/parser.h"

class DetectBrightEdge_t : public Parser
{
public:
    explicit DetectBrightEdge_t(int argc, char** argv, Wrapper* w);
    void parse() noexcept final;
};

#endif // DETECTBRIGHTEDGE_T_H
