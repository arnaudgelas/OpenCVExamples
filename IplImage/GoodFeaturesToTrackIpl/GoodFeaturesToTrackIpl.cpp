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

  std::vector< cv::Point2f > corners;

  // maxCorners – The maximum number of corners to return. If there are more corners
  // than that will be found, the strongest of them will be returned
  int maxCorners = 10;

  // qualityLevel – Characterizes the minimal accepted quality of image corners;
  // the value of the parameter is multiplied by the by the best corner quality
  // measure (which is the min eigenvalue, see cornerMinEigenVal() ,
  // or the Harris function response, see cornerHarris() ).
  // The corners, which quality measure is less than the product, will be rejected.
  // For example, if the best corner has the quality measure = 1500,
  // and the qualityLevel=0.01 , then all the corners which quality measure is
  // less than 15 will be rejected.
  double qualityLevel = 0.01;

  // minDistance – The minimum possible Euclidean distance between the returned corners
  double minDistance = 20.;

  // mask – The optional region of interest. If the image is not empty (then it
  // needs to have the type CV_8UC1 and the same size as image ), it will specify
  // the region in which the corners are detected
  cv::Mat mask;

  // blockSize – Size of the averaging block for computing derivative covariation
  // matrix over each pixel neighborhood, see cornerEigenValsAndVecs()
  int blockSize = 3;

  // useHarrisDetector – Indicates, whether to use operator or cornerMinEigenVal()
  bool useHarrisDetector = false;

  // k – Free parameter of Harris detector
  double k = 0.04;

  cv::goodFeaturesToTrack( image, corners, maxCorners, qualityLevel, minDistance, mask, blockSize, useHarrisDetector, k );

  for( size_t i = 0; i < corners.size(); i++ )
    {
    cvCircle( image, corners[i], 10, cv::Scalar( 255. ), -1 );
    }

  cv::namedWindow( argv[1], CV_WINDOW_NORMAL );
  cvShowImage( argv[1], image );

  cvReleaseImage( &image );
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
