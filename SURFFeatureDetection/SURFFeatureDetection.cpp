#include <iostream>

#include "cv.h"
#include "highgui.h"

int main( int argc, char* argv[] )
{
  if( argc != 6 )
    {
    std::cerr << "Usage: " << argv[0] << " <InputImage> <hessianThreshold> <nOctaves> <nOctaveLayers> <extended>" << std::endl;
    std::cerr << "nOctaves: 4" << std::endl;
    std::cerr << "nOctaveLayers: 2" << std::endl;
    std::cerr << "extended: 0" << std::endl;
    return EXIT_FAILURE;
    }

  IplImage* image = cvLoadImage( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
  if( !image )
    {
    std::cerr << "Could not load image file: " << argv[1] << std::endl;
    return EXIT_FAILURE;
    }

  std::vector< cv::KeyPoint > featurePoints;

  double hessianThreshold = atof( argv[2] );
  int nOctaves = atoi( argv[3] ); // 4
  int nOctaveLayers = atoi( argv[4] );// 2;
  bool extended = ( atoi( argv[5] ) != 0 );// false;

  cv::SURF detector = cv::SURF(hessianThreshold, nOctaves, nOctaveLayers, extended );
  detector( image, cv::Mat(), featurePoints );

  std::cout << featurePoints.size() << std::endl;

  CvScalar color;
  color.val[0] = 255.;

  int thickness = -1;

  size_t i = 1;

  for( std::vector< cv::KeyPoint >::const_iterator it = featurePoints.begin();
       it != featurePoints.end();
       ++it, ++i )
    {
      std::cout << "feature point " << i << std::endl;
      std::cout << "position: [ " << it->pt.x << ", " << it->pt.y << "]" << std::endl;
      std::cout << "size: " << it->size << std::endl;
      std::cout << "angle: " << it->angle << std::endl;
      std::cout << "response: " << it->response << std::endl;
      std::cout << "octave: " << it->octave << std::endl;

      std::cout << std::endl;

      cvCircle( image, it->pt, 10, color, thickness );
    }

  cv::namedWindow( argv[1], CV_WINDOW_NORMAL );
  cv::imshow( argv[1], image );

  cvReleaseImage( &image );
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
