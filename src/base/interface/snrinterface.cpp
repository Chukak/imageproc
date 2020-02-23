#include "base/interface/snrinterface.h"

void SNRInterface::snr_set(int32_t snr) noexcept
{
	snr_value = snr;
}

void SNRInterface::snr_set_radius(int16_t r) noexcept
{
	radius = r;
}
