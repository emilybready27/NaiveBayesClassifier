#include "core/image.h"

namespace naivebayes {

Image::Image(const std::vector<std::vector<char>>& pixels,
             const int class_number) {
  pixels_ = pixels; // makes a deep copy
  class_number_ = class_number;
}

Image::Image(const std::vector<std::string> &pixels, const int class_number) {
  for (size_t i = 0; i < pixels.size(); i++) {
    pixels_.emplace_back();
    for (size_t j = 0; j < pixels[i].size(); j++) {
      pixels_[i].push_back(pixels[i][j]);
    }
  }

  class_number_ = class_number;
}

std::vector<std::vector<char>> Image::GetPixels() const {
  return pixels_;
}

int Image::GetPixelColor(int row, int column) const {
  return (pixels_[row][column] == ' ') ? 0 : 1;
}

int Image::GetClassNumber() const {
  return class_number_;
}

int Image::GetNumberRows() const {
  return pixels_.size();
}

int Image::GetNumberColumns() const {
  return pixels_[0].size();
}


} // namespace naivebayes