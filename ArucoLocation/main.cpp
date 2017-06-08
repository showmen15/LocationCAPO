#include "ArucoLocation.h"

//http://docs.opencv.org/3.0-beta/modules/videoio/doc/reading_and_writing_video.html




//void bar(int x)
//{
//  // do stuff...
//}
//
//int main()
//{
//
//	//https://stackoverflow.com/questions/40544480/correct-way-to-pause-resume-an-stdthread
//	//Producent konsument
//
//  std::thread second (bar,0);  // spawn new thread that calls bar(0)
//
//  //second
//
//	  
//
//}
static void help()
{
    cout
        << "------------------------------------------------------------------------------" << endl
        << "This program shows how to write video files."                                   << endl
        << "You can extract the R or G or B color channel of the input video."              << endl
        << "Usage:"                                                                         << endl
        << "./video-write inputvideoName [ R | G | B] [Y | N]"                              << endl
        << "------------------------------------------------------------------------------" << endl
        << endl;
}
//
//int main(int argc, char *argv[])
//{
//    help();
//
//    if (argc != 4)
//    {
//        cout << "Not enough parameters" << endl;
//        return -1;
//    }
//
//    const string source      = argv[1];           // the source file name
//    const bool askOutputType = argv[3][0] =='Y';  // If false it will use the inputs codec type
//
//    VideoCapture inputVideo(source);              // Open input
//    if (!inputVideo.isOpened())
//    {
//        cout  << "Could not open the input video: " << source << endl;
//        return -1;
//    }
//
//    string::size_type pAt = source.find_last_of('.');                  // Find extension point
//    const string NAME = source.substr(0, pAt) + argv[2][0] + ".avi";   // Form the new name with container
//    int ex = static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form
//
//    // Transform from int to char via Bitwise operators
//    char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};
//
//    Size S = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
//                  (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
//
//    VideoWriter outputVideo;                                        // Open the output
//    if (askOutputType)
//        outputVideo.open(NAME, ex=-1, inputVideo.get(CV_CAP_PROP_FPS), S, true);
//    else
//        outputVideo.open(NAME, ex, inputVideo.get(CV_CAP_PROP_FPS), S, true);
//
//    if (!outputVideo.isOpened())
//    {
//        cout  << "Could not open the output video for write: " << source << endl;
//        return -1;
//    }
//
//    cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
//         << " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
//    cout << "Input codec type: " << EXT << endl;
//
//    int channel = 2; // Select the channel to save
//    switch(argv[2][0])
//    {
//    case 'R' : channel = 2; break;
//    case 'G' : channel = 1; break;
//    case 'B' : channel = 0; break;
//    }
//    Mat src, res;
//    vector<Mat> spl;
//
//    for(;;) //Show the image captured in the window and repeat
//    {
//        inputVideo >> src;              // read
//        if (src.empty()) break;         // check if at end
//
//        split(src, spl);                // process - extract only the correct channel
//        for (int i =0; i < 3; ++i)
//            if (i != channel)
//                spl[i] = Mat::zeros(S, spl[0].type());
//       merge(spl, res);
//
//       //outputVideo.write(res); //save or
//       outputVideo << res;
//    }
//
//    cout << "Finished writing" << endl;
//    return 0;
//}
//
//


int main222(int, char**)
{
    Mat src;
    // use default camera as video source
    VideoCapture cap(0);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    // get one frame from camera to know frame size and type
    cap >> src;
    // check if we succeeded
    if (src.empty()) {
        cerr << "ERROR! blank frame grabbed\n";
        return -1;
    }
    bool isColor = (src.type() == CV_8UC3);
    //--- INITIALIZE VIDEOWRITER
    VideoWriter writer;
    int codec = CV_FOURCC('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
    double fps = 25.0;                          // framerate of the created video stream
    string filename = "./live.avi";             // name of the output video file
    writer.open(filename, codec, fps, Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH), (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT)), isColor);
    // check if we succeeded
    if (!writer.isOpened()) {
        cerr << "Could not open the output video file for write\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Writing videofile: " << filename << endl
         << "Press any key to terminate" << endl;
    for (;;)
    {
        // check if we succeeded
        if (!cap.read(src)) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // encode the frame into the videofile stream
        writer.write(src);
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", src);
        if (waitKey(5) >= 0)
            break;
    }
    // the videofile will be closed and released automatically in VideoWriter destructor
    return 0;
}

int main()
{
	VideoCapture inputVideo(0); // open the default camera
	
    if(!inputVideo.isOpened())  // check if we succeeded    
		return -1;

	int CodecType =  CV_FOURCC('M', 'J', 'P', 'G');     // Get Codec Type- Int form
	double Fps = 25.0;
	Size InputSize = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT)); // Acquire input size

	VideoRecorder rec(CodecType,Fps,InputSize);

	Mat frame;
    namedWindow("frame",1);

	rec.StartRecord("./Ale.avi");
    for(int i = 0; i < 30; i++)
    {
        inputVideo >> frame; // get a new frame from camera

		rec.Record(frame);
		
        //cvtColor(frame, edges, COLOR_BGR2GRAY);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        imshow("frame", frame);
        if(waitKey(5) >= 0) break;
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

 
