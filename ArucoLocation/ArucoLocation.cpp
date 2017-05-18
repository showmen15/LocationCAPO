
#include "ArucoLocation.h"


 ArucoLocation:: ArucoLocation()
{
	string sIP;
	unsigned short port = 7777;

	for(int i = 0; i < ROBOTS_COUNT;i++)
	{
		RobotLocation[i].set_robotid(i);

		sIP = "192.168.2.20" + to_string(i);
		
		RobotClient[i] = new UdpClient(sIP.c_str(),port);
	}
}

 ArucoLocation::~ ArucoLocation()
{
	//for(int i = 0; i < ROBOTS_COUNT;i++)
	//{	
	//	
	//	RobotClient[i].~UdpClient();
	//}
}

void ArucoLocation::Run()
{
	working = true;
	int index = 0;

	while(working)
	{
	
	if(index == 3)
		working = false;

	index++;


	}
}

void ArucoLocation::Stop()
{
	working = false;
}