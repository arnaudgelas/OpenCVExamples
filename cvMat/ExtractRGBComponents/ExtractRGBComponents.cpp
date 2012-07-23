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

  cv::Mat src_img = cv::imread( argv[1] );
  if(!src_img.data)
    {
    return EXIT_FAILURE;
    }
    
  std::vector<cv::Mat> three_channels;
  cv::split(src_img,three_channels );

  cv::imwrite( "red.png", three_channels[2] );
  cv::imwrite( "green.png", three_channels[1] );
  cv::imwrite( "blue.png", three_channels[0] );


  return EXIT_SUCCESS;
}