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

  cv::Mat image = cv::imread( argv[1],1);
  if(!image.data)
    {
    return EXIT_FAILURE;
    }
    
  cv::Mat hsv;

  cv::cvtColor( image, hsv, CV_BGR2HSV );

  std::vector<cv::Mat> hsv_planes;
  cv::split( image, hsv_planes );
  
  cv::imwrite( "hue.png", hsv_planes[0]);
  cv::imwrite( "saturation.png", hsv_planes[1]);
  cv::imwrite( "value.png", hsv_planes[2]);

  return EXIT_SUCCESS;
}
