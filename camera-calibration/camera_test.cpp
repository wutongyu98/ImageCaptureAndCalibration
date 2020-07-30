#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include "popt_pp.h"

using namespace std;
using namespace cv;

int x = 0;
int w = 1440, h = 1080;

int main(int argc, char const *argv[])
{
  char* imgs_directory;
  char* extension;
  int im_width, im_height;

  VideoCapture cap1(2);
  VideoCapture cap2(0);
  cap1.set(CV_CAP_PROP_FRAME_WIDTH, w);
  cap1.set(CV_CAP_PROP_FRAME_HEIGHT, h);
  cap2.set(CV_CAP_PROP_FRAME_WIDTH, w);
  cap2.set(CV_CAP_PROP_FRAME_HEIGHT, h);
  Mat img1, img_res1, img2, img_res2, img_res1_col, img_res2_col;
  
  while (1) {



    cap1 >> img_res1;
    cap2 >> img_res2;
    
    resize(img_res1, img1, Size(w/2, h/2));
    resize(img_res2, img2, Size(w/2, h/2));
    imshow("Image11", img1);
    imshow("Image22", img2);
    
    
    imshow("Image1", img_res1);
    imshow("Image2", img_res2);
    

    
    
    waitKey(8);
   }
  return 0;
}
