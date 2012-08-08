#include <iostream>

#include "cv.h"
#include "highgui.h"


cv::Scalar Entropy (cv::Mat image)
{

    std::vector<cv::Mat> channels;
  cv::split( image, channels );

  int histSize = 256;
  float range[] = { 0, 256 } ;
  const float* histRange = { range };
  bool uniform = true;
  bool accumulate = false;
  cv::Mat hist0, hist1, hist2;

  cv::calcHist( &channels[0], 1, 0, cv::Mat(), hist0, 1, &histSize, &histRange, uniform, accumulate );
  cv::calcHist( &channels[1], 1, 0, cv::Mat(), hist1, 1, &histSize, &histRange, uniform, accumulate );
  cv::calcHist( &channels[2], 1, 0, cv::Mat(), hist2, 1, &histSize, &histRange, uniform, accumulate );

    //frequency
    float f0=0, f1=0, f2=0;
    for (int i=0;i<histSize;i++)
    {
        f0+=hist0.at<float>(i);
        f1+=hist1.at<float>(i);
        f2+=hist2.at<float>(i);
    }

    //entropy
    cv::Scalar e;
    e.val[0]=0;
    e.val[1]=0;
    e.val[2]=0;
    // e0=0, e1=0, e2=0;
    float p0, p1, p2;

    for (int i=0;i<histSize;i++)
    {
        p0=abs(hist0.at<float>(i))/f0;
        p1=abs(hist1.at<float>(i))/f1;
        p2=abs(hist2.at<float>(i))/f2;
        if (p0!=0)
            e.val[0]+=-p0*log10(p0);
        if (p1!=0)
            e.val[1]+=-p1*log10(p1);
        if (p2!=0)
            e.val[2]+=-p2*log10(p2);
    }

    return e;
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

    cv::Scalar ent; //0:1st channel, 1:2nd channel and 2:3rd channel

    ent=Entropy(image);

    std::cout<<"Entropy: "<<ent.val[0]<<std::endl;

    return 0;
}
