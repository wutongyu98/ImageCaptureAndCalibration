#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int w = 1440, h = 1080;

int main()
{


  VideoCapture cap1(1);
  VideoCapture cap2(0);
  cap1.set(CV_CAP_PROP_FRAME_WIDTH, w);
  cap1.set(CV_CAP_PROP_FRAME_HEIGHT, h);
  cap2.set(CV_CAP_PROP_FRAME_WIDTH, w);
  cap2.set(CV_CAP_PROP_FRAME_HEIGHT, h);
//   cap1.set(CV_CAP_PROP_AUTO_EXPOSURE, 0);
//   cap1.set(CV_CAP_PROP_EXPOSURE, -4);
  
  Mat img1, img_res1, img2, img_res2;
  
  while (1) 
  {
    cap1.grab();
    cap2.grab();
    cap1.retrieve(img_res1);
    cap2.retrieve(img_res2);

    //resize(img_res1, img1, Size(w/2, h/2));
    //resize(img_res2, img2, Size(w/2, h/2));
    imshow("Image1", img_res1);
    imshow("Image2", img_res2);
    waitKey(1);
  }
  
  
  return 0;
  
}
