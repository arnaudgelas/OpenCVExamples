#include <iostream>

#include "cv.h"
#include "highgui.h"

cv::Scalar Kurtosis (cv::Mat image)
{
    cv::Scalar kurt,mean,stddev;
    kurt.val[0]=0;
    kurt.val[1]=0;
    kurt.val[2]=0;
    meanStdDev(image,mean,stddev,cv::Mat());
    int sum0, sum1, sum2;
    int N=image.rows*image.cols;
    float den0=0,den1=0,den2=0;

    for (int i=0;i<image.rows;i++)
    {
        for (int j=0;j<image.cols;j++)
        {
            sum0=image.ptr<uchar>(i)[3*j]-mean.val[0];
            sum1=image.ptr<uchar>(i)[3*j+1]-mean.val[1];
            sum2=image.ptr<uchar>(i)[3*j+2]-mean.val[2];

            kurt.val[0]+=sum0*sum0*sum0*sum0;
            kurt.val[1]+=sum1*sum1*sum1*sum1;
            kurt.val[2]+=sum2*sum2*sum2*sum2;
            den0+=sum0*sum0;
            den1+=sum1*sum1;
            den2+=sum2*sum2;
        }
    }

    kurt.val[0]= (kurt.val[0]*N*(N+1)*(N-1)/(den0*den0*(N-2)*(N-3)))-(3*(N-1)*(N-1)/((N-2)*(N-3)));
    kurt.val[1]= (kurt.val[1]*N/(den1*den1))-3;
    kurt.val[2]= (kurt.val[2]*N/(den2*den2))-3;

    return kurt;
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

    cv::Scalar kurt; //0:1st channel, 1:2nd channel and 2:3rd channel

    kurt=Kurtosis(image);
    std::cout<<"Kurtosis: "<<kurt.val[0]<<std::endl;
    return 0;
}
