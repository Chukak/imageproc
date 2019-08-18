#include "base/interface/operationtype.h"
#include <algorithm>

OperationType::options_t OperationType::options;
OperationType::types_t OperationType::types;
OperationType::type_t OperationType::default_type = 0;

int8_t OperationType::parse_type(const char *flag) noexcept
{
	auto it = std::find(options.begin(), options.end(), flag);
	return it != options.end() ? types[std::distance(options.begin(), it)] : default_type;
}

OperationType::OperationType(type_t t) : type(t)
{}
