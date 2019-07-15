#ifndef CMDOPTIONS_H
#define CMDOPTIONS_H

namespace command_line
{
namespace options
{

constexpr const char * HELP_OPTION("--help");
constexpr const char * BLUR_OPTION("--blur");
constexpr const char * SAVE_OPTION("--save");

namespace blur_opt
{

constexpr const char * BLUR_TYPE("--type");
constexpr const char * BLUR_POINT("--point-anchor");
constexpr const char * BLUR_TYPES[] = {"gaussian",
                                       "median",
                                       "bilaterial"};

}

}
}

#endif // CMDOPTIONS_H
