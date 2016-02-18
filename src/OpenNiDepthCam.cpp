#include "OpenNiDepthCam.hpp"

#include <OpenNi.h>

struct OpenNiDepthCam::Impl
{
	openni::Device device;
	openni::VideoStream depth;
	openni::VideoStream color;
	openni::VideoFrameRef depthFrame;
	openni::VideoFrameRef colorFrame;

	void init(const std::string &uri)
	{
		openni::OpenNI::initialize();
		if (uri != std::string(""))
			device.open(uri.c_str());
		else
			device.open(openni::ANY_DEVICE);
		depth.create(device, openni::SENSOR_DEPTH);
		color.create(device, openni::SENSOR_COLOR);

		openni::VideoMode dm = depth.getVideoMode();
		dm.setResolution(640, 480);
		depth.setMirroringEnabled(false);
		depth.setVideoMode(dm);

		openni::VideoMode cm = color.getVideoMode();
		cm.setResolution(640, 480);
		color.setMirroringEnabled(false);
		color.setVideoMode(cm);
		
		depth.start();
		color.start();
	}
};

OpenNiDepthCam::OpenNiDepthCam(const std::string &uri)
:pimpl_(new Impl())
{
	pimpl_->init(uri);
}

OpenNiDepthCam::OpenNiDepthCam()
: pimpl_(new Impl())
{
	pimpl_->init("");
}

OpenNiDepthCam::~OpenNiDepthCam()
{
	pimpl_->depth.stop();
	pimpl_->color.stop();
	pimpl_->depth.destroy();
	pimpl_->color.destroy();
	openni::OpenNI::shutdown();
}

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

