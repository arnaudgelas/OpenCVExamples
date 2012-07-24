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

  cv::Mat image = cv::imread( argv[1],1);
  if(!image.data)
    {
    return EXIT_FAILURE;
    }
    

  cv::Point center;
  center.x = image.rows/ 2;
  center.y = image.cols / 2;
  int radius = 10;

  cv::Scalar color;
  color.val[0] = 255.;

  int thickness = atoi( argv[2] ); // if thickness < 0, the circle is filled

  cv::circle( image, center, radius, color, thickness );

  cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
  cv::imshow( argv[1], image );
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
