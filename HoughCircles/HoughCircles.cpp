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
  int method = CV_HOUGH_GRADIENT;
  /*
  double dp = 2.;
  double minDist = 10.;
  double param1=30.;
  double param2=15.;
  int minRadius = 5;
  int maxRadius = 50;
*/

  // The inverse ratio of the accumulator resolution to the image resolution.
  // For example, if dp=1 , the accumulator will have the same resolution as the
  // input image, if dp=2 - accumulator will have half as big width and height, etc
  double dp = 1.;

  // Minimum distance between the centers of the detected circles. If the parameter
  // is too small, multiple neighbor circles may be falsely detected in addition
  // to a true one. If it is too large, some circles may be missed
  double minDist = 5.;

  // The first method-specific parameter. in the case of CV_HOUGH_GRADIENT it is
  // the higher threshold of the two passed to Canny() edge detector (the lower
  // one will be twice smaller)
  double param1=100.;

  // The second method-specific parameter. in the case of CV_HOUGH_GRADIENT it is
  // the accumulator threshold at the center detection stage. The smaller it is,
  // the more false circles may be detected. Circles, corresponding to the larger
  // accumulator values, will be returned first
  double param2=20.;

  // Minimum circle radius
  int minRadius = 5;

  // Maximum circle radius
  int maxRadius = 100;
  cv::HoughCircles( image, circles, method, dp, minDist, param1, param2,
                minRadius, maxRadius );

  CvScalar color;
  color.val[0] = 255.;

  int thickness = 3;

  size_t i = 1;

  for( std::vector< cv::Vec3f >::const_iterator it = circles.begin();
       it != circles.end();
       ++it, ++i )
    {
      std::cout << "feature point " << i << std::endl;
      std::cout << "position: [ " << ( *it )[0] << ", " << ( *it )[1] << "]" << std::endl;
      std::cout << "radius: " << ( *it )[2] << std::endl;
      std::cout << std::endl;

      cvCircle( image, cv::Point( ( *it )[0], ( *it )[1] ), (*it)[2], color, thickness );
    }

  cv::namedWindow( argv[1], CV_WINDOW_NORMAL );
  cv::imshow( argv[1], image );

  cvReleaseImage( &image );
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
