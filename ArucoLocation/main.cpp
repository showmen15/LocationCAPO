#include "ArucoLocation.h"

//http://docs.opencv.org/3.0-beta/modules/videoio/doc/reading_and_writing_video.html

int main()
{
	bool working = true;
	int key;
	string sCameraParams =  "D:\\Desktop\\TestAruco\\test\\LocationCAPO\\Simple\\input\\out_camera_params.yml";
	ArucoLocation location(sCameraParams); //okiekt lokalizacji

	VideoCapture inputVideo(0); // open the default camera
	
    if(!inputVideo.isOpened())  // check if we succeeded    
		return -1;

	int CodecType =  CV_FOURCC('M', 'J', 'P', 'G');     // Get Codec Type- Int form
	double Fps = 25.0;
	Size InputSize = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT)); // Acquire input size

	VideoRecorder rec(CodecType,Fps,InputSize);

	Mat frame;
    namedWindow("frame",1);

    for(;working;)
    {
        inputVideo >> frame; // get a new frame from camera

		rec.Record(frame);
		location.Update(frame);	

        imshow("frame", frame);

		key = waitKey(5);
		if(key >= 0)
		{
		switch (key)
		{
		//S|s -> start recording
		case 83:
		case 115:
			{
			rec.StartRecord();
			break;
			}
			
		//E|e -> end recording
		case 69:
		case 101:
			{
				rec.StopRecord();
			break;
			}

		
		//Esc -> end progroam
		case 27:
			{
			working = false;
			break;
			}

		default:
			break;
		}
		}
    }
    
    return 0;
}

 
