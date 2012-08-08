#include <iostream>

#include "cv.h"
#include "highgui.h"

cv::Scalar Skewness (cv::Mat image)
{
    cv::Scalar skewness,mean,stddev;
    skewness.val[0]=0;
    skewness.val[1]=0;
    skewness.val[2]=0;
    meanStdDev(image,mean,stddev,cv::Mat());
    int sum0, sum1, sum2;
    float den0=0,den1=0,den2=0;
    int N=image.rows*image.cols;

    for (int i=0;i<image.rows;i++)
    {
        for (int j=0;j<image.cols;j++)
        {
            sum0=image.ptr<uchar>(i)[3*j]-mean.val[0];
            sum1=image.ptr<uchar>(i)[3*j+1]-mean.val[1];
            sum2=image.ptr<uchar>(i)[3*j+2]-mean.val[2];

            skewness.val[0]+=sum0*sum0*sum0;
            skewness.val[1]+=sum1*sum1*sum1;
            skewness.val[2]+=sum2*sum2*sum2;
            den0+=sum0*sum0;
            den1+=sum1*sum1;
            den2+=sum2*sum2;
        }
    }

    skewness.val[0]=skewness.val[0]*sqrt(N)/(den0*sqrt(den0));
    skewness.val[1]=skewness.val[1]*sqrt(N)/(den1*sqrt(den1));
    skewness.val[2]=skewness.val[2]*sqrt(N)/(den2*sqrt(den2));

    return skewness;
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

    cv::Scalar skew; //0:1st channel, 1:2nd channel and 2:3rd channel

    skew=Skewness(image);

    std::cout<<"Skewness: "<<skew.val[0]<<std::endl;
    return 0;
}
