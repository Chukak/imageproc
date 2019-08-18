#ifndef OPERATION_H
#define OPERATION_H

#include <opencv2/core/mat.hpp>

// in future
#define INIT_REF_CTORS_DEFAULT(name)                                                     \
	name(name&&) = default;                                                                \
	name(const name&) = default;                                                           \
	name& operator=(name&&) = default;                                                     \
	name& operator=(const name&) = default;

#define INIT_REF_CTORS_DEELETE(name)                                                     \
	name(name&&) = delete;                                                                 \
	name(const name&) = delete;                                                            \
	name& operator=(name&&) = delete;                                                      \
	name& operator=(const name&) = delete;

class Operation
{
public:
	bool good() const noexcept { return ok; }
	virtual void run() = 0;

public:
	cv::Mat result{};

protected:
	explicit Operation() = default;
	explicit Operation(cv::Mat&& src);
	INIT_REF_CTORS_DEFAULT(Operation)
public:
	virtual ~Operation() = default;

protected:
	bool ok{true};
	cv::Mat source{};
};

#endif // OPERATION_H
