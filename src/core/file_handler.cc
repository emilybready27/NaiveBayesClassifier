#include <core/file_handler.h>
#include <fstream>
#include <string>

namespace naivebayes {

File_Handler::File_Handler(const std::string& path_to_data) {
  std::ifstream path_to_data_test(path_to_data);
//  std::ifstream path_to_save_test(path_to_save);
  if (!path_to_data_test) {
    throw std::invalid_argument("The data file doesn't exist");
  }
//  if (!path_to_save_test) {
//    throw std::invalid_argument("The save file doesn't exist");
//  }
  path_to_data_ = path_to_data;
//  path_to_save_ = path_to_save;
}

std::vector<Image> File_Handler::ReadDataFile() {
  // open the data file to read from
  // TODO: fix to work with insertion operator
  std::fstream data_file(path_to_data_);

  // set num_rows of the image
  int num_rows = 0;
  int row_iterator = 0;
  std::string line;
  while (std::getline(data_file, line)) {
    if (line.size() == 1 && row_iterator != 0) {
      num_rows = row_iterator - 1;
      row_iterator = 0;
      break;
    }
    row_iterator++;
  }

  int class_number = 0; // update for each new image
  std::vector<std::vector<char>> pixels;
  std::vector<Image> images;

  // start from beginning of file again
  data_file.seekg(0);
  while (std::getline(data_file, line)) {
    // reached class number line
    if (line.size() == 1 && row_iterator == 0) {
      class_number = stoi(line);
      continue;
    }

    pixels.emplace_back();
    for (const char pixel : line) {
      pixels[row_iterator].push_back(pixel);
    }
    row_iterator++;
    
    // reached end of image
    if (row_iterator == num_rows) {
      images.emplace_back(pixels, class_number);
      row_iterator = 0;
      pixels.clear();
      continue;
    }
  }

  return images;
}

}  // namespace naivebayes