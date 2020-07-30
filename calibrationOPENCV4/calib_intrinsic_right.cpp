#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include "popt_pp.h"
#include <fstream>
#include <cstdio>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/calib3d/calib3d_c.h>

using namespace std;
using namespace cv;

bool is_file_exist(const char * filename)
{
    
    std::ifstream infile(filename);
    return infile.good();
    
}
vector< vector< Point3f > > object_points;
vector< vector< Point2f > > image_points;
vector<int> img_index;
vector< Point2f > corners;
vector< vector< Point2f > > left_img_points;

Mat img, gray;
Size im_size;

void setup_calibration(int board_width, int board_height, int num_imgs, 
                       float square_size, char* imgs_directory, char* imgs_filename,
                       char* extension) 
{
    Size board_size = Size(board_width, board_height);
    int board_n = board_width * board_height;
    
    for (int k = 1; k <= num_imgs; k++) {
        char img_file[100], img_file_right[100];
        char* imgs_filename_right = "left";
        sprintf(img_file, "%s%s%d.%s", imgs_directory, imgs_filename, k, extension);
        sprintf(img_file_right, "%s%s%d.%s", imgs_directory, imgs_filename_right, k, extension);
        
        
        const char * filename = &img_file[0];
        if(is_file_exist(filename))
        {
            img = imread(img_file, 1);
            cv::cvtColor(img, gray, COLOR_BGR2GRAY);
            
            bool found = false;
            found = cv::findChessboardCorners(img, board_size, corners,
                                              CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
            if (found)
            {
                cornerSubPix(gray, corners, cv::Size(5, 5), cv::Size(-1, -1),
                             TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
                drawChessboardCorners(gray, board_size, corners, found);
                // cv::imshow("Corners on Chessboard", gray); // display image with plotted cornners
                // cv::waitKey(500);
                
            }
            
            vector< Point3f > obj;
            for (int i = 0; i < board_height; i++)
                for (int j = 0; j < board_width; j++)
                    obj.push_back(Point3f((float)j * square_size, (float)i * square_size, 0));
                
                if (found) {
                    //       cout << k << ". Found corners!" << endl;
                    img_index.push_back(k);
                    image_points.push_back(corners);
                    object_points.push_back(obj);
                }
                else
                {
                    
                    
                    if(remove(img_file) != 0 && remove(img_file_right) != 0)
                        perror("file deletion failed");
                    else
                        cout <<"not found corners are " << k << endl;    }
        }
        else
        {
            
            remove(img_file_right);
            
        }
    }
}
                       
double computeReprojectionErrors(const vector< vector< Point3f > >& objectPoints,
                                 const vector< vector< Point2f > >& imagePoints,
                                 const vector< Mat >& rvecs, const vector< Mat >& tvecs,
                                 const Mat& cameraMatrix , const Mat& distCoeffs) {
  vector< Point2f > imagePoints2;
  int i, totalPoints = 0;
  double totalErr = 0, err;
  vector< float > perViewErrors;
  perViewErrors.resize(objectPoints.size());

  for (i = 0; i < (int)objectPoints.size(); ++i) {
    projectPoints(Mat(objectPoints[i]), rvecs[i], tvecs[i], cameraMatrix,
                  distCoeffs, imagePoints2);
    err = norm(Mat(imagePoints[i]), Mat(imagePoints2), CV_L2);
    cout << "error for the " << img_index[i]  << "th image is " << err << endl;
    int n = (int)objectPoints[i].size();
    perViewErrors[i] = (float) std::sqrt(err*err/n);
    totalErr += err*err;
    totalPoints += n;
  }
  return std::sqrt(totalErr/totalPoints);
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

  printf("Starting Calibration\n");
  Mat K;
  Mat D;
  vector< Mat > rvecs, tvecs;
  int flag = 0;
  flag |= CV_CALIB_FIX_K4;
  flag |= CV_CALIB_FIX_K5;
  calibrateCamera(object_points, image_points, img.size(), K, D, rvecs, tvecs, flag);
	
  cout << "Calibration error: " << computeReprojectionErrors(object_points, image_points, rvecs, tvecs, K, D) << endl;

  FileStorage fs(out_file, FileStorage::WRITE);
  fs << "K" << K;
  fs << "D" << D;
  fs << "board_width" << board_width;
  fs << "board_height" << board_height;
  fs << "square_size" << square_size;
  printf("Done Calibration\n");

  return 0;
}
