//
// Created by anacreon on 7/9/20.
//

#ifndef CTR_WS_IMAGE_READER_H
#define CTR_WS_IMAGE_READER_H

#include <opencv2/core/core.hpp>

class ImageReader {
 public:
  ImageReader() = default;

  virtual void SetExposureTime(int exposure_time) = 0;

  virtual auto GetSize() const -> cv::Size = 0;
//   virtual auto GetEncoding() const -> std::string = 0;
  virtual void Trigger() {}
  virtual void ReadImg(cv::Mat& img_storage) = 0;
  virtual void ResetCounter() = 0;

 protected:
 private:
};

#endif  // CTR_WS_IMAGE_READER_H
