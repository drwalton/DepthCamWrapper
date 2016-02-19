#include "DepthCam.hpp"
#include "OpenNiDepthCam.hpp"

DepthCamException::DepthCamException(const std::string &what)
:std::runtime_error(what.c_str())
{}

DepthCamException::~DepthCamException() throw()
{}

DepthCam::DepthCam()
{}

DepthCam::~DepthCam() throw()
{}

std::unique_ptr<DepthCam> openDefaultDepthCam()
{
	return std::unique_ptr<DepthCam>(new OpenNiDepthCam());
}

void DepthCam::saveCalibrationImages(const std::string &filename)
{
	throw DepthCamException(
		"saveCalibrationImages() not implemented for this DepthCam implementation.");
}
