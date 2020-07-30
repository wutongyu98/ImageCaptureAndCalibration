#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include "popt_pp.h"
#include <opencv2/highgui/highgui_c.h>

using namespace std;
using namespace cv;

vector< vector< Point3f > > object_points;
vector< vector< Point2f > > image_points;
vector< Point2f > corners;
vector< vector< Point2f > > left_img_points;

Mat img, img_res;
Size im_size;
char* scale_file("/home/ulc/Desktop/stereo_vision/calibration/calib_imgs/rescale1/");

void setup_calibration(int board_width, int board_height, int num_imgs, 
                       float square_size, char* imgs_directory, char* imgs_filename,
                       char* extension) {
  Size board_size = Size(board_width, board_height);
  int board_n = board_width * board_height;

  for (int k = 1; k <= num_imgs; k++) {
    char img_file[100];
    char img_file_new[100];
    sprintf(img_file, "%s%s%d.%s", imgs_directory, imgs_filename, k, extension);
    
    sprintf(img_file_new, "%s%s%d.%s", scale_file, imgs_filename, k, extension);

    
    img = imread(img_file, 1);
    resize(img, img_res, Size(480, 360));
    imwrite(img_file_new, img_res);   
  }
}



int main(int argc, char const **argv)
{
  int board_width, board_height, num_imgs;
  float square_size;
  char* imgs_directory;
  char* imgs_filename;
  char* out_file;
  char* extension;

  static struct poptOption options[] = {
    { "board_width",'w',POPT_ARG_INT,&board_width,0,"Checkerboard width","NUM" },
    { "board_height",'h',POPT_ARG_INT,&board_height,0,"Checkerboard height","NUM" },
    { "num_imgs",'n',POPT_ARG_INT,&num_imgs,0,"Number of checkerboard images","NUM" },
    { "square_size",'s',POPT_ARG_FLOAT,&square_size,0,"Size of checkerboard square","NUM" },
    { "imgs_directory",'d',POPT_ARG_STRING,&imgs_directory,0,"Directory containing images","STR" },
    { "imgs_filename",'i',POPT_ARG_STRING,&imgs_filename,0,"Image filename","STR" },
    { "extension",'e',POPT_ARG_STRING,&extension,0,"Image extension","STR" },
    { "out_file",'o',POPT_ARG_STRING,&out_file,0,"Output calibration filename (YML)","STR" },
    POPT_AUTOHELP
    { NULL, 0, 0, NULL, 0, NULL, NULL }
  };

  POpt popt(NULL, argc, argv, options, 0);
  int c;
  while((c = popt.getNextOpt()) >= 0) {}

  setup_calibration(board_width, board_height, num_imgs, square_size,
                   imgs_directory, imgs_filename, extension);

  
  printf("Done Rescale\n");

  return 0;
}
