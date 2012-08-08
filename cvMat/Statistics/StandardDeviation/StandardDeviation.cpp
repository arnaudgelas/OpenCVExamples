#include <iostream>

#include "cv.h"
#include "highgui.h"

int main( int argc, char* argv[] )
{
  if( argc != 2)
    {
    std::cerr << "Usage: " << argv[0] << " <InputImage>" << std::endl;
    return EXIT_FAILURE;
    }

  cv::Mat image = cv::imread( argv[1] );
  if(!image.data)
    {
    return EXIT_FAILURE;
    }

    cv::Scalar mean,stddev; //0:1st channel, 1:2nd channel and 2:3rd channel

    meanStdDev(image,mean,stddev,cv::Mat());
    std::cout<<"Standard deviation: "<<stddev.val[0]<<std::endl;
    return 0;
}
