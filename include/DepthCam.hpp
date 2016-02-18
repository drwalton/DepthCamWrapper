#ifndef DEPTHCAM_HPP_INCLUDED
#define DEPTHCAM_HPP_INCLUDED

#include <memory>

class DepthCam
{
public:
	virtual ~DepthCam() throw();

	virtual void getLatestFrames() = 0;
	virtual const unsigned short *const depthFramePtr() const = 0;
	virtual const unsigned char  *const colorFramePtr() const = 0;

	virtual size_t depthWidth() const = 0;
	virtual size_t depthHeight() const = 0;
	virtual size_t colorWidth() const = 0;
	virtual size_t colorHeight() const = 0;
protected:
	explicit DepthCam();
};

std::unique_ptr<DepthCam> openDefaultDepthCam();

#endif
