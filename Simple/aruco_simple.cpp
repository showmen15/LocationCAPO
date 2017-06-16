/*****************************
Copyright 2011 Rafael Muñoz Salinas. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Rafael Muñoz Salinas ''AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Rafael Muñoz Salinas OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Rafael Muñoz Salinas.
********************************/


#include <iostream>
#include "aruco.h"
#include "cvdrawingutils.h"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/video.hpp"

#include <math.h>

using namespace cv;
using namespace aruco;


int main2(int, char**)
{
    VideoCapture cap(1); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;


	cap.set(37, 0);

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        //cvtColor(frame, edges, CV_BGR2GRAY);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        imshow("edges", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}


float distanceBetweenPoint(Point p0,Point p1)
{
	return sqrt(pow(p0.x - p1.x,2) + pow(p0.y - p1.y,2));
}


int main(int argc, char **argv) {

	namedWindow("in", 1);

	VideoCapture inputVideo(0);              // Open input
	Mat src, res;
    
	if (!inputVideo.isOpened())
    {
        cout  << "Could not open the input video: "  << endl;
        return -1;
    }

	for(;;) //Show the image captured in the window and repeat
    { 	
		inputVideo >> src;              // read

		namedWindow("in", 1);

		imshow("in", src);
		
		
	  if(waitKey(30) >= 0) 
		  continue;
			
			

       // if (src.empty()) break;         // check if at end

       // split(src, spl);                // process - extract only the correct channel
       // for (int i =0; i < 3; ++i)
       //     if (i != channel)
       //         spl[i] = Mat::zeros(S, spl[0].type());
       //merge(spl, res);

       ////outputVideo.write(res); //save or
       //outputVideo << res;
    }

    cout << "Finished writing" << endl;
	return 0;
}
	


int main1(int argc, char **argv) {
	float x0 = 0;
	float y0 = 0;

	
	try {
        if (argc < 2) {
            cerr << "Usage: (in.jpg|in.avi) [cameraParams.yml] [markerSize] [outImage]" << endl;
            exit(0);
        }

        aruco::CameraParameters CamParam;
        MarkerDetector MDetector;
        vector< Marker > Markers;
        float MarkerSize = -1;
        // read the input image
        cv::Mat InImage;
        // try opening first as video
        VideoCapture vreader(0);
        
				while(true)
		{
		
		if (vreader.isOpened()) 
		{
            vreader.grab();
            vreader.retrieve(InImage);
        } 
		else 
		{
            InImage = cv::imread(argv[1]);
        }
        // at this point, we should have the image in InImage
        // if empty, exit
        if (InImage.total() == 0) {
            cerr << "Could not open input" << endl;
            return 0;
        }

        // read camera parameters if specifed
        if (argc >= 3) {
            CamParam.readFromXMLFile(argv[2]);
            // resizes the parameters to fit the size of the input image
            CamParam.resize(InImage.size());
        }
        // read marker size if specified
        if (argc >= 4)
            MarkerSize = atof(argv[3]);
       
		 cv::namedWindow("in", 1);


		 float dist;
			

        // Ok, let's detect
        MDetector.detect(InImage, Markers, CamParam, MarkerSize);
        
		// for each marker, draw info and its boundaries in the image
        for (unsigned int i = 0; i < Markers.size(); i++) 
		{
			cout << "Marker: " << i << " x: "   <<  Markers[i].getCenter().x << " y: " <<  Markers[i].getCenter().y;

			//Point p0 = Markers[i][0]

           // cout << Markers[i] << endl;
            Markers[i].draw(InImage, Scalar(0, 0, 255), 2);

			 dist = distanceBetweenPoint(Markers[i][0],Markers[i][1]);
		 cout << " Dystance:  "	 << dist;
        }

		cout << endl;

        // draw a 3d cube in each marker if there is 3d info
        /*if (CamParam.isValid() && MarkerSize != -1)
            for (unsigned int i = 0; i < Markers.size(); i++) {
                CvDrawingUtils::draw3dCube(InImage, Markers[i], CamParam);
            }*/
        // show input with augmented information
        cv::imshow("in", InImage);
        // show also the internal image resulting from the threshold operation
        cv::imshow("thes", MDetector.getThresholdedImage());


        cv::waitKey(10); // wait for key to be pressed
		}


        if (argc >= 5)
            cv::imwrite(argv[4], InImage);
    } catch (std::exception &ex)

    {
        cout << "Exception :" << ex.what() << endl;
    }
}



//int main(int argc, char **argv) 
//{
//    
//	try
//	{
//      /*  if (argc < 2) {
//            cerr << "Usage: (in.jpg|in.avi) [cameraParams.yml] [markerSize] [outImage]" << endl;
//            exit(0);
//        }*/
//
//
//        aruco::CameraParameters CamParam;
//        MarkerDetector MDetector;
//        vector< Marker > Markers;
//        float MarkerSize = 1000;
//        // read the input image
//        cv::Mat InImage;
//        // try opening first as video
//        //VideoCapture vreader(argv[1]);
//		VideoCapture vreader(1);
//
//
//	
//
//		//vreader.set(CV_CAP_PROP_BRIGHTNESS,77);
//		
//
//		
//
//		//vreader.set(39,0);
//		//value = vreader.get(39);
//
//		//vreader.set(3, 1280); //# set the resolution
//		//vreader.set(4, 720);
//
//		//vreader.set(37, 0);
//
//		//value = vreader.get(39);
//
//		while(true)
//		{
//
//			cout << vreader.get(CV_CAP_PROP_BRIGHTNESS) << "\n";
//
//        if (vreader.isOpened()) {
//            vreader.grab();
//            vreader.retrieve(InImage);
//
//        } else {
//            InImage = cv::imread(argv[1]);
//        }
//        // at this point, we should have the image in InImage
//        // if empty, exit
//        if (InImage.total() == 0) {
//            cerr << "Could not open input" << endl;
//            return 0;
//        }
//
//        // read camera parameters if specifed
//        if (argc >= 3) {
//            CamParam.readFromXMLFile(argv[2]);
//            // resizes the parameters to fit the size of the input image
//            CamParam.resize(InImage.size());
//        }
//
//        // read marker size if specified
//        if (argc >= 4)
//            MarkerSize = atof(argv[3]);
//        cv::namedWindow("in", 1);
//
//
//        // Ok, let's detect
//        MDetector.detect(InImage, Markers, CamParam, MarkerSize);
//        // for each marker, draw info and its boundaries in the image
//        for (unsigned int i = 0; i < Markers.size(); i++) {
//            cout << Markers[i] << endl;
//            Markers[i].draw(InImage, Scalar(0, 0, 255), 2);
//        }
//        // draw a 3d cube in each marker if there is 3d info
//        if (CamParam.isValid() && MarkerSize != -1)
//            for (unsigned int i = 0; i < Markers.size(); i++) {
//                CvDrawingUtils::draw3dCube(InImage, Markers[i], CamParam);
//            }
//        // show input with augmented information
//        cv::imshow("in", InImage);
//        // show also the internal image resulting from the threshold operation
//        cv::imshow("thes", MDetector.getThresholdedImage());
//        cv::waitKey(20); // wait for key to be pressed
//
//		}
//
//        if (argc >= 5)
//            cv::imwrite(argv[4], InImage);
//    } catch (std::exception &ex)
//
//    {
//        cout << "Exception :" << ex.what() << endl;
//    }
//}


