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

  cv::Mat image = cv::imread( argv[1] );
  if(!image.data)
    {
    return EXIT_FAILURE;
    }
  
  cv::Mat image_gray, dst;
  
  cv::cvtColor( image, image_gray, CV_RGB2GRAY );
  int threshold_value=100;
  int max_BINARY_value=200;
  
  cv::threshold( image_gray, dst, threshold_value, max_BINARY_value,0 );
  
  cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
  cv::imshow( argv[1], dst );

  cv::imwrite( "binaryThreshold.png", dst);
   
  cv::waitKey(0);

  return EXIT_SUCCESS;
}