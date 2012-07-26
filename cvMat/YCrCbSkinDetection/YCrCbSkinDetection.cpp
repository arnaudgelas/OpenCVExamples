#include <iostream>

#include "cv.h"
#include "highgui.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
    {
    std::cerr << "Usage: " << argv[0] << " <InputImage> <OutputImage>" << std::endl;
    return EXIT_FAILURE;
    }

  cv::Mat image = cv::imread( argv[1] );
  if(!image.data)
    {
    return EXIT_FAILURE;
    }
    
  cv::Mat YCrCb;
  cv::Mat dst=image;

  cv::cvtColor( image, YCrCb, CV_BGR2YCrCb );

 // std::vector<cv::Mat> YCrCb_planes;
 // cv::split( YCrCb, YCrCb_planes );
 // cv::Vec3b intensity;
  //uchar Cr, Cb;
  
  for (int i=0; i<image.rows; i++)
    for (int j=0; j<image.cols; j++)
    {
      /*intensity=image.at<cv::Vec3b><uchar>(i, j);
      if(intensity.val[1]<173 && intensity.val[1]>133 && intensity.val[2]<127 && intensity.val[2]>77)
      {
	intensity=dst.at<cv::Vec3b><uchar>(i, j);
	intensity.val[0]=0;
	intensity.val[1]=0;
	intensity.val[2]=0;
      }*///std::cout<<"YCrCb_planes[1]"<<YCrCb_planes[1].at<uchar>(i,j)<<std::endl;
    //  if(YCrCb_planes[1].at<uchar>(i,j)<173 && YCrCb_planes[1].at<uchar>(i,j)>133 && YCrCb_planes[1].at<uchar>(i,j)<127 && YCrCb_planes[1].at<uchar>(i,j)>77)
    //  {
	/*dst.at<uchar>(i,j)=(0,0,0);
	intensity=dst.at<cv::Vec3b>(i, j);
	std::cout<<"intensity.val[0]"<<intensity.val[0]<<std::endl;*/
	/*dst.ptr<uchar>(i)[3*j]=0;
	dst.ptr<uchar>(i)[3*j+1]=0;
	dst.ptr<uchar>(i)[3*j+2]=0;*/
	//elem = matrix.ptr<type>(i)[Nc*j+c] elem = matrix.ptr<type>(i)[Nc*j+c] 
	//std::cout<<"dst.ptr<uchar>(i)[3j]"<<dst.ptr<uchar>(i)[3*j]<<std::endl;
	//std::cout<<"flag"<<std::endl;
   //   }
	
	if(YCrCb.ptr<uchar>(i)[3*j+1]<173 && YCrCb.ptr<uchar>(i)[3*j+1]>133 && YCrCb.ptr<uchar>(i)[3*j+2]<127 && YCrCb.ptr<uchar>(i)[3*j+2]>77)
	{
	dst.ptr<uchar>(i)[3*j]=0;
	dst.ptr<uchar>(i)[3*j+1]=0;
	dst.ptr<uchar>(i)[3*j+2]=0;
	}
    }
    
  cv::namedWindow( argv[1], CV_WINDOW_AUTOSIZE );
  cv::imshow( argv[1], dst );
  cv::waitKey(0);
  
  cv::imwrite(argv[2],dst);
  return 0;
}