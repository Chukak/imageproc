#ifndef message_tS_H
#define message_tS_H

#include "settings/internal/types.h"
#include <iostream>

inline void printm(message_t msg) noexcept
{
	std::cout << msg << std::endl;
}

inline void printe(message_t msg) noexcept
{
	std::cerr << msg << std::endl;
}

namespace msg
{
// clang-format off
static message_t HELP_MSG(
    "Usage: " PROGRAM_NAME
    " [method] [option (value)]... [--save /path/to/saved/image] /path/to/image \n"
    "Methods: \n"
    "    --help                                                                                    Show this information.\n"
    "    --blur [--type (blur type)] [--point-anchor (x) (y)]                                      Smoothing image. \n"
    "                                                                                              Blur types: [gaussian, median, bilaterial].\n"
    "                                                                                              Anchor point only for original blur (without type).\n"
    "    --threshold [--type (threshold type)] [--gray] [--value (0-255)]                          Threshold image. \n"
    "                                                                                              Threshold type: [binary, binary-inv, truncated, to-zero, to-zero-inv].\n"
    "                                                                                              Threshold value is number in range 0-255. \n"
    "                                                                                              Convert image to graysale before processing: --gray. \n"
    "    --linear-filter [--kernel-size (size)] [--anchor (x) (y)] [--delta (v)]                   Filter the image. \n"
    "                                                                                              Kernel size is: 1(1x1), 3(3x3), 5(5x5), ... 127(127x127). \n"
    "                                                                                              Delta - what value will be added to each pixel of image. \n"
    "                                                                                              Anchor - point relative of the kernel. \n"
    "    --bright-edge                                                                             Detect bright edges on image. \n"
    "    --remapping [--type (remapping type)]                                                     Remapping image.\n"
    "                                                                                              Remapping type: [upside-down, x-direction, both-direction].\n"
    "    --save /path/to/image                                                                     Save image to file.\n"
    "\n");
// clang-format on
static const std::string IMG_NOT_FOUND_MSG("Image '' not found!");
static message_t SET_SAVE_PATH_MSG("Please set path to saved image!");

namespace blur
{
static message_t SET_X_Y_MSG("Please set the X and Y position of point.");
static message_t BLUR_TYPE_MSG(
    "Incorrect blur type. Avaliable types: [gaussian, median, bilatetial].");
static message_t SET_BLUR_TYPE_MSG("Please add a blur type.");
static message_t SET_BLUR_KERNEL_SIZE_MSG("Please add a kernel size value.");
static message_t BLUR_KERNEL_SIZE_MSG(
    "Incorrect kernel size. Kernel size must be: [1x1, 3x3, ... 127x127].");
} // namespace blur

namespace threshold
{
static message_t THRESHOLD_TYPE_MSG("Incorrect threshold type. Available types: [binary, "
                                    "binary-inv, truncated, to-zero, "
                                    "to-zero-inv].");
static message_t THRESHOLD_VALUE_MSG("Threshold value must be in range 0-255.");
static message_t SET_THRESHOLD_TYPE_MSG("Please add a threshold type.");
} // namespace threshold

namespace linear_filter
{
static message_t LINEAR_FILTER_KERNEL_SIZE_MSG(
    "Incorrect kernel size. Kernel size must be: [1x1, 3x3, ... 127x127].");
static message_t SET_LINEAR_FILTER_KERNEL_SIZE_MSG("Please add a kernel size value.");
static message_t SET_LINEAR_FILTER_DELTA_MSG("Please add a delta value.");
static message_t SET_X_Y_MSG("Please set the X and Y position of point.");
} // namespace linear_filter

namespace remapping
{
static message_t REMAPPING_TYPE_MSG(
    "Incorrect remapping type. Available types: [upside-down, x-direction, "
    "both-direction].");
static message_t SET_REMAPPING_TYPE_MSG("Please add a remapping type.");
} // namespace remapping
} // namespace msg

#endif // message_tS_H
