#include "core/image.h"

namespace naivebayes {

Image::Image(int row_count, int column_count) {
  row_count_ = row_count;
  column_count_ = column_count;
  class_number_ = 0;
  
  pixels_ = std::vector<std::vector<char>>(row_count,
                                           std::vector<char>(column_count, ' '));
}

Image::Image(const std::vector<std::vector<char>>& pixels, int class_number) {
  pixels_ = pixels;
  class_number_ = class_number;
  row_count_ = pixels.size();
  column_count_ = pixels[0].size();
}

Image::Image(const std::vector<std::string> &pixels, int class_number) {
  for (size_t i = 0; i < pixels.size(); i++) {
    pixels_.emplace_back();
    for (size_t j = 0; j < pixels[i].size(); j++) {
      pixels_[i].push_back(pixels[i][j]);
    }
  }

  class_number_ = class_number;
  row_count_ = pixels_.size();
  column_count_ = pixels[0].size();
}

int Image::GetPixelColor(int row, int column) const {
  return (pixels_[row][column] == ' ') ? 0 : 1;
}

void Image::SetPixelColor(int row, int column, char color) {
  pixels_[row][column] = color;
}

bool Image::IsPixelShaded(int row, int column) const {
  return pixels_[row][column] != ' ';
}

const std::vector<std::vector<char>>& Image::GetPixels() const {
  return pixels_;
}

int Image::GetClassNumber() const {
  return class_number_;
}

int Image::GetRowCount() const {
  return row_count_;
}

int Image::GetColumnCount() const {
  return column_count_;
}


} // namespace naivebayes