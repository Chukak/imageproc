#ifndef SHOW_H
#define SHOW_H

#include "interface/operation.h"

class Show : public Operation
{
public:
    explicit Show(const char * path);
    void run() final {}
};

#endif // SHOW_H
