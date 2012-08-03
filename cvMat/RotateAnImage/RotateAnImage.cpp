#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main( int argc, char* argv[] )
{
  cv::Mat src = cv::imread( argv[1] );

  if( !src.data )
    {
    return EXIT_FAILURE;
    }

  int Xcenter = atoi( argv[2] );
  int Ycenter = atoi( argv[3] );
  double angle = atof( argv[4] );
  double scale = 1.;

  cv::Mat rotationMatrix = cv::getRotationMatrix2D(
    cv::Point( Xcenter, Ycenter ),
    angle,
    scale );

  cv::Mat output;
  cv::warpAffine( src, output, rotationMatrix, cv::Size( src.rows, src.cols ) );

  cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
  cv::imshow( argv[1], output );

  cv::waitKey(0);

  return EXIT_SUCCESS;
}
