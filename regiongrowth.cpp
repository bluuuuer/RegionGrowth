#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Region.h"
#include "Region.cpp"

using namespace cv;
using namespace std;

int main(int argc,char ** argv){
    XRegion x(argv[1],argv[2]);
    Mat image = imread(argv[1],1);
    Mat result = x.RegionG();

    namedWindow("Result");
    namedWindow("Original");
    imshow("Original",image);
    imshow("Result",result);
}
