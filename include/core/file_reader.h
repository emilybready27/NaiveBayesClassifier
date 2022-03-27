#include <string>
#include <fstream>
#include <vector>
#include "image.h"
#include "number_class.h"

namespace naivebayes {

class FileReader {
 public:
  FileReader() = default;

  FileReader(std::istream& input);
  
  bool IsSaveFile() const;
  
  std::vector<Image> GetData() const;
  
  struct FauxModel {
    int total_image_count;
    int row_count;
    int column_count;
    std::vector<NumberClass> number_classes;
  };
  
  FauxModel GetFauxModel() const;
  
 private:
  bool read_save_file_;
  
  std::vector<Image> images_;
  
  FauxModel faux_model_;
  
  bool IsSaveFile(std::istream& input);
  
  void ReadSaveFile(std::istream&input);
  
  std::vector<std::vector<float>> ReadSaveFileMatrix(std::istream& input);
  
  void ReadDataFile(std::istream& input);
  
  int ReadDataFileRows(std::istream& input);
  
};

}  // namespace naivebayes
