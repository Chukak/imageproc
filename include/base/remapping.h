#ifndef REMAPPING_H
#define REMAPPING_H

#include "interface/operation.h"
#include "interface/operationtype.h"

enum REMAPPING_TYPE : OperationType::type_t
{
	REMAPPING_UPSIDE_DOWN,
	REMAPPING_X_DIRECTION,
	REMAPPING_BOTH_DIRECTION
};

class Remapping
    : public Operation
    , public OperationType
{
public:
	Remapping(COMMON_CLASS_TYPE t, cv::Mat&& src);

public:
	void run() final;

private:
	OT_VARIABLES
};

#endif // REMAPPING_H
