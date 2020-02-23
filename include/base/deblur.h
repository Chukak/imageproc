#ifndef DEBLUR_H
#define DEBLUR_H

#include "interface/operation.h"
#include "interface/operationtype.h"
#include "interface/snrinterface.h"

enum DEBLUR_TYPE : OperationType::type_t
{
	DEBLUR_OUT_OF_FOCUS,
	DEBLUR_MOTION
};

class Deblur
    : public Operation
    , public OperationType
    , public SNRInterface
{
public:
  explicit Deblur(COMMON_CLASS_TYPE t, cv::Mat&& src);

public:
  void run() final;

private:
  OT_VARIABLES
};

#endif // DEBLUR_H
