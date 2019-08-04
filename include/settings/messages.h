#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>

inline void printm(const char * msg) noexcept
{
    std::cout << msg << std::endl;
}

inline void printe(const char * msg) noexcept
{
    std::cerr << msg << std::endl;
}

namespace msg
{

// todo
constexpr const char * HELP_MSG
("Usage: " PROGRAM_NAME " [method] [option (value)]... [--save /path/to/saved/image] /path/to/image \n"
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
 "    --save /path/to/image                                                                     Save image to file.\n"
 "\n");
// todo
constexpr const char * IMG_NOT_FOUND_MSG("Image '' not found!");
constexpr const char* SET_SAVE_PATH_MSG("Please set path to saved image!");

namespace  blur
{
constexpr const char * SET_X_Y_MSG("Please set the X and Y position of point.");
constexpr const char * BLUR_TYPE_MSG("Incorrect blur type. Avaliable types: [gaussian, median, bilatetial].");
constexpr const char * SET_BLUR_TYPE_MSG("Please add a blur type.");
}

namespace  threshold
{
constexpr const char * THRESHOLD_TYPE_MSG("Incorrect threshold type. Available types: [binary, binary-inv, truncated, to-zero, to-zero-inv].");
constexpr const char * THRESHOLD_VALUE_MSG("Threshold value must be in range 0-255.");
constexpr const char * SET_THRESHOLD_TYPE_MSG("Please add a threshold type.");
}

namespace linear_filter
{
constexpr const char * LINEAR_FILTER_KERNEL_SIZE_MSG("Incorrect kernel size. Kernel size must be: [1x1, 3x3, ... 127x127].");
constexpr const char * SET_LINEAR_FILTER_KERNEL_SIZE_MSG("Please add a kernel size value.");
constexpr const char * SET_LINEAR_FILTER_DELTA_MSG("Please add a delta value.");
constexpr const char * SET_X_Y_MSG("Please set the X and Y position of point.");
}
}

#endif // MESSAGES_H
