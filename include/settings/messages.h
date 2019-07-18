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
("Usage: " PROGRAM_NAME " [method] [option (value)]... /path/to/image \n"
 "Methods: \n"
 "    --help                                                                            Show this information.\n"
 "    --blur [--type (blur type)] [--point-anchor (x) (y)]                              Smoothing image. \n"
 "                                                                                      Blur types: [gaussian, median, bilaterial].\n"
 "                                                                                      Anchor point only for original blur (without type).\n"
 "    --save /path/to/image                                                             Save image to file.\n"
 "\n");
// todo
constexpr const char * IMG_NOT_FOUND_MSG("Image '' not found!");

namespace  blur
{
constexpr const char * SET_X_Y_MSG("Please set the X and Y position of point");
constexpr const char * BLUR_TYPE_MSG("Incorrect blur type. Avaliable types: [gaussian, median, bilatetial]");
constexpr const char * SET_BLUR_TYPE_MSG("Please add a blut type.");
}

}

#endif // MESSAGES_H