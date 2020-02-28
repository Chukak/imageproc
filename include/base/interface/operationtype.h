#ifndef OPERATIONTYPE_H
#define OPERATIONTYPE_H

#include <string>
#include <vector>
#include <cstdint>

class OperationType
{
public:
	using options_t = std::vector<std::string>;
	using types_t = std::vector<int8_t>;
	using type_t = int8_t;
	using params_t = struct
	{
		options_t options;
		types_t types;
		type_t default_type;
	};

public:
	static type_t parse_type(params_t params, const char* flag) noexcept;

protected:
	explicit OperationType(type_t t);

protected:
	type_t type{0};
};

using COMMON_CLASS_TYPE = OperationType::type_t;

#define DECL_OT_PARAMS_VAR                                                               \
public:                                                                                  \
	static OperationType::params_t OTParams;

#define CTOR_OPTIONS OperationType::options_t
#define CTOR_TYPES OperationType::types_t
#define CTOR_TYPE OperationType::type_t

#define DECL_OT_PARAMS(classname, options, types, default_type)                          \
	classname::params_t classname::OTParams = {options, types, default_type};

#endif // OPERATIONTYPE_H
