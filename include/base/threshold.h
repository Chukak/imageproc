#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "interface/operation.h"
#include "interface/operationtype.h"
#include "interface/thresholdinterface.h"

enum THRESHOLD_TYPE : OperationType::type_t
{
	THRESHOLD_BINARY = 0,
	THRESHOLD_BINARY_INVERTED = 1,
	THRESHOLD_TRUNCATED = 2,
	THRESHOLD_TO_ZERO = 3,
	THRESHOLD_TO_ZERO_INVERTED = 4
};

class Threshold
    : public Operation
    , public OperationType
    , public ThresholdInterface
{
public:
	explicit Threshold(COMMON_CLASS_TYPE t, cv::Mat&& src, bool gray = false);

public:
	void run() final;

	DECL_OT_PARAMS_VAR

private:
	bool is_gray{false};
};

#endif // THRESHOLD_H
