#include <stdio.h>  
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "highgui.h" 
#include "cv.h" 
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    VideoCapture webcam(0); // open the default camera
    if(!webcam.isOpened())  // check if we succeeded
        return EXIT_FAILURE;
    
    webcam.set(CV_CAP_PROP_EXPOSURE, 0.0);
    webcam.set(CV_CAP_PROP_GAIN, 0.0);

    namedWindow( "lawebcam", CV_WINDOW_AUTOSIZE );
    namedWindow( "elcolormig", CV_WINDOW_AUTOSIZE );

    Mat fotograma;
    Mat fotogramaMitjana;
    Scalar colorMig(10,10,10);
    Scalar colorMigHSV(10,10,10);

    cout << "Prem Esc per parar el programa" << endl;
 
    while(true)
    {
      webcam >> fotograma; // agafa un nou fotograma de la camera

        if(!fotograma.data)
        {
            cerr << "no he pogut agafar el fotograma.";
            return EXIT_FAILURE;
        }
 
      //Ensenya el fotograma a la finestra
      imshow( "lawebcam", fotograma );

      //Calcula el color mig de la imatge
      colorMig = mean(fotograma);

      //Tradueix-lo a l'espai de color HSV
      cvtColor(fotograma,fotogramaMitjana,CV_RGB2HSV); 

      //Calcula el valor mig en l'espai HSV
      colorMigHSV = mean(fotogramaMitjana);

      //Posa tots els pixels del fotogramaMitjana 
      //amb el mateix valor que el colorMig
      fotogramaMitjana.setTo(colorMig);

      //Tradueix-lo a freqüència amb la fòrmula 200 + 2*tonalitat
      double frequence = 200+2*colorMigHSV[0];

      //prepara la commanda per a fer el so
      ostringstream command;
      command << "beep --verbose -f " << frequence << " 400 -d 100 -l 400";

      //crida el programa beep del systema
      system(command.str().c_str());

      //Ensenya el fotograma a la finestra
      imshow( "elcolormig", fotogramaMitjana );

      //Mira si s'ha pitjat ESC
      if(waitKey(2) >= 0) break;
    }

    return EXIT_SUCCESS;
}
