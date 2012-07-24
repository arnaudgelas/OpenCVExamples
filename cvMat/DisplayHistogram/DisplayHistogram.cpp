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

    //image loaded as a grayscale image
  cv::Mat image = cv::imread( argv[1],0 );
  if(!image.data)
    {
    return EXIT_FAILURE;
    }

  
  int histSize = 256;
  float range[] = { 0, 256 } ;
  const float* histRange = { range };
  bool uniform = true;
  bool accumulate = false;
  cv::Mat hist;
  
  cv::calcHist( &image, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );
  
  //Draw the histogram
  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound( (double) hist_w/histSize );
  cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );
  
  normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
  
  for( int i = 1; i < histSize; i++ )
  {
      cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) , cv::Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ), cv::Scalar( 255, 255, 255), 2, 8, 0  );
  }
  
  //Display histogram
  cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
  cv::imshow( argv[1], histImage );

  cv::waitKey(0);

  return EXIT_SUCCESS;
}
