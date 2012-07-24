#include <iostream>
#include <cv.h>
#include <highgui.h>

int main(int argc, char **argv)
{
  if( argc != 3 )
    {
    std::cerr << "Usage: " << argv[0] << "<InputImage> <NumberOfClusters>" << std::endl;
    return EXIT_FAILURE;
    }

  int NumberOfClusters = atoi( argv[2] );

  // (1)load a specified file as a 3-channel color image
  cv::Mat src_img = cv::imread( argv[1] );

  if(!src_img.data)
    {
    return EXIT_FAILURE;
    }

  // (2)reshape the image to be a 1 column matrix
  cv::Mat points;
  src_img.convertTo(points, CV_32FC3);
  points = points.reshape(3, src_img.rows*src_img.cols);

  // (3)run k-means clustering algorithm to segment pixels in RGB color space
  cv::Mat_<int> clusters(points.size(), CV_32SC1);
  cv::Mat centers;
  cv::kmeans(points, NumberOfClusters, clusters,
   cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0), 1, cv::KMEANS_PP_CENTERS, centers);

  // (4)make a each centroid represent all pixels in the cluster
  cv::Mat dst_img(src_img.size(), src_img.type());
  cv::MatIterator_<cv::Vec3f> itf = centers.begin<cv::Vec3f>();
  cv::MatIterator_<cv::Vec3b> itd = dst_img.begin<cv::Vec3b>(), itd_end = dst_img.end<cv::Vec3b>();
  for(int i=0; itd != itd_end; ++itd, ++i) {
    cv::Vec3f color = itf[clusters(1,i)];
    (*itd)[0] = cv::saturate_cast<uchar>(color[0]);
    (*itd)[1] = cv::saturate_cast<uchar>(color[1]);
    (*itd)[2] = cv::saturate_cast<uchar>(color[2]);
  }

  // (5)show source and destination image, and quit when any key pressed
  cv::namedWindow("src_img", CV_WINDOW_AUTOSIZE);
  imshow("src_img", src_img);
  cv::namedWindow("dst_img", CV_WINDOW_AUTOSIZE);
  imshow("dst_img", dst_img);
  cv::waitKey(0);

  cv::imwrite( "kmeans_output.png", dst_img );

  return 0;
}
