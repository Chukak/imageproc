#ifndef BASEPROCESS_H
#define BASEPROCESS_H

class BaseProcess
{
    template<typename C>
    friend struct set_type_process;
public:
    // all classes
    enum TypeObject
    {
        Blur_t,
        Show_t,
        Threshold_t,
        LinearFilter_t,
        DetectBrightEdge_t,
        Invalid
    };
public:
    BaseProcess() = default;
    template<typename O>
    explicit BaseProcess(O * obj);
    virtual ~BaseProcess() = default;
    BaseProcess(BaseProcess&&) = default;
    BaseProcess(const BaseProcess&) = default;

    BaseProcess& operator=(BaseProcess&&) = default;
    BaseProcess& operator=(const BaseProcess&) = default;

    inline TypeObject type() const noexcept { return t; }
private:
    TypeObject t{Invalid};
};

template<typename C>
struct set_type_process
{
    friend class BaseProcess;
private:
    explicit set_type_process(C *obj, BaseProcess *b);
};

template<typename O>
BaseProcess::BaseProcess(O * obj)
{
    set_type_process<O>(obj, this);
}

#endif // BASEPROCESS_H
