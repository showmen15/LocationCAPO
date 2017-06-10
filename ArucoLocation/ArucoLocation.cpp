
#include "ArucoLocation.h"


 ArucoLocation:: ArucoLocation(string cameraParams)
{
	 MarkerSize = 1000; //wielkosc markera
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
            Markers[i].draw(InImage, Scalar(0, 0, 255), 2);	
        }

		//cout << "Location Done" <<  Markers.size() << endl;

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