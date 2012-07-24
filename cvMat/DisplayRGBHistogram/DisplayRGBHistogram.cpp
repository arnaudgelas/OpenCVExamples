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

 
  cv::Mat image = cv::imread( argv[1],1);
  if(!image.data)
    {
    return EXIT_FAILURE;
    }

  std::vector<cv::Mat> bgr_planes;
  cv::split( image, bgr_planes );
  
  int histSize = 256;
  float range[] = { 0, 256 } ;
  const float* histRange = { range };
  bool uniform = true;
  bool accumulate = false;
  cv::Mat b_hist, g_hist, r_hist;
  
  cv::calcHist( &bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
  cv::calcHist( &bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
  cv::calcHist( &bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
  
  //Draw the histograms
  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound( (double) hist_w/histSize );
  cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );
  
  normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
  normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
  normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
  
  for( int i = 1; i < histSize; i++ )
  {
      cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) , cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ), cv::Scalar( 255, 0, 0), 2, 8, 0  );
      cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) , cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ), cv::Scalar( 0, 255, 0), 2, 8, 0  );
      cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) , cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ), cv::Scalar( 0, 0, 255), 2, 8, 0  );
  }
  
  //Display histogram
  cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
  cv::imshow( argv[1], histImage );

  cv::waitKey(0);

  return EXIT_SUCCESS;
}
