#include "base/interface/operationtype.h"
#include <algorithm>

int8_t OperationType::parse_type(params_t params, const char *flag) noexcept
{
	auto it = std::find(params.options.begin(), params.options.end(), flag);
	return it != params.options.end()
						 ? params.types[std::distance(params.options.begin(), it)]
						 : params.default_type;
}

OperationType::OperationType(type_t t) : type(t)
{}
