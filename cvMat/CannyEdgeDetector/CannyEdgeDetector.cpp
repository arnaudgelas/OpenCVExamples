#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

int main( int argc, char** argv )
{
  if( argc != 6 )
    {
    std::cerr << "Usage: " << argv[0] << "<InputImage> <OutputImage> <LowerBound (30)> <UpperBound (3*LowerBound)> <KernelSize (3)>" << std::endl;
    return EXIT_FAILURE;
    }

  cv::Mat src = cv::imread( argv[1], 0 );

  if( !src.data )
    {
    return EXIT_FAILURE;
    }

  int lowThreshold = atoi( argv[3] );
  int highThreshold = atoi( argv[4] );
  int kernelSize = atoi( argv[5] );

  cv::Mat output;

  cv::blur( src, output, cv::Size( kernelSize, kernelSize ) );
  cv::Canny( output, output, lowThreshold, highThreshold, kernelSize );

  cv::namedWindow( "canny", CV_WINDOW_AUTOSIZE );
  cv::imshow( "canny", output );

  cv::imwrite( argv[2], output );

  cv::waitKey(0);

  return EXIT_SUCCESS;
}
