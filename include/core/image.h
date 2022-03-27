#pragma once

#include <vector>
namespace naivebayes {

class Image {
 public:

  Image(const std::vector<std::vector<char>>& pixels, const int class_number);
  
  Image(const std::vector<std::string> &pixels, const int class_number);

  std::vector<std::vector<char>> GetPixels() const;
  
  int GetPixelColor(int row, int column) const;

  int GetClassNumber() const;
  
  int GetNumberRows() const;
  
  int GetNumberColumns() const;
  
 private:
  std::vector<std::vector<char>> pixels_;
  int class_number_;

};

} // namespace naivebayes