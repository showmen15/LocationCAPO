#ifndef ARUCOLOCATION_H_
#define ARUCOLOCATION_H_

#include <iostream>
#include "ArucoLocation.pb.h" // protobuf //https://www.youtube.com/watch?v=x-u-hEFhDDo
#include "UdpClientLinux.h"  //http://www.binarytides.com/udp-socket-programming-in-winsock/
#include "VideoRecorder.h"


#include <math.h>

#include "opencv2/opencv.hpp"
#include <thread>         // std::thread
#include <mutex>		  //sekcja krtyczyna
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <iostream>
#include "aruco.h"
#include "cvdrawingutils.h"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/video.hpp"

#include <math.h>



#define ROBOTS_COUNT 10

using namespace std;
using namespace cv;
using namespace aruco;

class  ArucoLocation
{
private:
	Aruco::ArucoLocation RobotLocation[ROBOTS_COUNT];
	UdpClient *RobotClient[ROBOTS_COUNT];


	void run();
	bool working;
	

	//mutex processingData;
	//mutex waitingForData;

	//int Input;

	thread thr;


//std::mutex m;
std::condition_variable cv;
//std::string data;
//bool ready;
//bool processed;


std::mutex mtx;           // mutex for critical section

 aruco::CameraParameters CamParam;
  MarkerDetector MDetector;
  vector< Marker > Markers;
  float MarkerSize;
       
  Mat InImage; // read the input image
public:
	 ArucoLocation(string cameraParams);
	~ ArucoLocation();
	void Run();
	void Stop();
	 void Update(Mat frame);
};





#endif /* ARUCOLOCATION_H_ */