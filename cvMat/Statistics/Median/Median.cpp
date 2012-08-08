#include <iostream>

#include "cv.h"
#include "highgui.h"

cv::Scalar median (cv::Mat image)
{
    double m=(image.rows*image.cols)/2;
    int bin0=0, bin1=0, bin2=0;
    cv::Scalar med;
    med.val[0]=-1;
    med.val[1]=-1;
    med.val[2]=-1;
    int histSize = 256;
  float range[] = { 0, 256 } ;
  const float* histRange = { range };
  bool uniform = true;
  bool accumulate = false;
  cv::Mat hist0, hist1, hist2;
    std::vector<cv::Mat> channels;
  cv::split( image, channels );
  cv::calcHist( &channels[0], 1, 0, cv::Mat(), hist0, 1, &histSize, &histRange, uniform, accumulate );
    cv::calcHist( &channels[1], 1, 0, cv::Mat(), hist1, 1, &histSize, &histRange, uniform, accumulate );
    cv::calcHist( &channels[2], 1, 0, cv::Mat(), hist2, 1, &histSize, &histRange, uniform, accumulate );

    for (int i=0; i<256 && ( med.val[0]<0 || med.val[1]<0 || med.val[2]<0);i++)
    {
        bin0=bin0+cvRound(hist0.at<float>(i));
        bin1=bin1+cvRound(hist1.at<float>(i));
        bin2=bin2+cvRound(hist2.at<float>(i));
        if (bin0>m && med.val[0]<0)
            med.val[0]=i;
        if (bin1>m && med.val[1]<0)
            med.val[1]=i;
        if (bin2>m && med.val[2]<0)
            med.val[2]=i;
    }

    return med;
}

int main( int argc, char* argv[] )
{
  if( argc != 2)
    {
    std::cerr << "Usage: " << argv[0] << " <InputImage>" << std::endl;
    return EXIT_FAILURE;
    }

  cv::Mat image = cv::imread( argv[1] );
  if(!image.data)
    {
    return EXIT_FAILURE;
    }
    cv::Scalar med; //0:1st channel, 1:2nd channel and 2:3rd channel
    med=median(image);
    std::cout<<"Median: "<<med.val[0]<<std::endl;

    return 0;
}
