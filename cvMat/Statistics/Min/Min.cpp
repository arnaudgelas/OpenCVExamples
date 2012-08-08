#include <iostream>

#include "cv.h"
#include "highgui.h"

cv::Scalar Min (cv::Mat image)
{
    cv::Scalar min;
    min.val[0]=image.ptr<uchar>(0)[0];
    min.val[1]=image.ptr<uchar>(0)[1];
    min.val[2]=image.ptr<uchar>(0)[2];

    for (int i=0;i<image.rows;i++)
        for (int j=0;j<image.cols;j++)
        {
            if(min.val[0]>image.ptr<uchar>(i)[3*j])
                min.val[0]=image.ptr<uchar>(i)[3*j];
            if(min.val[1]>image.ptr<uchar>(i)[3*j+1])
                min.val[1]=image.ptr<uchar>(i)[3*j+1];
            if(min.val[2]>image.ptr<uchar>(i)[3*j+2])
                min.val[2]=image.ptr<uchar>(i)[3*j+2];
        }
    return min;
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

    cv::Scalar min; //0:1st channel, 1:2nd channel and 2:3rd channel

    min=Min(image);

    std::cout<<"Minimum: "<<min.val[0]<<std::endl;
    return 0;
}
