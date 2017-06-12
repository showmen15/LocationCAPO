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

#include <sstream>
#include <string>

#include <math.h>
#include <time.h>
#include <iostream>
#include <string>
#include <stdio.h>



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

	thread thr;

condition_variable cv;
mutex mtx;           // mutex for critical section

 CameraParameters CamParam;
  MarkerDetector MDetector;
  vector< Marker > Markers;
  float MarkerSize;
  float MarkerSizeM;
       
  Mat InImage; // read the input image

  //double get_x(Marker marker);
  //double get_y(Marker marker);
  //double get_alfa(Marker marker);

  void set_location(Marker marker, Aruco::ArucoLocation* location);
  double  distance(double x0,double y0,double x1,double y1);

  double Xp; //poczatek ukladu wspolzednych Xp
  double Yp; //poczatek ukladu wspolzednych Yp

  
public:
	 ArucoLocation(string cameraParams);
	~ArucoLocation();
	void Run();
	void Stop();
	void Update(Mat frame);

	void AddXp(double in);
	void AddYp(double in);

	void GetXpYp();
};





#endif /* ARUCOLOCATION_H_ */