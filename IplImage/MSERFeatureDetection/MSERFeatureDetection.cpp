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

  std::vector< std::vector< cv::Point > > featurePoints;

  /*
( int _delta, int _min_area, int _max_area,
          float _max_variation, float _min_diversity,
          int _max_evolution, double _area_threshold,
          double _min_margin, int _edge_blur_size );
  */

  cv::MSER detector;

  detector( image, featurePoints, cv::Mat() );

  CvScalar color;
  color.val[0] = 255.;

  int thickness = -1;

  size_t i = 1;

  for( std::vector< std::vector< cv::Point > >::const_iterator it = featurePoints.begin();
       it != featurePoints.end();
       ++it, ++i )
    {
      size_t j = 1;

      for( std::vector< cv::Point >::const_iterator pIt = it->begin();
           pIt != it->end();
           ++pIt, ++j )
      {
        std::cout << "feature point " << i <<" * " << j << std::endl;
        std::cout << "position: [ " << pIt->x << ", " << pIt->y << "]" << std::endl;
        std::cout << std::endl;

        cvCircle( image, *pIt, 10, color, thickness );
      }
    }

  cv::namedWindow( argv[1], CV_WINDOW_NORMAL );
  cv::imshow( argv[1], image );

  cvReleaseImage( &image );
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
