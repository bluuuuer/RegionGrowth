#include "XRegion.h"

using namespace cv;

XRegion::XRegion(char* filename,char* s){
    image = imread(filename);
    result = Mat::zeros(image.rows,image.cols,image.type());
    visit = Mat::zeros(image.rows,image.cols,CV_8UC1);
    s0 = atof(s);
    idex = 1;
}

XRegion::~XRegion(){
}

Mat XRegion::RegionG(){
    for(int j = 0;j < image.rows;j ++)
        for (int i = 0;i < image.cols;i ++)
            if(visit.at<uchar>(j,i) == 0){
                RegionG8(j,i);
                idex ++;
            }

    for(int i = 1;i < idex;i ++){
        Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
        Mat_<Vec3b>::iterator itend = image.end<Vec3b>();
        Mat_<uchar>::iterator vi = visit.begin<uchar>();
        int sum[3] = {0,0,0};
        int count = 0;
        for(;it != itend;it ++,vi ++){
            if(*vi == i){
                sum[0] += (*it)[0];
                sum[1] += (*it)[1];
                sum[2] += (*it)[2];
                count ++;
            }
        }
        sum[0] /= count;
        sum[1] /= count;
        sum[2] /= count;

        it = image.begin<Vec3b>();
        vi = visit.begin<uchar>();
        Mat_<Vec3b>::iterator itout = result.begin<Vec3b>();
        for(;it != itend;it ++,itout ++,vi ++){
            if(*vi == i){
                (*itout)[0] = sum[0];
                (*itout)[1] = sum[1];
                (*itout)[2] = sum[2];
            }
        }
    }
    return result;
}

void XRegion::RegionG8(int j,int i){
    float dis = Variance(j,i);
    if(dis <= s0)
        visit.at<uchar>(j,i) = idex;

    if(j-1 >= 0)
        if(visit.at<uchar>(j-1,i) == 0)
            RegionG8(j-1,i);
    if(i-1 >= 0)
        if(visit.at<uchar>(j,i-1) == 0)
            RegionG8(j,i-1);
    if(i+1 <= image.cols)
        if(visit.at<uchar>(j,i+1) == 0)
            RegionG8(j,i+1);
    if(j+1 <= image.rows)
        if(visit.at<uchar>(j+1,i) == 0)
            RegionG8(j+1,i);
    return;
}

float XRegion::Variance(int j,int i){
    return 0.0;
}
