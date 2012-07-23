#include <cstdlib>
#include <iostream>

#include "cv.h"
#include "highgui.h"

int main( int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage: " << argv[0] << "<InputImage>" << std::endl;
    return EXIT_FAILURE;
    }

  IplImage* img = cvLoadImage( argv[1] );
  if( !img )
    {
    std::cerr << "Could not load image file: " << argv[1] << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << img->width << " x " << img->height << std::endl;

  CvSize size = cvSize( img->width, img->height );

  IplImage* imageHSV = cvCreateImage( size, img->depth, 3 );
  cvCvtColor( img, imageHSV, CV_BGR2HSV );

  IplImage* imageH = cvCreateImage( size, img->depth, 1 );
  IplImage* imageS = cvCreateImage( size, img->depth, 1 );
  IplImage* imageV = cvCreateImage( size, img->depth, 1 );

  cvSplit( imageHSV, imageH, imageS, imageV, NULL );
  cvReleaseImage( &imageHSV );

  cvSaveImage( "hue.png", imageH );
  cvSaveImage( "saturation.png", imageS );
  cvSaveImage( "value.png", imageV );

  cvReleaseImage( &imageH );
  cvReleaseImage( &imageS );
  cvReleaseImage( &imageV );

  cvReleaseImage( &img );

  return EXIT_SUCCESS;
}
