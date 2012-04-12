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

  IplImage* image = cvLoadImage( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
  if( !image )
    {
    std::cerr << "Could not load image file: " << argv[1] << std::endl;
    return EXIT_FAILURE;
    }

  std::vector< cv::Vec3f > circles;
  int method = CV_HOUGH_MULTI_SCALE;
  double dp = 10.;
  double minDist = 5.;
  double param1=100.;
  double param2=100.;
  int minRadius = 0;
  int maxRadius = 0;

  cv::HoughCircles( image, circles, method, dp, minDist, param1, param2,
                minRadius, maxRadius );

  CvScalar color;
  color.val[0] = 255.;

  int thickness = -1;

  size_t i = 1;

  for( std::vector< cv::Vec3f >::const_iterator it = circles.begin();
       it != circles.end();
       ++it, ++i )
    {
      std::cout << "feature point " << i << std::endl;
      std::cout << "position: [ " << ( *it )[0] << ", " << ( *it )[1] << "]" << std::endl;

      std::cout << std::endl;

      cvCircle( image, cv::Point( ( *it )[0], ( *it )[1] ), 10, color, thickness );
    }

  cv::namedWindow( argv[1], CV_WINDOW_NORMAL );
  cv::imshow( argv[1], image );

  cvReleaseImage( &image );
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
