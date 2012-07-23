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
    
  CvSize size = cvSize( image->width, image->height );
  IplImage* image_gray = cvCreateImage( size, image->depth, 1 );
  IplImage* dst = cvCreateImage( size, image->depth, 1 );
  
  cvCvtColor( image, image_gray, CV_RGB2GRAY );
  int threshold_value=100;
  int max_BINARY_value=200;
  
  cvThreshold( image_gray, dst, threshold_value, max_BINARY_value,0 );
  
  cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
  cvShowImage( argv[1], dst );

  cvSaveImage( "binaryThreshold.png", dst);
   
  cvReleaseImage( &image );
  cvReleaseImage( &image_gray );
  cvReleaseImage( &dst );
  cv::waitKey(0);

  return EXIT_SUCCESS;
}