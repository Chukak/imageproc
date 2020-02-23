#ifndef SNRINTERFACE_H
#define SNRINTERFACE_H

#include <cstdint>

class SNRInterface
{
public:
	void snr_set_radius(int16_t r) noexcept;
	void snr_set(int32_t snr) noexcept;

protected:
	explicit SNRInterface() = default;

protected:
	int16_t radius{0};
	int32_t snr_value{0};
};

#endif // SNRINTERFACE_H
