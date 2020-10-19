//
// Created by anacreon on 7/9/20.
//

#ifndef CTR_WS_TCAM_IMAGE_READER_H
#define CTR_WS_TCAM_IMAGE_READER_H

// #include <sensor_msgs/image_encodings.h>
#include "tcamimage.h"
#include "image_reader.h"

class TCAMImageReader : public ImageReader {
 public:
  enum class CamType { kTCAMMaster, kTCAMFollower };
  TCAMImageReader(std::string name, std::string serial_num, CamType cam_type = CamType::kTCAMFollower);
  void SetExposureTime(int exposure_time) override;
//   void friend SetGain(int gain);
  auto GetSize() const -> cv::Size override;
  auto GetEncoding() const -> std::string { return encoding_; };
  void Trigger() override;
  void ReadImg(cv::Mat& img_storage) override;
  void ResetCounter() override{};

 protected:
 private:
  std::string name_;
  std::string serial_num_;
  TcamImage cam_;
  CamType cam_type_ = CamType::kTCAMFollower;
  int exposure_time_ = 5000;
  int width_ = 1440;
  int height_ = 1080;
  int frame_rate_ = 30;
  int counter_ = 1;
  std::string encoding_ = "CV_8UC4";
//   std::string encoding_ = sensor_msgs::image_encodings::BGRA8;
  cv::Mat img_;
};

#endif  // CTR_WS_TCAM_IMAGE_READER_H
