#ifndef KERNELSIZE_H
#define KERNELSIZE_H

#include <cstdint>

class KernelSize
{
public:
    void ks_set(int16_t k) noexcept;
    static bool ks_check(int16_t k) noexcept;
protected:
    explicit KernelSize() = default;
    explicit KernelSize(int16_t k);
protected:
    int16_t kernel_size{3};
};

#endif // KERNELSIZE_H
