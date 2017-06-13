#include "VideoRecorder.h"


VideoRecorder::VideoRecorder(int codecType,double fps,Size inputSize,string programStartUp)
{
	sOutputDir = getDirectory(programStartUp) + "\\Output\\";

	if(!directoryExists(sOutputDir))
		mkdir(sOutputDir.c_str());

	CodecType = codecType;
	Fps = fps;
	InputSize = inputSize;

	recording = false;
}

VideoRecorder::~VideoRecorder()
{
	if(outputVideo != NULL)
		StopRecord();
}

void VideoRecorder::StartRecord()
{ 
	string sPath = sOutputDir + getTimeAndFormat() +  ".avi"; // "test1.avi"; //"C:\\git\\LocationCAPO\\ArucoLocation\\Debug\\test7.avi"; //".\\Output\\test.mp4"; //+ getTimeAndFormat() + ".mp4"; //wygeneruj nazwe pliku w katalogu gdzie program jest

	if(IsRecord())
		StopRecord();

	StartRecord(sPath);
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
		recording = true;
	}
}

void VideoRecorder::Record(Mat frame)
{
	if(recording)
		outputVideo->write(frame);
}

void VideoRecorder::StopRecord()
{
	if(recording)
	{
		recording = false;
		outputVideo->release();
		delete outputVideo;
		outputVideo = NULL;

		cout << "Finished writing" << endl;
	}
}

bool VideoRecorder::IsRecord()
{
	return recording;
}

string VideoRecorder::getTimeAndFormat()
{
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime

	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "Robot_%Y_%m_%d_%H_%M_%S", &tstruct);

	return buf;
}

string VideoRecorder::getDirectory(const string& path)
{
	size_t found = path.find_last_of("/\\");
	return(path.substr(0, found));
}

bool  VideoRecorder::directoryExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}