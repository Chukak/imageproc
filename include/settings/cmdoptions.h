#ifndef CMDOPTIONS_H
#define CMDOPTIONS_H

#include "settings/internal/types.h"

namespace command_line
{
namespace options
{
static message_t HELP_OPTION("--help");
static message_t BLUR_OPTION("--blur");
static message_t THRESHOLD_OPTION("--threshold");
static message_t LINEAR_FILTER_OPTION("--linear-filter");
static message_t BRIGHT_EDGE_OPTION("--bright-edge");
static message_t REMAPPING_OPTION("--remapping");
static message_t HISTOGRAM_EQUALIZATION_OPTION("--histogram-equal");
static message_t SAVE_OPTION("--save");

namespace blur_opt
{
static message_t BLUR_TYPE("--type");
static message_t BLUR_POINT("--point-anchor");
static message_t BLUR_KERNEL_SIZE("--kernel-size");
static messages_t BLUR_TYPE_VALUES = {"gaussian", "median", "bilaterial"};
} // namespace blur_opt

namespace threshold_opt
{
static message_t THRESHOLD_TYPE("--type");
static message_t THRESHOLD_VALUE("--value");
static message_t THRESHOLD_GRAY("--gray");
static messages_t THRESHOLD_TYPE_VALUES = {"binary",
                                           "binary-inv",
                                           "truncated",
                                           "to-zero",
                                           "to-zero-inv"};
} // namespace threshold_opt

namespace linear_filter_opt
{
static message_t LINEAR_FILTER_KERNEL_SIZE("--kernel-size");
static message_t LINEAR_FILTER_ANCHOR("--anchor");
static message_t LINEAR_FILTER_DELTA("--delta");
} // namespace linear_filter_opt

namespace remapping_opt
{
static message_t REMAPPING_TYPE("--type");
static messages_t REMAPPING_TYPE_VALUES = {"upside-down",
                                           "x-direction",
                                           "both-direction"};
} // namespace remapping_opt

} // namespace options
} // namespace command_line

#endif // CMDOPTIONS_H
