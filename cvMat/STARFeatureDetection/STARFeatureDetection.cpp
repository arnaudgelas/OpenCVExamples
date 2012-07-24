#include <iostream>

#include "cv.h"
#include "highgui.h"

int main( int argc, char* argv[] )
{
  if( argc != 7 )
    {
    std::cerr << "Usage: " << argv[0] << " <InputImage> <maxSize> <responseThreshold> <lineThresholdProjected> <lineThresholdBinarized> <suppressNonmaxSize>" << std::endl;
    return EXIT_FAILURE;
    }

  cv::Mat image = cv::imread( argv[1],0);
  if(!image.data)
    {
    return EXIT_FAILURE;
    }

  std::vector< cv::KeyPoint > featurePoints;

  // the full constructor initialized all the algorithm parameters:
  // maxSize - maximum size of the features. The following
  //      values of the parameter are supported:
  //      4, 6, 8, 11, 12, 16, 22, 23, 32, 45, 46, 64, 90, 128

  // responseThreshold - threshold for the approximated laplacian,
  //      used to eliminate weak features. The larger it is,
  //      the less features will be retrieved

  // lineThresholdProjected - another threshold for the laplacian to
  //      eliminate edges

  // lineThresholdBinarized - another threshold for the feature
  //      size to eliminate edges.
  // The larger the 2 threshold, the more points you get.

  int maxSize = atoi( argv[2] );
  int responseThreshold = atoi( argv[3] );
  int lineThresholdProjected = atoi( argv[4] );
  int lineThresholdBinarized = atoi( argv[5] );
  int suppressNonmaxSize = atoi( argv[6] );

  cv::StarDetector detector(  maxSize,
                              responseThreshold,
                              lineThresholdProjected,
                              lineThresholdBinarized,
                              suppressNonmaxSize);;

  detector( image, featurePoints );

  cv::Scalar color;
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

      cv::circle( image, it->pt, 10, color, thickness );
    }

  cv::namedWindow( argv[1], CV_WINDOW_NORMAL );
  cv::imshow( argv[1], image );

  cv::waitKey(0);

  return EXIT_SUCCESS;
}
