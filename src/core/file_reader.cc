#include <core/file_reader.h>
#include <string>

namespace naivebayes {

FileReader::FileReader(std::istream& input) {
  // set num_rows of the image
  int num_rows = 0;
  int row_iterator = 0;
  std::string line;
  while (std::getline(input, line)) {
    if (line.size() == 1 && row_iterator != 0) {
      num_rows = row_iterator - 1;
      row_iterator = 0;
      break;
    }
    row_iterator++;
  }
  
  int class_number = 0; // update for each new image
  std::vector<std::vector<char>> pixels;

  // start from beginning of file again
  input.seekg(0);
  while (std::getline(input, line)) {
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
      images_.emplace_back(pixels, class_number);
      row_iterator = 0;
      pixels.clear();
      continue;
    }
  }
}
std::vector<Image> FileReader::GetImages() const {
  return images_;
}

}  // namespace naivebayes