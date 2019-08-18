#ifndef OPERATIONTYPE_H
#define OPERATIONTYPE_H

#include <string>
#include <vector>
#include <cstdint>

#define OT_VARIABLES \
    static options_t options; \
    static types_t types; \
    static type_t default_type; \

class OperationType
{
public:
    using options_t = std::vector<std::string>;
    using types_t = std::vector<int8_t>;
    using type_t = int8_t;
public:
    static type_t parse_type(const char* flag) noexcept;
protected:
    static options_t options;
    static types_t types;
    static type_t default_type;
protected:
    explicit OperationType(type_t t);
protected:
    type_t type{0};
};

using COMMON_CLASS_TYPE = OperationType::type_t;

#endif // OPERATIONTYPE_H
