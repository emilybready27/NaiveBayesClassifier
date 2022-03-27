#include <core/file_reader.h>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

namespace naivebayes {

FileReader::FileReader(std::istream& input) {
  read_save_file_ = IsSaveFile(input);
  if (read_save_file_) {
    ReadSaveFile(input);
  } else {
    ReadDataFile(input);
  }
}

void FileReader::ReadSaveFile(std::istream& input) {
  std::string line;
  std::getline(input, line); // skip over "save" line

  std::getline(input, line);
  faux_model_.total_image_count_ = std::stoi(line);

  std::getline(input, line);
  faux_model_.row_count_ = std::stoi(line);

  std::getline(input, line);
  faux_model_.column_count_ = std::stoi(line);

  int count = 0;
  NumberClass number_class = NumberClass(0);
  while (input.peek() != EOF) {
    // store class number
    if (count == 0) {
      std::getline(input, line);
      number_class = NumberClass(stoi(line));
      count = 1;
      
    // store class number count   
    } else {
      std::getline(input, line);
      number_class.SetClassNumberCount(stoi(line));
      number_class.SetRowCount(faux_model_.row_count_);
      number_class.SetColumnCount(faux_model_.column_count_);
      number_class.ResetFeatureProbsShaded(0);
      count = 0;
      
      if (number_class.GetClassNumberCount() <= 0) {
        faux_model_.number_classes_.push_back(number_class);
      } else {

        // store class feature probabilities for shaded
        std::vector<std::vector<float>> matrix;

        for (int i = 0; i < faux_model_.row_count_; i++) {
          std::getline(input, line);

          std::stringstream ss(line);
          std::istream_iterator<std::string> begin(ss);
          std::istream_iterator<std::string> end;
          std::vector<std::string> tokens(begin, end);

          std::vector<float> row(tokens.size());
          std::transform(tokens.begin(),
                         tokens.end(),
                         row.begin(),
                         [](const std::string& val) {
                           return std::stof(val); });
          matrix.push_back(row);
        }

        number_class.SetFeatureProbsShaded(matrix);
        faux_model_.number_classes_.push_back(number_class);
      }
    }
  }
  
  
  
}

void FileReader::ReadDataFile(std::istream& input) {
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

bool FileReader::IsSaveFile(std::istream& input) {
  std::string line;
  std::getline(input, line);
  input.seekg(0);
  return line == "save";
}

bool FileReader::IsSaveFile() const {
  return read_save_file_;
}

std::vector<Image> FileReader::GetData() const {
  // TODO: throw invalid_argument_exception
  return images_;
}

FileReader::FauxModel FileReader::GetFauxModel() const {
  return faux_model_;
}



}  // namespace naivebayes