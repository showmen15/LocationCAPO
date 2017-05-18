#ifndef ARUCOLOCATION_H_
#define ARUCOLOCATION_H_

#include <iostream>
#include "ArucoLocation.pb.h" // protobuf //https://www.youtube.com/watch?v=x-u-hEFhDDo
#include "UdpClientLinux.h"


#define ROBOTS_COUNT 9 

using namespace std;

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