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
    
  IplImage* ipl_img = cvLoadImage( argv[1] );
  if( !ipl_img )
    {
    std::cerr << "Could not load image file: " << argv[1] << std::endl;
    return EXIT_FAILURE;
    }

  cv::Mat imgmat(ipl_img,false); 
  
  return 0;
}