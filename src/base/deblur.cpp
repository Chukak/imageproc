#include "base/deblur.h"
#include "settings/cmdoptions.h"
#include "functions/default.h"
#include <opencv2/imgproc.hpp>
#include <iostream>

static const cv::Scalar CIRCLE_COLOR_DEFAULT(255);

OperationType::options_t Deblur::options = {
    command_line::options::deblur_opt::DEBLUR_TYPE_VALUES[0],
    command_line::options::deblur_opt::DEBLUR_TYPE_VALUES[1]};

OperationType::types_t Deblur::types = {DEBLUR_OUT_OF_FOCUS, DEBLUR_MOTION};

OperationType::type_t Deblur::default_type = DEBLUR_OUT_OF_FOCUS;

Deblur::Deblur(COMMON_CLASS_TYPE t, cv::Mat&& src) :
		Operation(std::forward<cv::Mat>(src)), OperationType(t)
{}

void Deblur::run()
{
	switch(static_cast<DEBLUR_TYPE>(type)) {
	case DEBLUR_OUT_OF_FOCUS: {
		cv::cvtColor(source, source, cv::COLOR_BGR2GRAY);
		cv::Rect roi(0, 0, source.cols & -2, source.rows & -2);
		{
			cv::Size size(roi.size());
			cv::Mat ioMat(size, CV_32F, cv::Scalar(0));
			cv::circle(ioMat, {size.width / 2, size.height / 2}, radius, CIRCLE_COLOR_DEFAULT);
			cv::Mat psfHMat = ioMat / cv::sum(ioMat)[0];

			cv::Mat outputDiv;
			{
				cv::Mat filterOut, fftShifted, complex, denom;
				functions::fft_shift(psfHMat, fftShifted);

				cv::Mat planes[2];
				try {
					planes[0] = cv::Mat_<float>(fftShifted.clone());
					planes[1] = cv::Mat::zeros(fftShifted.size(), CV_32F);
				} catch(const cv::Exception& e) {
					ok = false;
					std::cerr << "OpenCV Exception: " << e.what() << std::endl;
					return;
				}
				cv::merge(planes, 2, complex);
				cv::dft(complex, complex);
				cv::split(complex, planes);

				cv::pow(cv::abs(planes[0]), 2, denom);
				denom += 1.0 / static_cast<double>(snr_value);
				cv::divide(planes[0], denom, outputDiv);
			}

			{
				const cv::Mat& inputMat = source(roi);
				cv::Mat planes[2];
				try {
					planes[0] = cv::Mat_<float>(inputMat.clone());
					planes[1] = cv::Mat::zeros(inputMat.size(), CV_32F);
				} catch(const cv::Exception& e) {
					ok = false;
					std::cerr << "OpenCV Exception: " << e.what() << std::endl;
					return;
				}

				cv::Mat complex, complexH1, complexH2;
				cv::merge(planes, 2, complex);
				cv::dft(complex, complex, cv::DFT_SCALE);

				cv::Mat planesH[2] = {cv::Mat_<float>(outputDiv.clone()),
															cv::Mat::zeros(outputDiv.size(), CV_32F)};

				cv::merge(planesH, 2, complexH1);
				cv::mulSpectrums(complex, complexH1, complexH2, 0);
				cv::idft(complexH2, complexH2);

				cv::split(complexH2, planes);
				result = planes[0];
			}
		}
		result.convertTo(result, CV_8U);
		cv::normalize(result, result, 0, 255, cv::NORM_MINMAX);
		break;
	}
	case DEBLUR_MOTION:
		break;
	}
	ok = !result.empty();
}
