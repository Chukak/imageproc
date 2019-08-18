#include "settings/arguments.h"
#include "execute/wrapper.h"
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace command_line;

int main(int argc, char** argv)
{
    Wrapper w;
    Arguments args(argc, argv, &w);

    if (!args.valid) {
        std::cerr << "not valid\n";
        return 1;
    }

    if (args.finish) {
        std::cerr << "finish\n";
        return 0;
    }

    if (!w.exec()) {
         std::cerr << "false exec\n";
        return 1;
    }

    if (!args.save_path.empty()) {
        cv::imwrite(args.save_path, w.get());
    } else {
        cv::imshow("output", w.get());
        cv::waitKey();
    }

    return 0;
}
