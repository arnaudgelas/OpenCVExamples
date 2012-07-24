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

  std::vector< cv::Vec2f > lines;

  // rho – Distance resolution of the accumulator in pixels
  double rho = 1.;

  // theta – Angle resolution of the accumulator in radians
  double theta = CV_PI / 180.;

  // threshold – The accumulator threshold parameter. Only those lines are returned that get enough votes ( >\texttt{threshold} )
  double threshold = 100.;

  // srn – For the multi-scale Hough transform it is the divisor for the distance
  // resolution rho .The coarse accumulator distance resolution will be rho and
  // the accurate accumulator resolution will be rho/srn . If both srn=0 and stn=0
  // then the classical Hough transform is used, otherwise both these parameters
  // should be positive.
  double srn = 0.;

  // stn – For the multi-scale Hough transform it is the divisor for the distance resolution theta
  double stn = 0.;

  cv::HoughLines( image, lines, rho, theta, threshold, srn, stn );

  for( size_t i = 0; i < lines.size(); i++ )
    {
    float rho = lines[i][0];
    float theta = lines[i][1];
    double a = cos(theta), b = sin(theta);
    double x0 = a*rho, y0 = b*rho;
    cv::Point pt1( cvRound(x0 + 1000*(-b)), cvRound(y0 + 1000*(a)));
    cv::Point pt2(cvRound( x0 - 1000*(-b)), cvRound(y0 - 1000*(a)));
    cvLine( image, pt1, pt2, cv::Scalar(0,0,255), 3, 8 );
    }

  cv::namedWindow( argv[1], CV_WINDOW_NORMAL );
  cvShowImage( argv[1], image );

  cvReleaseImage( &image );
  cv::waitKey(0);

  return EXIT_SUCCESS;
}
