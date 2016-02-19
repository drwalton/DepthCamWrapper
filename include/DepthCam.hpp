#ifndef DEPTHCAM_HPP_INCLUDED
#define DEPTHCAM_HPP_INCLUDED

#include <memory>
#include <string>
#include <exception>

class DepthCamException : std::runtime_error
{
public:
	DepthCamException(const std::string &what);
	virtual ~DepthCamException() throw();
};

class DepthCam
{
public:
	virtual ~DepthCam() throw();

	virtual void getLatestFrames() = 0;
	virtual const unsigned short *const depthFramePtr() const = 0;
	virtual const unsigned char  *const colorFramePtr() const = 0;
	virtual const unsigned short *const irFramePtr()    const = 0;

	virtual void startColor() = 0;
	virtual void stopColor() = 0;
	virtual void startDepth() = 0;
	virtual void stopDepth() = 0;
	virtual void startIr() = 0;
	virtual void stopIr() = 0;

	virtual size_t depthWidth() const = 0;
	virtual size_t depthHeight() const = 0;
	virtual size_t colorWidth() const = 0;
	virtual size_t colorHeight() const = 0;

	virtual void saveCalibrationImages(const std::string &filename);
protected:
	explicit DepthCam();
};

std::unique_ptr<DepthCam> openDefaultDepthCam();

#endif
