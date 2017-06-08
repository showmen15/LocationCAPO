#ifndef ARUCOLOCATION_H_
#define ARUCOLOCATION_H_

#include <iostream>
#include "ArucoLocation.pb.h" // protobuf //https://www.youtube.com/watch?v=x-u-hEFhDDo
#include "UdpClientLinux.h"  //http://www.binarytides.com/udp-socket-programming-in-winsock/
#include "VideoRecorder.h"


#include <math.h>

#include "opencv2/opencv.hpp"



#define ROBOTS_COUNT 10

using namespace std;
using namespace cv;

class  ArucoLocation
{
private:
	Aruco::ArucoLocation RobotLocation[ROBOTS_COUNT];
	UdpClient *RobotClient[ROBOTS_COUNT];

	bool working;
public:
	 ArucoLocation();
	~ ArucoLocation();
	void Run();
	void Stop();
};





#endif /* ARUCOLOCATION_H_ */