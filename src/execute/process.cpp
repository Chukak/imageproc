#include "execute/process.h"
#include "base/blur.h"
#include "base/show.h"
#include "base/threshold.h"
#include "base/linearfilter.h"
#include "base/detectbrigthedge.h"
#include "base/remapping.h"


template<class C>
Process<C>::Process(C * obj, void (C::*fn)()) :
    BaseProcess(obj),
    object(obj),
    method(fn)
{    
}

template<class C>
void Process<C>::set_data(C * obj, void (C::*fn)()) noexcept
{

}

template<class C>
void Process<C>::exec() noexcept
{
    method(object.get());
}

template class Process<Blur>;
template class Process<Show>;
template class Process<Threshold>;
template class Process<LinearFilter>;
template class Process<DetectBrigthEdge>;
template class Process<Remapping>;
