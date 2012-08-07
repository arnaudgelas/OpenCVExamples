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

cv::Scalar mode (cv::Mat image)
{
    double m=(image.rows*image.cols)/2;
    int bin0=0, bin1=0, bin2=0;
    cv::Scalar mode;
    mode.val[0]=-1;
    mode.val[1]=-1;
    mode.val[2]=-1;
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

    for (int i=0; i<256 ;i++)
    {
        if (bin0<cvRound(hist0.at<float>(i)))
        {
            bin0=cvRound(hist0.at<float>(i));
            mode.val[0]=i;
        }
        if (bin1<cvRound(hist1.at<float>(i)))
        {
            bin1=cvRound(hist1.at<float>(i));
            mode.val[1]=i;
        }
        if (bin2<cvRound(hist2.at<float>(i)))
        {
            bin2=cvRound(hist2.at<float>(i));
            mode.val[2]=i;
        }
    }

    return mode;
}

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

 /*   if (stddev.val[0]>0)
        skewness.val[0]/=(N*stddev.val[0]*stddev.val[0]*stddev.val[0]);
    else
        std::cout<<"Channel 0: No skewness, Variance=0"<<std::endl;
    if (stddev.val[1]>0)
        skewness.val[1]/=(N*stddev.val[1]*stddev.val[1]*stddev.val[1]);
    else
        std::cout<<"Channel 1: No skewness, Variance=0"<<std::endl;
    if (stddev.val[2]>0)
        skewness.val[2]/=(N*stddev.val[2]*stddev.val[2]*stddev.val[2]);
    else
        std::cout<<"Channel 2: No skewness, Variance=0"<<std::endl;*/

    skewness.val[0]=skewness.val[0]*sqrt(N)/(den0*sqrt(den0));
    skewness.val[1]=skewness.val[1]*sqrt(N)/(den1*sqrt(den1));
    skewness.val[2]=skewness.val[2]*sqrt(N)/(den2*sqrt(den2));

    return skewness;
}

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

   /* if (stddev.val[0]>0)
        kurt.val[0]=(kurt.val[0]/(N*stddev.val[0]*stddev.val[0]*stddev.val[0]*stddev.val[0]))-3;
    else
        std::cout<<"Channel 0: No kurtosis, Variance=0"<<std::endl;
    if (stddev.val[1]>0)
        kurt.val[1]=(kurt.val[1]/(N*stddev.val[1]*stddev.val[1]*stddev.val[1]*stddev.val[1]))-3;
    else
        std::cout<<"Channel 1: No kurtosis, Variance=0"<<std::endl;
    if (stddev.val[2]>0)
        kurt.val[2]=(kurt.val[2]/(N*stddev.val[2]*stddev.val[2]*stddev.val[2]*stddev.val[2]))-3;
    else
        std::cout<<"Channel 2: No kurtosis, Variance=0"<<std::endl;*/

    kurt.val[0]= (kurt.val[0]*N*(N+1)*(N-1)/(den0*den0*(N-2)*(N-3)))-(3*(N-1)*(N-1)/((N-2)*(N-3)));
    kurt.val[1]= (kurt.val[1]*N/(den1*den1))-3;
    kurt.val[2]= (kurt.val[2]*N/(den2*den2))-3;

    return kurt;
}

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
  if( argc != 3)
    {
    std::cerr << "Usage: " << argv[0] << " <InputImage>" << std::endl;
    return EXIT_FAILURE;
    }

  cv::Mat image = cv::imread( argv[1] );
  if(!image.data)
    {
    return EXIT_FAILURE;
    }
  cv::Mat image_gray = cv::imread( argv[1],0 );
  if(!image_gray.data)
    {
    return EXIT_FAILURE;
    }
  cv::Mat mask = cv::imread( argv[2],0 );
  if(!mask.data)
    {
    return EXIT_FAILURE;
    }

    cv::Scalar mean,stddev,med,mod,min,max,skew,kurt,ent; //0:1st channel, 1:2nd channel and 2:3rd channel

    meanStdDev(image,mean,stddev,cv::Mat());
    med=median(image);
    mod=mode(image);
    min=Min(image);
    max=Max(image);
    skew=Skewness(image);
    kurt=Kurtosis(image);
    ent=Entropy(image);

    std::cout<<"Mean: "<<mean.val[0]<<std::endl;
    std::cout<<"Standard deviation: "<<stddev.val[0]<<std::endl;
    std::cout<<"Variance: "<<stddev.val[0]*stddev.val[0]<<std::endl;
    std::cout<<"Median: "<<med.val[0]<<std::endl;
    std::cout<<"Mode: "<<mod.val[0]<<std::endl;
    std::cout<<"Minimum: "<<min.val[0]<<std::endl;
    std::cout<<"Maximum: "<<max.val[0]<<std::endl;
    std::cout<<"Skewness: "<<skew.val[0]<<std::endl;
    std::cout<<"Kurtosis: "<<kurt.val[0]<<std::endl;
    std::cout<<"Entropy: "<<ent.val[0]<<std::endl;
    return 0;
}
