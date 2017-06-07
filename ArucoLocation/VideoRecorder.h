#ifndef VIDEORECORDER_H_
#define VIDEORECORDER_H_

#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

using namespace std;
using namespace cv;


class VideoRecorder
{
private:
	void init();
	VideoWriter* outputVideo; 
	string zmienna;

public:
	VideoRecorder(void);
	~VideoRecorder(void);

	void StartRecord(string sFileName);
	void Record(Mat frame);
	void EndRecord();
};

#endif /* VIDEORECORDER_H_ */