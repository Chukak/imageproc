#include "settings/parser/parserdetectbrightedge_t.h"
#include "base/detectbrigthedge.h"

ParserDetectBrightEdge_t::ParserDetectBrightEdge_t(int argc, char** argv, Wrapper* w) :
    Parser(argc, argv, w)
{
}

void ParserDetectBrightEdge_t::parse() noexcept
{
   ++index;
    set_save_path();
    cv::Mat frame;
    set_image(frame);
    if (!bad) {
        auto bright_edge = new DetectBrigthEdge(std::move(frame));
        set_process(bright_edge);
    }
}
