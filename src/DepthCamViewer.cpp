#include "DepthCam.hpp"
#include <opencv2/opencv.hpp>

const float depthScale = 1.f / 4000.f; //float(UINT_MAX) / 4000.f;

enum Mode {IR, COLOR};
Mode mode = COLOR;

int main()
{
	std::unique_ptr<DepthCam> cam = openDefaultDepthCam();
	cv::namedWindow("Depth");
	cv::namedWindow("Color/IR");
	cv::moveWindow("Depth", 0, 0);
	cv::moveWindow("Color/IR", cam->depthWidth(), 0);

	cv::Mat bgrColor(cam->colorHeight(), cam->colorWidth(), CV_8UC3);
	cv::Mat sclDepth(cam->depthHeight(), cam->depthWidth(), CV_32FC1);
	cv::Mat sclIr(cam->depthHeight(), cam->depthWidth(), CV_32FC1);

	int currCalibNo = 0;

	int key = 0;
	while (key != 27) {
		cam->getLatestFrames();
		cv::Mat depth(cam->depthHeight(), cam->depthWidth(), CV_16UC1, const_cast<unsigned short*>(cam->depthFramePtr()));
		depth.convertTo(sclDepth, CV_32FC1);
		sclDepth *= depthScale;
		cv::imshow("Depth", sclDepth);
		if (mode == COLOR) {
			cv::Mat color(cam->colorHeight(), cam->colorWidth(), CV_8UC3, const_cast<unsigned char *>(cam->colorFramePtr()));
			cv::cvtColor(color, bgrColor, CV_RGB2BGR);
			cv::imshow("Color/IR", bgrColor);
		} else /*mode == IR*/ {
			cv::Mat ir(cam->depthHeight(), cam->depthWidth(), CV_16UC1, const_cast<unsigned short*>(cam->irFramePtr()));
			ir.convertTo(sclIr, CV_32FC1);
			sclIr /= 255.f;
			cv::imshow("Color/IR", sclIr);
		}
		key = cv::waitKey(33);

		if (key == 'c') {
			cam->saveCalibrationImages(std::to_string(currCalibNo));
			++currCalibNo;
		}
		if (key == 'm') {
			if (mode == IR) {
				cam->stopIr();
				cam->startColor();
				mode = COLOR;
			} else /*mode == COLOR*/ {
				cam->stopColor();
				cam->startIr();
				mode = IR;
			}
		}
	}

	return 0;
}
