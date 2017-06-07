#include "VideoRecorder.h"


VideoRecorder::VideoRecorder()
{
}


VideoRecorder::~VideoRecorder()
{
}


void VideoRecorder::StartRecord(string sFileName)
{
}


void VideoRecorder::init()
{
	//outputVideo = new VideoWriter();

	//outputVideo = new VideoWriter();
	//
	//// Open the output
 //   if (askOutputType)
 //       outputVideo.open(NAME, ex=-1, inputVideo.get(CV_CAP_PROP_FPS), S, true);
 //   else
 //       outputVideo.open(NAME, ex, inputVideo.get(CV_CAP_PROP_FPS), S, true);

 //   if (!outputVideo.isOpened())
 //   {
 //       cout  << "Could not open the output video for write: " << source << endl;
 //       return -1;
 //   }
}

void VideoRecorder::StartRecord(string sFileName)
{
}

void VideoRecorder::Record(Mat frame)
{
}

void VideoRecorder::EndRecord()
{
	outputVideo->release();
	delete outputVideo;
}



