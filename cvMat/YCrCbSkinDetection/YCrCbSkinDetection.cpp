#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "cv.h"
#include "highgui.h"

cv::Mat histogram(cv::Mat image, int threshMin, int threshMax,cv::Mat mask, int flag)
{
	int rangeMax;
	if(flag==0)
		rangeMax=240;
	else
		rangeMax=235;
	int histSize = rangeMax-16;
  float range[] = { 16, rangeMax } ;
  const float* histRange = { range };
  bool uniform = true;
  bool accumulate = false;
  cv::Mat hist;

  cv::calcHist( &image, 1, 0, mask, hist, 1, &histSize, &histRange, uniform, accumulate );

  //Draw the histogram
  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound( (double) hist_w/histSize );
  cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

  normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

  for( int i = 1; i < histSize; i++ )
  {
      cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) , cv::Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ), cv::Scalar( 255, 255, 255), 2, 8, 0  );
  }
  cv::line( histImage, cv::Point( bin_w*threshMin, hist_h ) , cv::Point( bin_w*threshMin, 0 ), cv::Scalar( 0, 0, 255), 2, 5, 0  );
	cv::line( histImage, cv::Point( bin_w*threshMax, hist_h ) , cv::Point( bin_w*threshMax, 0 ), cv::Scalar( 0, 255, 0), 2, 5, 0  );
  
	return histImage;
}

int main( int argc, char* argv[] )
{
	if( argc < 3 )
	{
		std::cerr << "Usage: " << argv[0] << " <InputImage>	<OutputImage>	" << std::endl;
		std::cerr << "Options: " << std::endl;
		std::cerr << "<YMinThreshold>	<YMaxThreshold>	<CrMinThreshold>	<CrMaxThreshold>	<CbMinThreshold>	<CbMaxThreshold>" << std::endl;
		return EXIT_FAILURE;
	}
    
  cv::Mat image = cv::imread( argv[1] );
  if(!image.data)
   {
    return EXIT_FAILURE;
   }
    
  cv::Mat YCrCb;
  cv::Mat dst=image;
	cv::Mat mask = cv::Mat::zeros(image.rows,image.cols, CV_8UC1);

  cv::cvtColor( image, YCrCb, CV_BGR2YCrCb );

		//Default values
		int YMin=-1;
		int YMax=256;
		int CrMin=133;
		int CrMax=173;
		int CbMin=77;
		int CbMax=127;
	if(argc==9)
	{
		YMin=atoi(argv[3]);
		YMax=atoi(argv[4]);
		CrMin=atoi(argv[5]);
		CrMax=atoi(argv[6]);
		CbMin=atoi(argv[7]);
		CbMax=atoi(argv[8]);
	}

  for (int i=0; i<image.rows; i++)
    for (int j=0; j<image.cols; j++)
    {
	
			if(YCrCb.ptr<uchar>(i)[3*j]<YMax && YCrCb.ptr<uchar>(i)[3*j]>YMin && YCrCb.ptr<uchar>(i)[3*j+1]<CrMax && YCrCb.ptr<uchar>(i)[3*j+1]>CrMin && YCrCb.ptr<uchar>(i)[3*j+2]<CbMax && YCrCb.ptr<uchar>(i)[3*j+2]>CbMin)
			{
				dst.ptr<uchar>(i)[3*j]=0;
				dst.ptr<uchar>(i)[3*j+1]=0;
				dst.ptr<uchar>(i)[3*j+2]=0;
				mask.at<uchar>(i,j)=255;
			}
    }

  std::vector<cv::Mat> YCrCb_planes;
  cv::split( YCrCb, YCrCb_planes );
	
  cv::Mat histCr=histogram(YCrCb_planes[1],CrMin,CrMax,cv::Mat(),0);
	cv::Mat histCb=histogram(YCrCb_planes[2],CbMin,CbMax,cv::Mat(),0);
	//Binary mask histogram
	/*cv::Mat histCr=histogram(YCrCb_planes[1],CrMin,CrMax,mask,0);
	cv::Mat histCb=histogram(YCrCb_planes[2],CbMin,CbMax,mask,0);*/

	//Y histogram
	/*cv::Mat histY=histogram(YCrCb_planes[0],YMin,YMax,cv::Mat(),1);
	cv::namedWindow( "Y histogram", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Y histogram", histY );*/
	
	cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
  cv::imshow( argv[1], dst );
	cv::namedWindow( "Cr histogram", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Cr histogram", histCr );
  cv::namedWindow( "Cb histogram", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Cb histogram", histCb );
	//Display mask
	/*cv::namedWindow( "mask", CV_WINDOW_AUTOSIZE );
  cv::imshow( "mask", mask );*/
  cv::waitKey(0);
  
  cv::imwrite(argv[2],dst);
  return 0;
}