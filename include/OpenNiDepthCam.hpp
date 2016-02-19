#ifndef OPENNIDEPTHCAM_HPP_INCLUDED
#define OPENNIDEPTHCAM_HPP_INCLUDED

#include "DepthCam.hpp"
#include <memory>
#include <string>

class OpenNiDepthCam : public DepthCam
{
public:
	explicit OpenNiDepthCam();
	explicit OpenNiDepthCam(const std::string &uri);
	virtual ~OpenNiDepthCam() throw();

	virtual void getLatestFrames();
	virtual const unsigned short *const depthFramePtr() const;
	virtual const unsigned char  *const colorFramePtr() const;
	virtual const unsigned short *const irFramePtr() const;

	virtual size_t depthWidth() const;
	virtual size_t depthHeight() const;
	virtual size_t colorWidth() const;
	virtual size_t colorHeight() const;

	virtual void startColor();
	virtual void stopColor();
	virtual void startDepth();
	virtual void stopDepth();
	virtual void startIr();
	virtual void stopIr();

	virtual void saveCalibrationImages(const std::string &baseFilename);
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl_;
};

#endif
