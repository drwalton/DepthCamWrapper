#include "DepthCam.hpp"
#include "OpenNiDepthCam.hpp"

DepthCam::DepthCam()
{}

DepthCam::~DepthCam() throw()
{}

std::unique_ptr<DepthCam> openDefaultDepthCam()
{
	return std::unique_ptr<DepthCam>(new OpenNiDepthCam());
}
