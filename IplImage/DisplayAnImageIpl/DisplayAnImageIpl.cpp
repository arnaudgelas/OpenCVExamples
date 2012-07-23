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

  cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
  cvShowImage( argv[1], image );

  cvReleaseImage( &image );
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
