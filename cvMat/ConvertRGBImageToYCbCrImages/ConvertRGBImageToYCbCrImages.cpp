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
    
  cv::Mat YCrCb;

  cv::cvtColor( image, YCrCb, CV_BGR2YCrCb );

  std::vector<cv::Mat> YCrCb_planes;
  cv::split( image, YCrCb_planes );
  
  cv::imwrite( "Y.png", YCrCb_planes[0]);
  cv::imwrite( "Cr.png", YCrCb_planes[1]);
  cv::imwrite( "Cb.png", YCrCb_planes[2]);

  return EXIT_SUCCESS;
}
