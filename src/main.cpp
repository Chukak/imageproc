#include "settings/arguments.h"
#include "execute/wrapper.h"
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace command_line;

int main(int argc, char** argv)
{
    Wrapper w;
    Arguments args(argc, argv, &w);

    if (!args.is_valid()) {
        std::cerr << "not valid\n";
        return 1;
    }

    if (args.is_finish()) {
        std::cerr << "finish\n";
        return 0;
    }

    if (!w.run_exec()) {
         std::cerr << "false exec\n";
        return 1;
    }

    if (args.has_save_path()) {
        cv::imwrite(args.saved_image_name(), w.get_result());
    } else {
        cv::imshow("output", w.get_result());
        cv::waitKey();
    }

    return 0;
}
