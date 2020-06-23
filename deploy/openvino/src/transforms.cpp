//   Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include <string>
#include <vector>

#include "include/paddlex/transforms.h"

namespace PaddleX {

std::map<std::string, int> interpolations = {{"LINEAR", cv::INTER_LINEAR},
                                             {"NEAREST", cv::INTER_NEAREST},
                                             {"AREA", cv::INTER_AREA},
                                             {"CUBIC", cv::INTER_CUBIC},
                                             {"LANCZOS4", cv::INTER_LANCZOS4}};

bool Normalize::Run(cv::Mat* im){
  for (int h = 0; h < im->rows; h++) {
    for (int w = 0; w < im->cols; w++) {
      im->at<cv::Vec3f>(h, w)[0] =
          (im->at<cv::Vec3f>(h, w)[0] / 255.0 - mean_[0]) / std_[0];
      im->at<cv::Vec3f>(h, w)[1] =
          (im->at<cv::Vec3f>(h, w)[1] / 255.0 - mean_[1]) / std_[1];
      im->at<cv::Vec3f>(h, w)[2] =
          (im->at<cv::Vec3f>(h, w)[2] / 255.0 - mean_[2]) / std_[2];
    }
  }
  return true;
}

bool CenterCrop::Run(cv::Mat* im) {
  int height = static_cast<int>(im->rows);
  int width = static_cast<int>(im->cols);
  if (height < height_ || width < width_) {
    std::cerr << "[CenterCrop] Image size less than crop size" << std::endl;
    return false;
  }
  int offset_x = static_cast<int>((width - width_) / 2);
  int offset_y = static_cast<int>((height - height_) / 2);
  cv::Rect crop_roi(offset_x, offset_y, width_, height_);
  *im = (*im)(crop_roi);
  return true;
}


float ResizeByShort::GenerateScale(const cv::Mat& im) {
  int origin_w = im.cols;
  int origin_h = im.rows;
  int im_size_max = std::max(origin_w, origin_h);
  int im_size_min = std::min(origin_w, origin_h);
  float scale =
      static_cast<float>(short_size_) / static_cast<float>(im_size_min);
  if (max_size_ > 0) {
    if (round(scale * im_size_max) > max_size_) {
      scale = static_cast<float>(max_size_) / static_cast<float>(im_size_max);
    }
  }
  return scale;
}

bool ResizeByShort::Run(cv::Mat* im) {
  float scale = GenerateScale(*im);
  int width = static_cast<int>(scale * im->cols);
  int height = static_cast<int>(scale * im->rows);
  cv::resize(*im, *im, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
  return true;
}

void Transforms::Init(const YAML::Node& transforms_node, bool to_rgb) {
  transforms_.clear();
  to_rgb_ = to_rgb;
  for (const auto& item : transforms_node) {
    std::string name = item.begin()->first.as<std::string>();
    std::cout << "trans name: " << name << std::endl;
    std::shared_ptr<Transform> transform = CreateTransform(name);
    transform->Init(item.begin()->second);
    transforms_.push_back(transform);
  }
}

std::shared_ptr<Transform> Transforms::CreateTransform(
    const std::string& transform_name) {
  if (transform_name == "Normalize") {
    return std::make_shared<Normalize>();
  } else if (transform_name == "CenterCrop") {
    return std::make_shared<CenterCrop>();
  } else if (transform_name == "ResizeByShort") {
    return std::make_shared<ResizeByShort>();
  } else {
    std::cerr << "There's unexpected transform(name='" << transform_name
              << "')." << std::endl;
    exit(-1);
  }
}

bool Transforms::Run(cv::Mat* im, Blob::Ptr blob) {
  // 按照transforms中预处理算子顺序处理图像
  if (to_rgb_) {
    cv::cvtColor(*im, *im, cv::COLOR_BGR2RGB);
  }
  (*im).convertTo(*im, CV_32FC3);

  for (int i = 0; i < transforms_.size(); ++i) {
    if (!transforms_[i]->Run(im)) {
      std::cerr << "Apply transforms to image failed!" << std::endl;
      return false;
    }
  }

  // 将图像由NHWC转为NCHW格式
  // 同时转为连续的内存块存储到Blob
  SizeVector blobSize = blob->getTensorDesc().getDims();
  const size_t width = blobSize[3];
  const size_t height = blobSize[2];
  const size_t channels = blobSize[1];
  MemoryBlob::Ptr mblob = InferenceEngine::as<MemoryBlob>(blob);
  auto mblobHolder = mblob->wmap();
  float *blob_data = mblobHolder.as<float *>();
  for (size_t c = 0; c < channels; c++) {
      for (size_t  h = 0; h < height; h++) {
          for (size_t w = 0; w < width; w++) {
              blob_data[c * width * height + h * width + w] =
                      im->at<cv::Vec3f>(h, w)[c];
          }
      }
  }
  return true;
}
}  // namespace PaddleX
