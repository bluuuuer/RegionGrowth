#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

stack <Vec3b> seedd;

int Variance(const Mat image,const Mat visit,int r,int c){
    for(int j = 0;)
}

int RegionG8(const Mat image,Mat* visit,int r,int c,int s0,int *idex){
    int dis = Variance(image,visit,r,c);
    if(dis <= s0){
        visit.at<int>(r,c) = idex;
        seedd.push(image.at<Vec3b>(r,c));
    }
}

void RegionG(const Mat image,Mat* visit,int r,int c,int s0,int *idex){
    RegionG8(image,&visit,r-1,c,s0,idex);
    RegionG8(image,&visit,r,c-1,s0,idex);
    RegionG8(image,&visit,r,c+1,s0,idex);
    RegionG8(image,&visit,r+1,c,s0,idex);
    if(seedd.pop())
        RegionG(image,&visit,,idex)
    else
        return;
}

int main(int argc,char ** argv){
    Mat image = imread(argv[1],1);
    Mat visit = Mat::zeros(image.rows,image.cols,CV_8UC1);
    Mat result = Mat::zeros(image.rows,image.cols,image.type());
    int idex = 1;

    const float s0 = atof(argv[2]);
    for(int j = 1;j < image.rows - 1;j ++){
        for(int i = 1;i < image.cols - 1;i ++){
            if(visit.at<int>(j,i) == 0){
                seedd.push(image.at<Vec3b>(j,i));
                RegionG(image,&visit,j,i,s0,&idex);
                idex ++;
            }
        }
    }
    for(int i = 0;i < idex;i ++){
        Mat_<Vec3b>::const_iterator it = image.begin<Vec3b>();
        Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();
        Mat_<uchar>::const_iterator vi = visit.begin<uchar>();
        Mat_<Vec3b>::const_iterator itout = result.begin<Vec3b>();
        int sum[3] = {0,0,0};
        int count = 0;
        for(;it!=itend;it++,itout++,vi++){
            if(*vi == i){
                sum[0] += *it[0];
                sum[1] += *it[1];
                sum[2] += *it[2];
                count ++;
            }
        }
        sum[0] /= count;
        sum[1] /= count;
        sum[2] /= count;

        Mat_<Vec3b>::const_iterator it = image.begin<Vec3b>();
        Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();
        Mat_<uchar>::const_iterator vi = visit.begin<uchar>();
        Mat_<Vec3b>::const_iterator itout = result.begin<Vec3b>();
        for(;it!=itend;it++,itout++){
            if(*vi == i){
                *itout[0] = sum[0];
                *itout[1] = sum[1];
                *itout[2] = sum[2];
            }
        }
    }

    namedWindow("Result");
    namedWindow("Original");
    imshow("Original",image);
    imshow("Result",result);
}
