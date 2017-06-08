#include "VideoRecorder.h"


VideoRecorder::VideoRecorder(int codecType,double fps,Size inputSize)
{
	 CodecType = codecType;
	 Fps = fps;
	 InputSize = inputSize;
}

VideoRecorder::~VideoRecorder()
{
	if(outputVideo != NULL)
		StopRecord();
}

void VideoRecorder::StartRecord(string sFileName)
{
	outputVideo = new VideoWriter();
	outputVideo->open(sFileName.c_str(),CodecType,Fps,InputSize,true);

	 if (!outputVideo->isOpened())
    {
		cout  << "Could not open the output video for write:" << sFileName  << endl;
	 }
	 else
	 {
		 cout  << "Open output stream" << sFileName  << endl;
	 }
}

void VideoRecorder::Record(Mat frame)
{
	outputVideo->write(frame);
}

void VideoRecorder::StopRecord()
{
	outputVideo->release();
	delete outputVideo;
	outputVideo = NULL;

	cout << "Finished writing" << endl;
}



