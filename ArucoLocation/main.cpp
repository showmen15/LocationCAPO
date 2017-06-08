#include "ArucoLocation.h"

//http://docs.opencv.org/3.0-beta/modules/videoio/doc/reading_and_writing_video.html




void bar(int x)
{
  // do stuff...
}

int main()
{

	//https://stackoverflow.com/questions/40544480/correct-way-to-pause-resume-an-stdthread
	//Producent konsument

  std::thread second (bar,0);  // spawn new thread that calls bar(0)

  second

	  

}

int main1()
{
	VideoCapture inputVideo(0); // open the default camera
	
    if(!inputVideo.isOpened())  // check if we succeeded    
		return -1;

	int CodecType =  static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form
	double Fps = inputVideo.get(CV_CAP_PROP_FPS);
	Size InputSize = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT)); // Acquire input size

	VideoRecorder rec(CodecType,Fps,InputSize);

	Mat frame;
    namedWindow("frame",1);

	rec.StartRecord("C:\\Ale.avi");
    for(;;)
    {
        inputVideo >> frame; // get a new frame from camera

		rec.Record(frame);
		
        //cvtColor(frame, edges, COLOR_BGR2GRAY);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        imshow("frame", frame);
        if(waitKey(30) >= 0) break;
    }

	rec.StopRecord();

    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;


	//ArucoLocation lok;
	//lok.Run();


	//Aruco::ArucoLocation testowy;
	//testowy.set_alfa(99);
	//UdpClient *cl = new UdpClient("127.0.0.1",7777);

	//cl->Send("ala ma kot");

	////testowy.set_alfa(45);

	////cout << testowy.alfa();


	return 0;
}

 
