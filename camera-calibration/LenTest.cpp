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

  /*static struct poptOption options[] = {
    { "img_width",'w',POPT_ARG_INT,&im_width,0,"Image width","NUM" },
    { "img_height",'h',POPT_ARG_INT,&im_height,0,"Image height","NUM" },
    { "imgs_directory",'d',POPT_ARG_STRING,&imgs_directory,0,"Directory to save images in","STR" },
    { "extension",'e',POPT_ARG_STRING,&extension,0,"Image extension","STR" },
    POPT_AUTOHELP
    { NULL, 0, 0, NULL, 0, NULL, NULL }
  };

  POpt popt(NULL, argc, argv, options, 0);*/
  int c;
//   while((c = popt.getNextOpt()) >= 0) {}

  VideoCapture cap1(1);
  VideoCapture cap2(0);
  cap1.set(CV_CAP_PROP_FRAME_WIDTH, w);
  cap1.set(CV_CAP_PROP_FRAME_HEIGHT, h);
  cap2.set(CV_CAP_PROP_FRAME_WIDTH, w);
  cap2.set(CV_CAP_PROP_FRAME_HEIGHT, h);
  cout << " here 1" << endl;
//   cap1.set(CV_CAP_PROP_AUTO_EXPOSURE, 0.75);
//   cap2.set(CV_CAP_PROP_AUTO_EXPOSURE, 7);
//   
//   
//   cap1.set(CV_CAP_PROP_EXPOSURE, 1) ;
//   cap2.set(CV_CAP_PROP_EXPOSURE, 4) ;
  Mat img1, img_res1, img2, img_res2, img_res1_col, img_res2_col;
  int flag = 600, flag1 = 20;
  
//   while (x<60) 
  
  while (1) 
  {
	//cap1.set(CV_CAP_PROP_BRIGHTNESS,0.058);
	//cap1.set(CV_CAP_PROP_GAIN, 0.15);    
	//cap2.set(CV_CAP_PROP_BRIGHTNESS,0.058);
	//cap2.set(CV_CAP_PROP_GAIN, 0.15);
    cap1.grab();
    cap2.grab();
    cap1.retrieve(img_res1);
    cap2.retrieve(img_res2);
//     cap1 >> img_res1;
//     cap2 >> img_res2;
    //cvtColor(img_res1, img_res1, CV_BGR2GRAY);
    //cvtColor(img_res2, img_res2, CV_BGR2GRAY);
//     char img_file1[200], img_file2[200];
//     char title_image1[200] = "IMAGE1 time left is ", title_image2[200] = "IMAGE2 time left is ";
//     sprintf(img_file1, "%s%d.", title_image1, (flag/10));
//     sprintf(img_file2, "%s%d.", title_image2, (flag/10));

    resize(img_res1, img1, Size(w/2, h/2));
    resize(img_res2, img2, Size(w/2, h/2));
    imshow("Image1", img1);
    imshow("Image2", img2);
    
    //imshow("Image1", img_res1);
    //imshow("Image2", img_res2);
    
    
    waitKey(8);
//     flag1--;
//     if (flag1 == 0){
//     cout << img_file1 << endl;
//     flag1 = 20;
//     }
//     flag--;
//     //if (waitKey(30) > 0) {
//     if (flag == 1) {
//       x++;
//       std::string filename1 = "../calib_imgs/right" + std::to_string(x) + ".bmp";
//       std::string filename2 = "../calib_imgs/left" + std::to_string(x) + ".bmp";
//             
//       cout << "Saving img pair " << x << endl;
//       imwrite(filename1, img_res1);
//       imwrite(filename2, img_res2);
//       flag = 160;
//     }
  }
  return 0;
}
