#include "OpenNiDepthCam.hpp"

#include <OpenNi.h>

struct OpenNiDepthCam::Impl
{
	openni::Device device;
	openni::VideoStream depth;
	openni::VideoStream color;
	openni::VideoFrameRef depthFrame;
	openni::VideoFrameRef colorFrame;
};

OpenNiDepthCam::OpenNiDepthCam(const std::string &uri)
:pimpl_(new Impl())
{
	openni::OpenNI::initialize();
	pimpl_->device.open(uri.c_str());
	pimpl_->depth.create(pimpl_->device, openni::SENSOR_DEPTH);
	pimpl_->color.create(pimpl_->device, openni::SENSOR_COLOR);
	pimpl_->depth.start();
	pimpl_->color.start();
}

OpenNiDepthCam::~OpenNiDepthCam()
{}

void OpenNiDepthCam::getLatestFrames()
{
	pimpl_->depth.readFrame(&pimpl_->depthFrame);
	pimpl_->color.readFrame(&pimpl_->colorFrame);
}

const unsigned short *const OpenNiDepthCam::depthFramePtr() const
{
	return reinterpret_cast<const unsigned short*>(pimpl_->depthFrame.getData());
}

const unsigned char *const OpenNiDepthCam::colorFramePtr() const
{
	return reinterpret_cast<const unsigned char*>(pimpl_->colorFrame.getData());
}

size_t OpenNiDepthCam::depthWidth() const
{
	openni::VideoMode m = pimpl_->depth.getVideoMode();
	return m.getResolutionX();
}
size_t OpenNiDepthCam::depthHeight() const
{
	openni::VideoMode m = pimpl_->depth.getVideoMode();
	return m.getResolutionY();
}
size_t OpenNiDepthCam::colorWidth() const
{
	openni::VideoMode m = pimpl_->color.getVideoMode();
	return m.getResolutionX();

}
size_t OpenNiDepthCam::colorHeight() const
{
	openni::VideoMode m = pimpl_->color.getVideoMode();
	return m.getResolutionY();
}

