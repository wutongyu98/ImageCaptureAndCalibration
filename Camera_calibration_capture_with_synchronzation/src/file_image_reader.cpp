//
// Created by anacreon on 7/9/20.
//
#include "file_image_reader.h"
#include <iostream>
#include <opencv2/opencv.hpp>

FileImageReader::FileImageReader(std::string name)
    : name_(std::move(name)), nh_("kitti_stereo/" + name_), file_settings_(nh_) {}

auto FileImageReader::GetSize() const -> cv::Size { return cv::Size(width_, height_); }

void FileImageReader::ReadImg(cv::Mat& img_storage) {
  img_storage = cv::imread(GetFilename(), CV_LOAD_IMAGE_COLOR);
  counter_++;
}

void FileImageReader::ResetCounter() { counter_ = 1; }
