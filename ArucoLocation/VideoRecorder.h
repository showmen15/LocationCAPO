#ifndef VIDEORECORDER_H_
#define VIDEORECORDER_H_

#include <iostream>
#include <string>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <stdio.h>
#include <direct.h>

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

using namespace std;
using namespace cv;


//http://docs.opencv.org/2.4/doc/tutorials/highgui/video-write/video-write.html
//http://docs.opencv.org/trunk/dd/d9e/classcv_1_1VideoWriter.html

class VideoRecorder
{
private:
	VideoWriter* outputVideo; 

	int CodecType;
	double Fps;
	Size InputSize;

	bool recording;

	void StartRecord(string sFileName);
	string getTimeAndFormat();

	string getDirectory (const string& path);
	bool  directoryExists(const std::string& dirName_in);

	string sOutputDir;

public:
	VideoRecorder(int codecType,double fps,Size inputSize,string programStartUp);
	~VideoRecorder(void);

	void StartRecord();

	void Record(Mat frame);
	void StopRecord();
	bool IsRecord();
};

#endif /* VIDEORECORDER_H_ */