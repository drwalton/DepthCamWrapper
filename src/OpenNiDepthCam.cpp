#include "OpenNiDepthCam.hpp"

#include <OpenNi.h>
#include <opencv2/opencv.hpp>

struct OpenNiDepthCam::Impl
{
	openni::Device device;
	openni::VideoStream depth;
	openni::VideoStream color;
	openni::VideoStream ir;
	openni::VideoFrameRef depthFrame;
	openni::VideoFrameRef colorFrame;
	openni::VideoFrameRef irFrame;
	bool colorRunning;
	bool depthRunning;
	bool irRunning;

	void init(const std::string &uri)
	{
		openni::OpenNI::initialize();
		if (uri != std::string(""))
			device.open(uri.c_str());
		else
			device.open(openni::ANY_DEVICE);
		depth.create(device, openni::SENSOR_DEPTH);
		color.create(device, openni::SENSOR_COLOR);
		ir.create(device, openni::SENSOR_IR);

		openni::VideoMode dm = depth.getVideoMode();
		dm.setResolution(640, 480);
		depth.setMirroringEnabled(false);
		depth.setVideoMode(dm);

		openni::VideoMode cm = color.getVideoMode();
		cm.setResolution(640, 480);
		color.setMirroringEnabled(false);
		color.setVideoMode(cm);
		
		openni::VideoMode im = ir.getVideoMode();
		im.setResolution(640, 480);
		ir.setMirroringEnabled(false);
		ir.setVideoMode(im);

		depth.start();
		color.start();
		depthRunning = true;
		colorRunning = true;
		irRunning = false;
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
	if (pimpl_->depthRunning)
		pimpl_->depth.readFrame(&pimpl_->depthFrame);
	if (pimpl_->colorRunning)	
		pimpl_->color.readFrame(&pimpl_->colorFrame);
	if (pimpl_->irRunning)
		pimpl_->ir.readFrame(&pimpl_->irFrame);
}

const unsigned short *const OpenNiDepthCam::depthFramePtr() const
{
	return reinterpret_cast<const unsigned short*>(pimpl_->depthFrame.getData());
}

const unsigned char *const OpenNiDepthCam::colorFramePtr() const
{
	return reinterpret_cast<const unsigned char*>(pimpl_->colorFrame.getData());
}

const unsigned short *const OpenNiDepthCam::irFramePtr() const
{
	return reinterpret_cast<const unsigned short*>(pimpl_->irFrame.getData());
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

void OpenNiDepthCam::startColor()
{
	pimpl_->color.start();
	pimpl_->colorRunning = true;
}

void OpenNiDepthCam::stopColor()
{
	pimpl_->color.stop();
	pimpl_->colorRunning = false;
}
void OpenNiDepthCam::startDepth()
{
	pimpl_->depth.start();
	pimpl_->depthRunning = true;
}
void OpenNiDepthCam::stopDepth()
{
	pimpl_->depth.stop();
	pimpl_->depthRunning = false;
}
void OpenNiDepthCam::startIr()
{
	pimpl_->ir.start();
	pimpl_->irRunning = true;
}
void OpenNiDepthCam::stopIr()
{
	pimpl_->ir.stop();
	pimpl_->irRunning = false;
}

void OpenNiDepthCam::saveCalibrationImages(const std::string &basefilename)
{
	if (pimpl_->colorRunning) {
		pimpl_->color.readFrame(&pimpl_->colorFrame);
		pimpl_->color.stop();
		pimpl_->ir.start();
		pimpl_->ir.readFrame(&pimpl_->irFrame);
		pimpl_->ir.stop();
		pimpl_->color.start();
	}
	else {
		pimpl_->ir.stop();
		pimpl_->color.start();
		//Allow white balance to work for a few frames.
		for (size_t i = 0; i < 10; ++i) {
			pimpl_->color.readFrame(&pimpl_->colorFrame);
		}
		pimpl_->color.stop();
		pimpl_->ir.start();
		pimpl_->ir.readFrame(&pimpl_->irFrame);
	}
	cv::Mat irFrameIm(cv::Size(640, 480), CV_16UC1, 
		const_cast<void*>(pimpl_->irFrame.getData()));
	static cv::Mat scaleIrFrameIm(irFrameIm.size(), CV_32FC1);
	irFrameIm.convertTo(scaleIrFrameIm, CV_32FC1);
	//scaleIrFrameIm *= 255.f / float(USHRT_MAX);
	static cv::Mat ucharIrFrameIm(irFrameIm.size(), CV_8UC1);
	scaleIrFrameIm.convertTo(ucharIrFrameIm, CV_8UC1);
	cv::Mat colorFrameIm(cv::Size(640, 480), CV_8UC3, 
		const_cast<void*>(pimpl_->colorFrame.getData()));
	static cv::Mat colorFrameImBgr(colorFrameIm.size(), CV_8UC3);
	cv::cvtColor(colorFrameIm, colorFrameImBgr, CV_RGB2BGR);
	cv::imwrite(basefilename + "_color.png", colorFrameImBgr);
	cv::imwrite(basefilename + "_ir.png", ucharIrFrameIm);
}
