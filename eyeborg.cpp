#include "cv.h" 
#include "highgui.h" 
#include <stdio.h>  
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    VideoCapture webcam(0); // open the default camera
    if(!webcam.isOpened())  // check if we succeeded
        return -1;

    double width = webcam.get(CV_CAP_PROP_FRAME_WIDTH);
    double height = webcam.get(CV_CAP_PROP_FRAME_HEIGHT);

    VideoWriter video("webcam.avi",-1, 30, cvSize((int)width,(int)height) );
    VideoWriter video_mitjana("mitjana.avi",-1, 30, cvSize((int)width,(int)height) );

    namedWindow( "lawebcam", CV_WINDOW_AUTOSIZE );
    namedWindow( "elcolormig", CV_WINDOW_AUTOSIZE );

    Mat fotograma;
    Mat matriuMitjana;
    Scalar colorMig(10,10,10);
    Scalar colorMigHSV(10,10,10);

    if(!video.isOpened() || !video.isOpened())
    {
        cerr << "No he pogut crear el vídeo";
        return -1;
    }

    std::cout << "Prem Esc per parar el programa" << std::endl;
 
    while(true)
    {
      webcam >> fotograma; // agafa un nou fotograma de la camera

        if(!fotograma.data)
        {
            cerr << "no he pogut agafar el fotograma.";
            return -1;
        }
 
        // Save frame to video
        video << fotograma;
 
      //Ensenya el fotograma a la finestra
      imshow( "lawebcam", fotograma );

      //Calcula el color mig de la imatge
      colorMig = mean(fotograma);

      //Copia el color mig a la imatge
      matriuMitjana.setTo(colorMig);

      //Tradueix-lo a l'espai de color HSV
      cvtColor(fotograma,matriuMitjana,CV_RGB2HSV); 

      //Calcula el valor mig en l'espai HSV
      colorMigHSV = mean(matriuMitjana);

      //Tradueix-lo a freqüència amb la fòrmula 200 + 2*tonalitat
      double frequence = 200+2*colorMigHSV[0];

      //prepara la commanda per a fer el so
      ostringstream command;
      command << "beep --verbose -f " << frequence << " 400 -d 100 -l 400";

      //crida el programa beep del systema
      system(command.str().c_str());

      //Ensenya el fotograma a la finestra
      imshow( "elcolormig", matriuMitjana );

      //Copia el fotograma al vídeo del disc
      video_mitjana << matriuMitjana;

      //Mira si s'ha pitjat ESC
      if(waitKey(2) >= 0) break;
    }

    return EXIT_SUCCESS;
}
