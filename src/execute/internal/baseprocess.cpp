#include "execute/internal/baseprocess.h"
#include "base/blur.h"
#include "base/show.h"
#include "base/threshold.h"
#include "base/linearfilter.h"
#include <utility>

using namespace std;

template<typename C>
set_type_process<C>::set_type_process(C *obj[[maybe_unused]], BaseProcess *b)
{
    if (is_same<C, Blur>::value) {
        b->t = BaseProcess::Blur_t;
    } else if (is_same<C, Show>::value) {
        b->t = BaseProcess::Show_t;
    } else if (is_same<C, Threshold>::value) {
        b->t = BaseProcess::Threshold_t;
    } else if (is_same<C, LinearFilter>::value) {
        b->t = BaseProcess::LinearFilter_t;
    } else {
        b->t = BaseProcess::Invalid;
    }
}

template class set_type_process<Blur>;
template class set_type_process<Show>;
template class set_type_process<Threshold>;
template class set_type_process<LinearFilter>;
