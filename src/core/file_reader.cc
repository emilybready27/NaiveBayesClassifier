#include <core/file_reader.h>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

namespace naivebayes {

FileReader::FileReader(const visualizer::Sketchpad& sketchpad) {
  
}

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

  // save all single-value state
  std::getline(input, line);
  faux_model_.k_laplace = std::stof(line);
  std::getline(input, line);
  faux_model_.k_max_class_count = std::stoi(line);
  std::getline(input, line);
  faux_model_.total_class_count = std::stoi(line);
  std::getline(input, line);
  faux_model_.total_image_count = std::stoi(line);
  std::getline(input, line);
  faux_model_.row_count = std::stoi(line);
  std::getline(input, line);
  faux_model_.column_count = std::stoi(line);
  
  // read in list of class number counts
  std::getline(input, line);
  faux_model_.class_number_counts = ReadSaveFileVectorInt(line);
  
  // read in list of prior probabilities
  std::getline(input, line);
  faux_model_.prior_probs = ReadSaveFileVectorFloat(line);
  
  // store vector of NumberClasses
  bool new_class = true;
  NumberClass number_class = NumberClass(0,
                                         faux_model_.row_count,
                                         faux_model_.column_count);
  while (input.peek() != EOF) {
    // construct new NumberClass
    if (new_class) {
      std::getline(input, line);
      number_class = NumberClass(stoi(line),
                                 faux_model_.row_count,
                                 faux_model_.column_count);
      new_class = false;
      
    // store NumberClass data   
    } else {
      std::getline(input, line);
      number_class.SetClassNumberCount(stoi(line));
      
      // construct feature probabilities shaded matrix
      std::vector<std::vector<float>> matrix = ReadSaveFileMatrix(input);
      number_class.SetFeatureProbsShaded(matrix);
      faux_model_.number_classes.push_back(number_class);
      new_class = true;
    }
  }  
}

std::vector<int>
FileReader::ReadSaveFileVectorInt(const std::string& line) {
  std::stringstream ss(line);
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;
  std::vector<std::string> counts(begin, end);
  
  // transform each character into an integer
  std::vector<int> destination(counts.size());
  std::transform(counts.begin(),
                 counts.end(),
                 destination.begin(),
                 [](const std::string& val) {
                   return std::stoi(val); });
  return destination;
}

std::vector<float>
FileReader::ReadSaveFileVectorFloat(const std::string& line) {
  std::stringstream sss(line);
  std::istream_iterator<std::string> begins(sss);
  std::istream_iterator<std::string> ends;
  std::vector<std::string> probs(begins, ends);
  
  // transform each character into a float
  std::vector<float> destination(probs.size());
  std::transform(probs.begin(),
                 probs.end(),
                 destination.begin(),
                 [](const std::string& val) {
                   return std::stof(val); });
  return destination;
}

std::vector<std::vector<float>>
FileReader::ReadSaveFileMatrix(std::istream& input) {
  std::vector<std::vector<float>> matrix;
  
  for (int i = 0; i < faux_model_.row_count; i++) {
    std::string line;
    std::getline(input, line);
    std::vector<float> row = ReadSaveFileVectorFloat(line);
    matrix.push_back(row);
  }
  
  return matrix;
}

void FileReader::ReadDataFile(std::istream& input) {
  // set num_rows of the image
  int num_rows = ReadDataFileRows(input);
  int row_iterator = 0;
  int class_number = 0; // update for each new Image
  std::vector<std::vector<char>> pixels;

  std::string line;
  while (std::getline(input, line)) {
    // reached class number line, new Image
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

int FileReader::ReadDataFileRows(std::istream& input) {
  int num_rows = 0;
  int row_iterator = 0;
  std::string line;
  while (std::getline(input, line)) {
    if (line.size() == 1 && row_iterator != 0) {
      num_rows = row_iterator - 1;
      break;
    }
    row_iterator++;
  }
  
  // handle one-image files
  if (num_rows == 0) {
    num_rows = row_iterator - 1;
  }
  
  input.clear();
  input.seekg(0); // set iterator to beginning of file again
  return num_rows;
}

bool FileReader::IsSaveFile(std::istream& input) {
  std::string line;
  std::getline(input, line);
  input.seekg(0);
  return line == "save"; // used to indicate save file
}

bool FileReader::IsSaveFile() const {
  return read_save_file_;
}

std::vector<Image> FileReader::GetData() const {
  return images_;
}

FileReader::FauxModel FileReader::GetFauxModel() const {
  return faux_model_;
}

}  // namespace naivebayes