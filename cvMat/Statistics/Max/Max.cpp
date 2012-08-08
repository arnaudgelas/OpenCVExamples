#include <iostream>

#include "cv.h"
#include "highgui.h"


cv::Scalar Max (cv::Mat image)
{
    cv::Scalar max;
    max.val[0]=image.ptr<uchar>(0)[0];
    max.val[1]=image.ptr<uchar>(0)[1];
    max.val[2]=image.ptr<uchar>(0)[2];

    for (int i=0;i<image.rows;i++)
        for (int j=0;j<image.cols;j++)
        {
            if(max.val[0]<image.ptr<uchar>(i)[3*j])
                max.val[0]=image.ptr<uchar>(i)[3*j];
            if(max.val[1]<image.ptr<uchar>(i)[3*j+1])
                max.val[1]=image.ptr<uchar>(i)[3*j+1];
            if(max.val[2]<image.ptr<uchar>(i)[3*j+2])
                max.val[2]=image.ptr<uchar>(i)[3*j+2];
        }
    return max;
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

    cv::Scalar max; //0:1st channel, 1:2nd channel and 2:3rd channel

    max=Max(image);

    std::cout<<"Maximum: "<<max.val[0]<<std::endl;
    return 0;
}
