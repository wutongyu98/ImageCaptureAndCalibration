#include <iostream>
#include <string>
#include <sys/stat.h> // using this header for directory operation

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>

#include "tcamimage.h"
#include <unistd.h>

#include <vector>
#include "image_reader.h"
#include "input_arg_parser.h"
#include "tcam_image_reader.h"

using namespace gsttcam;
using namespace std;
using namespace cv;
int w = 1440, h = 1080, x = 0;
int flag = 230; // change this number to increase the counting down time for starting image saving 
int flag1 = 5;

template <typename T>
struct LRPair {
    T left;
    T right;
    LRPair() = default;
    LRPair(T&& l, T&& r) : left(std::forward<T>(l)), right(std::forward<T>(r)){};
};

LRPair<ImageReader*> cameras;

auto DirExists(const std::string& path) -> bool {
  struct stat info;

  if (stat(path.c_str(), &info) != 0) {
    return false;
  }
  return (info.st_mode & S_IFDIR) != 0U;
}

int main(int argc, char** argv)
{
    gst_init(&argc, &argv);
    std::vector<std::string> camera_id;
    
    
    auto device_list = gsttcam::get_device_list();
    
    if (device_list.empty()) {
        std::cout << "No Cameras Found" << std::endl;
    } else {
        std::cout << "Cameras:" << std::endl;
        for (auto& device : device_list) {
            std::cout << "  - Name : " << device.name << "\n"
            << "    Serial: " << device.serial << "\n"
            << "    Ident: " << device.identifier << "\n"
            << "    Connection Type: " << device.connection_type << std::endl;
            camera_id.emplace_back(device.serial);
        }
    }
    
    
    cameras.left =  static_cast<ImageReader*>(new TCAMImageReader{"left", camera_id[0], TCAMImageReader::CamType::kTCAMMaster});
    cameras.right = static_cast<ImageReader*>(new TCAMImageReader{"right", camera_id[1]});
    
    LRPair<cv::Mat> frames;
    std::string output_path = "../calib_imgs/";
    if (!DirExists(output_path)) {
        if (mkdir(output_path.c_str(), ACCESSPERMS) == -1) {
            std::cerr << "Error Creating Directory \'" << output_path << "\':  " << strerror(errno) << std::endl;
        } else {
            std::cout << "Directory \'" << output_path << "\' created\n";
        }
    }
    
    while (x<50) {
        
        cameras.left->Trigger();
        cameras.right->Trigger();
        
        cameras.left->ReadImg(frames.left);
        cameras.right->ReadImg(frames.right);
        
        if(!frames.left.empty() & !frames.right.empty())
        {
            cv::Mat img1, img2;
            char img_file1[200], img_file2[200];
            char title_image1[200] = "IMAGE1 time left is ", title_image2[200] = "IMAGE2 time left is ";
            sprintf(img_file1, "%s%d.", title_image1, (flag/5));
            sprintf(img_file2, "%s%d.", title_image2, (flag/5));
            int scale_ratio = 2;
            resize(frames.left, img1, Size(w/scale_ratio, h/scale_ratio));
            resize(frames.right, img2, Size(w/scale_ratio, h/scale_ratio));
            imshow("Image1", img1);
            imshow("Image2", img2);
            
            
            waitKey(1);
            flag1--;    
            if (flag1 == 0){
                cout << img_file1 << endl;
                flag1 = 5;
            }
            flag--;
            //if (waitKey(30) > 0) {
            if (flag == 1) {
                x++;
                std::string filename1 = "../calib_imgs/right" + std::to_string(x) + ".jpg";
                std::string filename2 = "../calib_imgs/left" + std::to_string(x) + ".jpg";
                
                cout << "Saving img pair " << x << endl;
                imwrite(filename1, frames.left);
                imwrite(filename2, frames.right);
                flag = 60; // change this number to increase/reduce the counting down time between two images
            }
        }
        else
            cout << "EMPTY FRAME!" << endl;
        
    }
    return 0;
}
