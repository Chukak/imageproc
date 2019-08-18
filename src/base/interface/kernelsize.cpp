#include "base/interface/kernelsize.h"

KernelSize::KernelSize(int16_t k) : kernel_size(k)
{}

void KernelSize::ks_set(int16_t k) noexcept
{
	kernel_size = k;
}

bool KernelSize::ks_check(int16_t k) noexcept
{
	return (k > 0 && k <= 127) && (k % 2 == 1);
}
