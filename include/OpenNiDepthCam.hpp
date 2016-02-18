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

	virtual size_t depthWidth() const;
	virtual size_t depthHeight() const;
	virtual size_t colorWidth() const;
	virtual size_t colorHeight() const;
private:
	struct Impl;
	std::unique_ptr<Impl> pimpl_;
};

#endif
