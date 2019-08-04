#include "settings/parser/detectbrightedge_t.h"
#include "base/detectbrigthedge.h"

DetectBrightEdge_t::DetectBrightEdge_t(int argc, char** argv, Wrapper* w) :
    Parser(argc, argv, w)
{
}

void DetectBrightEdge_t::parse() noexcept
{
   ++index;
    check_save_path();
    cv::Mat frame;
    bool ok;
    set_image(frame, ok);
    if (ok) {
        auto bright_edge = new DetectBrigthEdge(std::move(frame));
        set_process(bright_edge, &DetectBrigthEdge::run);
    }
}
