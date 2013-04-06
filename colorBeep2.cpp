#include "cv.h" 
#include "highgui.h" 
#include <stdio.h>  
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "opencv2/opencv.hpp"

using namespace cv;

double getFreqFromColor(int r, int g, int b){
    std::cout << "color(hsv): " << r << " " << g << " " << b << std::endl; 
    return r;

}

int main(int argc, char **argv)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow( "mywindow", CV_WINDOW_AUTOSIZE );
    namedWindow( "mymeanwindow", CV_WINDOW_AUTOSIZE );

    Mat averageMat;
    Scalar averageColor(10,10,10);

    for(;;)
    {
      Mat frame;
      cap >> frame; // get a new frame from camera

      cv::imshow( "mywindow", frame );
      Scalar averageColor = mean(frame);
      cvtColor(frame,averageMat,CV_RGB2HSV); 
      Scalar averageColorhsv = mean(averageMat);
      averageMat.setTo(averageColor);

      double frequence = 200+2*getFreqFromColor(averageColorhsv[0], averageColorhsv[1],averageColorhsv[2]);

      std::ostringstream command;
      command << "beep --verbose -f " << frequence << " 400 -d 100 -l 400";
      system(command.str().c_str());

      cv::imshow( "mymeanwindow", averageMat );

      if(waitKey(10) >= 0) break;
    }

    // the camera will be deinitialized automatically in VideoCapture destructor
    return EXIT_SUCCESS;
}
