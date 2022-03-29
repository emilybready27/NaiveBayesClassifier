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
    float k_laplace;
    int k_max_class_count;
    int total_class_count;
    int total_image_count;
    int row_count;
    int column_count;
    std::vector<int> class_number_counts;
    std::vector<NumberClass> number_classes;
    std::vector<float> prior_probs;
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
