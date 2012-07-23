#include <iostream>

#include "cv.h"
#include "highgui.h"

int main( int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage: " << argv[0] << " <InputImage>" << std::endl;
    return EXIT_FAILURE;
    }

  IplImage* image = cvLoadImage( argv[1] );
  if( !image )
    {
    std::cerr << "Could not load image file: " << argv[1] << std::endl;
    return EXIT_FAILURE;
    }
    
  IplImage *r = cvCreateImage(cvSize(image->width, image->height ),image->depth, 1);
  IplImage *g = cvCreateImage(cvSize(image->width, image->height ),image->depth, 1);
  IplImage *b = cvCreateImage(cvSize(image->width, image->height ),image->depth, 1);

  cvSplit( image, b, g, r, 0 );

  cvSaveImage( "red.png", r );
  cvSaveImage( "green.png", g );
  cvSaveImage( "blue.png", b );

  cvReleaseImage( &r );
  cvReleaseImage( &g );
  cvReleaseImage( &b );
  
  cvReleaseImage( &image );

  return EXIT_SUCCESS;
}