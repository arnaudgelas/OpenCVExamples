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
//  std::cout << size << std::endl;

  cvReleaseImage( &img );

  return EXIT_SUCCESS;
}
