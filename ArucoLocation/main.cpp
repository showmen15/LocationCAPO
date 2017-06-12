#include "ArucoLocation.h"

//http://docs.opencv.org/3.0-beta/modules/videoio/doc/reading_and_writing_video.html


//string getTimeAndFormat()
//{
//	  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
//
//	time_t     now = time(0);
//    struct tm  tstruct;
//    char       buf[80];
//    tstruct = *localtime(&now);
//  
//    strftime(buf, sizeof(buf), "Robot_%Y_%m_%d_%X", &tstruct);
//
//    return buf;
//}

int main()
{
	//string ss = getTimeAndFormat();
	//ss += "aaa";

	   // current date/time based on current system
   //time_t now = time(0);
   //
   //// convert now to string form
   //char* dt = ctime(&now);

   //cout << "The local date and time is: " << dt << endl;

   //// convert now to tm struct for UTC
   //tm *gmtm = gmtime(&now);
   //dt = asctime(gmtm);
   //cout << "The UTC date and time is:"<< dt << endl;


	 // current date/time based on current system
   //time_t now = time(0);

   //cout << "Number of sec since January 1,1970:" << now << endl;

   //tm *ltm = localtime(&now);

   //// print various components of tm structure.
   //cout << "Year" << 1900 + ltm->tm_year<<endl;
   //cout << "Month: "<< 1 + ltm->tm_mon<< endl;
   //cout << "Day: "<<  ltm->tm_mday << endl;
   //cout << "Time: "<< 1 + ltm->tm_hour << ":";
   //cout << 1 + ltm->tm_min << ":";
   //cout << 1 + ltm->tm_sec << endl;
	
	
	//while(true)
	//{
	//	int key = waitKey(5);

	//	if(key > -1)
	//	{
	//		key += 1;
	//	}

	//}
	return 0;
}



int main22()
{
	bool working = true;
	int key;
	string sCameraParams =  ".\\out_camera_params.yml";
	ArucoLocation location(sCameraParams); //okiekt lokalizacji

	VideoCapture inputVideo(0); // open the default camera
	
    if(!inputVideo.isOpened())  // check if we succeeded    
		return -1;

	int CodecType =  CV_FOURCC('H', '2', '6', '4');  //CV_FOURCC('M', 'J', 'P', 'G');     // Get Codec Type- Int form
	double Fps = 17.0; //25.0
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

		// P|p  -> print Xp, Yp
		case 80:
		case 112:
			{
				location.GetXpYp();
				break;
			}

		//strzalka up
		case 11:
			{
				location.AddYp(-1);
				break;
			}

		//strzalka down
		case 12:
			{
				location.AddYp(1);
				break;
			}

         //strzalka left
		case 13:
			{
				location.AddXp(-1);
				break;
			}
		
		//strzalka right
		case 14:
			{
				location.AddYp(1);
				break;
			}

		default:
			break;
		}
		}
    }
    
    return 0;
}

 
