//
// Created by anacreon on 7/9/20.
//
#include "tcam_image_reader.h"
#include <iostream>
#include <utility>

TCAMImageReader::TCAMImageReader(std::string name, std::string serial_num, CamType cam_type)
    : name_(std::move(name)), serial_num_(std::move(serial_num)), cam_(serial_num_), cam_type_(cam_type) {
  cam_.set_capture_format("BGRx", gsttcam::FrameSize{width_, height_}, gsttcam::FrameRate{frame_rate_, 1});

  cam_.set_trigger(false);

  // Start the camera
  cam_.start();
  cam_.set_trigger(true);
  cam_.set_low_latency_mode(true);
  // if (cam_type_ == CamType::kTCAMFollower) {
  // cam_.set_trigger(true);
  // cam_.set_trigger_polarity_pos(true);
  // cam_.
  //} else if (cam_type_ == CamType::kTCAMMaster) {
  //  cam_.set_trigger(false);
  // cam_.set_strobe_enable(true);
  // cam_.set_strobe_delay_us(0);
  // cam_.set_strobe_length_is_exposure(true);
  // cam_.set_strobe_polarity_pos(true);
  //}
  cam_.set_auto_exposure();
  cam_.set_exposure_time(exposure_time_);
  cam_.set_white_balance_auto(false);

  std::shared_ptr<gsttcam::Property> gain_value = nullptr;

  try {
    gain_value = cam_.get_property("Gain");
  } catch (std::exception& ex) {
    printf("Error %s : %s\n", ex.what(), "Gain Value");
  }

  if (gain_value != nullptr) {
    std::cout << "I am setting gain for cam " << std::endl;
    gain_value->set(cam_, 120);
  }

  std::shared_ptr<gsttcam::Property> gain_auto = nullptr;

  try {
    gain_auto = cam_.get_property("Gain Auto");
  } catch (std::exception& ex) {
    printf("Error %s : %s\n", ex.what(), "Gain Auto");
  }

  if (gain_auto != nullptr) {
    int auto_val;
    gain_auto->get(cam_, auto_val);
    if (auto_val == 1) {
      printf("Current gain automatic is On.\n");
    } else {
      printf("Current gain  automatic is Off.\n");
    }
  }

  if (gain_value != nullptr) {
    int gain;
    gain_value->get(cam_, gain);
    printf("Current gain value is %d.\n", gain);
  }
}

void TCAMImageReader::SetExposureTime(int exposure_time) {
  exposure_time_ = exposure_time;
  cam_.set_exposure_time(exposure_time_);

}




auto TCAMImageReader::GetSize() const -> cv::Size { return cv::Size(width_, height_); }

void TCAMImageReader::Trigger() {
  cam_.saveNextImage();
  cam_.trigger();
}

void TCAMImageReader::ReadImg(cv::Mat& img_storage) {
  cam_.snapImage(80);

  img_storage.create(cam_.getHeight(), cam_.getWidth(), CV_8UC(cam_.getBytesPerPixel()));
  memcpy(img_storage.data, cam_.getImageData(), cam_.getImageDataSize());
  counter_++;
}
