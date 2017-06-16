#include "ArucoLocation.h"

//formatowanie kodu
// CTRL+K CTRL+F 

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

int main22()
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

bool temp;

void run()
{
	while(temp)
	{

		Sleep(1000);
	}
}


int main22(int argc, char **argv)
{
	temp = true;
	thread thr = thread(run);
	temp = false;

	thr.join();
	return 0;
}


bool isParam(string line)
{
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

int main(int argc, char **argv)
{
	try
	{
		string programStartUp = argv[0];
		string source = argv[1];

		VideoCapture inputVideo;

		if(isParam(source))
			inputVideo = VideoCapture(stoi(source.c_str())); // open the default camera
		else
			inputVideo = VideoCapture(source); // open file

		if(!inputVideo.isOpened())  // check if we succeeded    
			return -1;

		bool working = true;
		int key;
		string sCameraParams =  ".\\out_camera_params.yml";

		int CodecType = CV_FOURCC('M', 'J', 'P', 'G'); //CV_FOURCC('H', '2', '6', '3'); // Get Codec Type- Int form
		double Fps = 17.0; //25.0
		Size InputSize = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT)); // Acquire input size

		ArucoLocation location(sCameraParams,InputSize); //okiekt lokalizacji
		VideoRecorder rec(CodecType,Fps,InputSize,programStartUp);

		Mat frame;
		namedWindow("frame",1);
		cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);

		int zaczytane = 20;

		for(;working;)
		{
			inputVideo >> frame; // get a new frame from camera

			



			/*
			//Grayscale matrix
    cv::Mat grayscaleMat (frame.size(), CV_8U);

    //Convert BGR to Gray
    cv::cvtColor( frame, grayscaleMat, CV_BGR2GRAY );

    //Binary image
    cv::Mat binaryMat(grayscaleMat.size(), grayscaleMat.type());

    //Apply thresholding
    cv::threshold(grayscaleMat, binaryMat, 100, 255, cv::THRESH_BINARY);

    //Show the results
    
    cv::imshow("Output", binaryMat);
	*/

	rec.Record(frame);
			location.Update(frame);	

			imshow("frame", frame);

			key = waitKey(200);
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
						rec.StopRecord();
						location.Stop();
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
				case 2490368:
					{
						location.AddYp(-1);
						break;
					}

					//strzalka down
				case 2621440:
					{
						location.AddYp(1);
						break;
					}

					//strzalka left
				case 2424832:
					{
						location.AddXp(-1);
						break;
					}

					//strzalka right
				case 2555904:
					{
						location.AddXp(1);
						break;
					}

				default:
					break;
				}
			}
		}
	}
	catch(Exception ex)
	{
		cout << ex.what();
	}


	return 0;
}


