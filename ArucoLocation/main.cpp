#include "ArucoLocation.h"

//http://docs.opencv.org/3.0-beta/modules/videoio/doc/reading_and_writing_video.html

//void bar(int x)
//{
//  // do stuff...
//}
//
//int main()
//{
//
//	//https://stackoverflow.com/questions/40544480/correct-way-to-pause-resume-an-stdthread
//	//Producent konsument
//
//  std::thread second (bar,0);  // spawn new thread that calls bar(0)
//
//  //second
//
//	  
//
//}

int main22()
{
	/*
	
	ArucoLocation* location = new ArucoLocation();
	
	for(int i = 0;; i++)
	{

		location->Update(i);

		Sleep(1000);
		cout << "Working main" << endl;
	}

	delete location;*/

	return 0;
}

int main()
{
	string sCameraParams =  "D:\\Desktop\\TestAruco\\test\\LocationCAPO\\Simple\\input\\out_camera_params.yml";
	ArucoLocation* location = new ArucoLocation(sCameraParams); //okiekt lokalizacji

	VideoCapture inputVideo(0); // open the default camera
	
    if(!inputVideo.isOpened())  // check if we succeeded    
		return -1;

	int CodecType =  CV_FOURCC('M', 'J', 'P', 'G');     // Get Codec Type- Int form
	double Fps = 25.0;
	Size InputSize = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT)); // Acquire input size

	VideoRecorder rec(CodecType,Fps,InputSize);

	Mat frame;
    namedWindow("frame",1);

	//rec.StartRecord("./Ale.avi");
    for(;;)
    {
        inputVideo >> frame; // get a new frame from camera

		//rec.Record(frame);
		location->Update(frame);
		
		//cout << "Main" << endl;
			

        imshow("frame", frame);
        if(waitKey(5) >= 0) 
			break;
    }

	//rec.StopRecord();
	delete location;

    
    return 0;
}

 
