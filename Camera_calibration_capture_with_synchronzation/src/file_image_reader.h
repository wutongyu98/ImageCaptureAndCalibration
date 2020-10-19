//
// Created by anacreon on 7/9/20.
//

#ifndef CTR_WS_FILE_IMAGE_READER_H
#define CTR_WS_FILE_IMAGE_READER_H

#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
#include "image_reader.h"

class FileImageReader : public ImageReader {
 public:
  explicit FileImageReader(std::string name);
  void SetExposureTime(int exposure_time) override { exposure_time_ = exposure_time; };

  auto GetSize() const -> cv::Size override;
  auto GetEncoding() const -> std::string override { return encoding_; };
  void ReadImg(cv::Mat& img_storage) override;
  void ResetCounter() override;

 protected:
 private:
  std::string name_;
  ros::NodeHandle nh_;
  int exposure_time_ = 5000;
  int width_ = 1440;
  int height_ = 1080;
  int frame_rate_ = 30;
  int counter_ = 1;
  std::string encoding_ = sensor_msgs::image_encodings::BGR8;

  struct FileSettings {
    std::string ros_namespace;
    std::string filename;
    std::string folder_path;
    std::string file_prefix;
    std::string file_suffix;
    std::string publish_topic;
    explicit FileSettings(const ros::NodeHandle& nh) : ros_namespace(nh.getNamespace()) {
      nh.param<std::string>("filename", filename, "");
      if (filename.empty()) {
        nh.param<std::string>("folder_path", folder_path, "");
        if (folder_path.empty()) {
          ROS_WARN_STREAM("'folder_path' of " << ros_namespace << " is empty");
        }
        nh.param<std::string>("file_prefix", file_prefix, "");
        if (file_prefix.empty()) {
          ROS_WARN_STREAM("'file_prefix' of " << ros_namespace << " is empty");
        }
        nh.param<std::string>("file_suffix", file_suffix, "");
        if (file_suffix.empty()) {
          ROS_WARN_STREAM("'file_suffix' of " << ros_namespace << " is empty");
        }
      }
      nh.param<std::string>("publish_topic", publish_topic, "");
      if (publish_topic.empty()) {
        ROS_WARN_STREAM("'publish_topic' of " << ros_namespace << " is empty");
      }
    }
  };
  FileSettings file_settings_;

  auto GetFilename() const -> std::string {
    if (!file_settings_.filename.empty()) {
      return file_settings_.filename;
    }
    if (!file_settings_.folder_path.empty() && !file_settings_.file_suffix.empty()) {
      return file_settings_.folder_path + file_settings_.file_prefix + std::to_string(counter_) +
             file_settings_.file_suffix;
    }
    return "";
  }
};

#endif  // CTR_WS_FILE_IMAGE_READER_H
