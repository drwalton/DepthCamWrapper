#include "DepthCam.hpp"
#include <opencv2/opencv.hpp>

const float depthScale = 1.f / 4000.f; //float(UINT_MAX) / 4000.f;

int main()
{
	std::unique_ptr<DepthCam> cam = openDefaultDepthCam();
	cv::namedWindow("Depth");
	cv::namedWindow("Color");
	cv::moveWindow("Depth", 0, 0);
	cv::moveWindow("Color", cam->depthWidth(), 0);

	cv::Mat bgrColor(cam->colorHeight(), cam->colorWidth(), CV_8UC3);
	cv::Mat sclDepth(cam->depthHeight(), cam->depthWidth(), CV_32FC1);

	while (cv::waitKey(1) != 27) {
		cam->getLatestFrames();
		cv::Mat depth(cam->depthHeight(), cam->depthWidth(), CV_16UC1, const_cast<unsigned short*>(cam->depthFramePtr()));
		cv::Mat color(cam->colorHeight(), cam->colorWidth(), CV_8UC3, const_cast<unsigned char *>(cam->colorFramePtr()));
		cv::cvtColor(color, bgrColor, CV_RGB2BGR);
		depth.convertTo(sclDepth, CV_32FC1);
		sclDepth *= depthScale;
		cv::imshow("Depth", sclDepth);
		cv::imshow("Color", bgrColor);
	}

	return 0;
}
