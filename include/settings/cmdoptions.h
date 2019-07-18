#ifndef CMDOPTIONS_H
#define CMDOPTIONS_H

namespace command_line
{
namespace options
{

constexpr const char * HELP_OPTION("--help");
constexpr const char * BLUR_OPTION("--blur");
constexpr const char * THRESHOLD_OPTION("--threshold");
constexpr const char * SAVE_OPTION("--save");

namespace blur_opt
{
constexpr const char * BLUR_TYPE("--type");
constexpr const char * BLUR_POINT("--point-anchor");
constexpr const char * BLUR_TYPE_VALUES[] = {"gaussian",
                                             "median",
                                             "bilaterial"};
}

namespace  threshold_opt
{
constexpr const char * THRESHOLD_TYPE("--type");
constexpr const char * THRESHOLD_VALUE("--value");
constexpr const char * THRESHOLD_GRAY("--gray");
constexpr const char * THRESHOLD_TYPE_VALUES[] = {"binary",
                                                  "binary-inv",
                                                  "truncated",
                                                  "to-zero",
                                                  "to-zero-inv"};
}

}
}

#endif // CMDOPTIONS_H
