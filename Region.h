#include <stdio.h>

class XRegion{
public:
    XRegion(char * filename,char * s);
    ~XRegion();
    Mat RegionG();
private:
    Mat image;
    Mat result;
    Mat visit;
    float s0;
    int idex;
    void RegionG8(int j,int i);
    float Variance(int j,int i);
};
