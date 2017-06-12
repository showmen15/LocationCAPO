
#include "ArucoLocation.h"


 ArucoLocation:: ArucoLocation(string cameraParams)
{
	 MarkerSize = 1000; //wielkosc markera
	 MarkerSizeM = 0.26; //wielkosc markera w m
     CamParam.readFromXMLFile(cameraParams); // read camera parameters
           
	string sIP;
	unsigned short port = 7777;

	for(int i = 0; i < ROBOTS_COUNT;i++)
	{
		RobotLocation[i].set_robotid(i);

		sIP = "192.168.2.20" + to_string(i);
		
		RobotClient[i] = new UdpClient(sIP.c_str(),port);
	}

	 working = true;

	 thr = thread(&ArucoLocation::run,this);

	 Xp = 0;
	 Yp = 0;
}

 ArucoLocation::~ArucoLocation()
{	
	working = false;
	mtx.unlock();
	cv.notify_one();
	thr.~thread();


	/*for(int i = 0; i < ROBOTS_COUNT;i++)
	{	
		
		RobotClient[i].~UdpClient();
	}*/
}

 void ArucoLocation::run()
 { 
	 Aruco::ArucoLocation currentLocation;
	 UdpClient* curentRobotClient;

	 string output;
	 cv::namedWindow("in", 1);
	 cv::namedWindow("thes", 1);
	 
	 while(working)
	 {
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck);

		CamParam.resize(InImage.size());  // resizes the parameters to fit the size of the input image
        MDetector.detect(InImage, Markers, CamParam, MarkerSize);  // Ok, let's detect

        for (unsigned int i = 0; i < Markers.size(); i++) // for each marker, draw info and its boundaries in the image
		{
			currentLocation = RobotLocation[Markers[i].id];
			curentRobotClient = RobotClient[Markers[i].id];

			set_location(Markers[i],currentLocation);
		
			currentLocation.SerializePartialToString(&output);
			curentRobotClient->Send(output);

			Markers[i].draw(InImage, Scalar(0, 0, 255), 2);	
			Markers[i].directionVector(InImage,currentLocation.alfa());
        }

		CvDrawingUtils::draw2dAxis(InImage,Xp,Yp); //narysuj osie Ox Oy

		cv::imshow("in", InImage); // show input with augmented information       
        cv::imshow("thes", MDetector.getThresholdedImage());  // show also the internal image resulting from the threshold operation	  
		cv::waitKey(1); // wait for key to be pressed
	 }
 }

 void ArucoLocation::Update(Mat frame)
 {
	 std::unique_lock<std::mutex> lck(mtx,std::defer_lock);

	 if(lck.try_lock())
	 {		
		 frame.copyTo(InImage);
		 cv.notify_one();
	 }
 }

//void ArucoLocation::Run()
//{
//	working = true;
//	int index = 0;
//	string output;
//
//	while(working)
//	{	
//		for(int i = 0; i < ROBOTS_COUNT;i++)
//		{
//			RobotLocation[i].set_alfa(423423);
//
//			RobotLocation[i].SerializePartialToString(&output);
//			RobotClient[i]->Send(output);
//
//			Aruco::ArucoLocation temp;
//
//			temp.ParseFromString(output);
//
//			
//		}
//
//
//
//	if(index == 3)
//		working = false;
//
//	index++;
//
//
//	}
//}

void ArucoLocation::Stop()
{
	working = false;
}

//double ArucoLocation::get_x(Marker marker)
//{
//	return 1.0;
//}
//
//double ArucoLocation::get_y(Marker marker)
//{
//	return 2.0;
//}
//
//double ArucoLocation::get_alfa(Marker marker)
//{
//	return 3.0;
//}

void ArucoLocation::set_location(Marker marker, Aruco::ArucoLocation location)
{
	double x0 = marker[0].x;
	double y0 = marker[0].y;

	double x1 = marker[1].x;
	double y1 = marker[1].y;
	
	double dist = distance(x0, y0, x1, y1);
	
	double Xl = marker.getCenter().x - Xp;
	double Yl = marker.getCenter().y - Yp;

	double Xlm = (MarkerSizeM * Xl) / dist;
	double Ylm = (MarkerSizeM * Yl) / dist;

	double Vxl = x1 - x0;
	double Vyl = y1 - y0;

	double Vl = sqrt(pow(Vxl,2) + pow(Vyl,2));
	
	double alfa = Vxl / Vl;

	location.set_x(Xlm); //pozyajca w metrach
	location.set_y(Ylm); //pozyajca w metrach
	location.set_alfa(alfa); //kat w radianach

	cout << alfa << endl;
}

double ArucoLocation::distance(double x0,double y0,double x1,double y1)
{
	return sqrt( pow(x1 - x0, 2) + pow(y1 - y0,2));
}

void ArucoLocation::AddXp(double in)
{
	if((Xp + in) >= 0)
		Xp += in;
}

void ArucoLocation::AddYp(double in)
{
	if((Yp + in) >= 0)
		Yp += in;
}

void ArucoLocation::GetXpYp()
{
	cout << "Xp: " << Xp << " Yp: " << Yp << endl;
}