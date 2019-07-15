#include "base/show.h"
#include <opencv2/imgcodecs.hpp>

Show::Show(const char * path)
{
    result = cv::imread(path, -1);
    ok = !result.empty();
}
