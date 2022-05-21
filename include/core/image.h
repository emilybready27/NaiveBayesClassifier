#pragma once

#include <vector>

namespace naivebayes {

/**
 * Image used to decipher a digit.
 */
class Image {
 public:
  /**
   * Constructs an Image of all unshaded pixels.
   */
  Image(int row_count, int column_count);
  
  /**
   * Constructs an Image from a matrix of pixels and its corresponding
   * class number.
   * @param pixels std::vector<std::vector<char>>
   * @param class_number int (0-9)
   */
  Image(const std::vector<std::vector<char>>& pixels, int class_number);
  
  /**
   * Constructs an Image from a vector of string rows of pixels and its
   * corresponding number class.
   * @param pixels std::vector<std::string>
   * @param class_number int (0-9)
   */
  Image(const std::vector<std::string> &pixels, int class_number);
    
  /**
   * Returns the pixel color at the given coordinates by mapping 
   * ' ' symbol to color 0 and '#' or '+' symbol to color 1.
   * @param row int
   * @param column int
   * @return int (0 or 1)
   */
  int GetPixelColor(int row, int column) const;
  
  /**
   * Sets the color at the given coordinates to the given color by mapping
   * ' ' symbol to color 0 and '#' or '+' symbol to color 1.
   * @param row int
   * @param column int
   * @param color char (' ', '#', or '+')
   */
  void SetPixelColor(int row, int column, char color);
  
  /**
   * Determines if the pixel at the given location is shaded or not.
   * @param row int
   * @param column int
   * @return bool
   */
  bool IsPixelShaded(int row, int column) const;

  /**
   * Getters for Image state.
   */
  const std::vector<std::vector<char>>& GetPixels() const;
  int GetClassNumber() const;
  int GetRowCount() const;
  int GetColumnCount() const;
  
 private:
  /**
   * Matrix of ' ', '#', and '+' symbols.
   */
  std::vector<std::vector<char>> pixels_;
  
  /**
   * Digit (0-9) the Image represents.
   */
  int class_number_;
  
  /**
   * Number of rows in the Image.
   */
  int row_count_;
  
  /**
   * Number of columns in the Image.
   */
  int column_count_;
};

} // namespace naivebayes