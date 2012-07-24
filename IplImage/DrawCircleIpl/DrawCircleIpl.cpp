#include <iostream>

#include "cv.h"
#include "highgui.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
    {
    std::cerr << "Usage: " << argv[0] << " <InputImage> <Thickness>" << std::endl;
    return EXIT_FAILURE;
    }

  IplImage* image = cvLoadImage( argv[1] );
  if( !image )
    {
    std::cerr << "Could not load image file: " << argv[1] << std::endl;
    return EXIT_FAILURE;
    }

  CvPoint center;
  center.x = image->width / 2;
  center.y = image->height / 2;
  int radius = 10;

  CvScalar color;
  color.val[0] = 255.;

  int thickness = atoi( argv[2] ); // if thickness < 0, the circle is filled

  cvCircle( image, center, radius, color, thickness );

  cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
  cvShowImage( argv[1], image );

  cvReleaseImage( &image );
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
