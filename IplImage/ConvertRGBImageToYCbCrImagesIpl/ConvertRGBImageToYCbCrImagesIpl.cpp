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

  IplImage* imageYCrCb = cvCreateImage( size, img->depth, 3 );
  cvCvtColor( img, imageYCrCb, CV_BGR2YCrCb );

  IplImage* imageY  = cvCreateImage( size, img->depth, 1 );
  IplImage* imageCr = cvCreateImage( size, img->depth, 1 );
  IplImage* imageCb = cvCreateImage( size, img->depth, 1 );

  cvSplit( imageYCrCb, imageY, imageCr, imageCb, NULL );
  cvReleaseImage( &imageYCrCb );

  cvSaveImage( "y.png", imageY );
  cvSaveImage( "Cr.png", imageCr );
  cvSaveImage( "Cb.png", imageCb);

  cvReleaseImage( &imageY );
  cvReleaseImage( &imageCr );
  cvReleaseImage( &imageCb );

  cvReleaseImage( &img );

  return EXIT_SUCCESS;
}
