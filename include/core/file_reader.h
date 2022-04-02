#include <string>
#include <fstream>
#include <vector>
#include "image.h"
#include "number_class.h"
#include <visualizer/sketchpad.h>

namespace naivebayes {

/**
 * Reads in training data and configurations of previous Models.
 */
class FileReader {
 public:
  /**
   * Default constructor.
   */
  FileReader() = default;

  /**
   * Constructs an instance to read from the given input, handling
   * both reading from data files for training and save files.
   * @param input std::istream
   */
  FileReader(std::istream& input);
  
  FileReader(const visualizer::Sketchpad& sketchpad);
  
  /**
   * Checks if the given file to read from is a save file or data file.
   * @return bool
   */
  bool IsSaveFile() const;
  
  /**
   * Struct used to initialize a new Model from the configurations
   * stored in a save file, used to avoid circular dependency between
   * Model and FileWriter.
   */
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
  
  /**
   * Retrieves the FauxModel used to rebuild a saved Model.
   * @return 
   */
  FauxModel GetFauxModel() const;
  
  /**
   * Retrieves the Image data used in training a Model.
   * @return std::vector<Image>
   */
  std::vector<Image> GetData() const;
  
 private:
  /**
   * Indicates if FileReader is currently reading a data file or save file.
   */
  bool read_save_file_;
  
  /**
   * Vector of the Images constructed from reading the data file.
   */
  std::vector<Image> images_;
  
  /**
   * Struct used to initialize a new Model from a save file.
   */
  FauxModel faux_model_;
  
  /**
   * Checks the given file for an indication of a save file or data file.
   * @param input std::istream
   * @return bool
   */
  bool IsSaveFile(std::istream& input);
  
  /**
   * Reads the saved input into a FauxModel. 
   * @param input std::istream
   */
  void ReadSaveFile(std::istream& input);
  
  /**
   * Reads in the string and transforms it into a vector of integers.
   * @param line std::string
   * @return std::vector<int>
   */
  std::vector<int> ReadSaveFileVectorInt(const std::string& line);
  
  /**
   * Reads in the string and transforms it into a vector of floats.
   * @param line std::string
   * @return std::vector<float>
   */
  std::vector<float> ReadSaveFileVectorFloat(const std::string& line);
  
  /**
   * Reads in the matrix and transforms it into a vector of vectors of floats.
   * @param input std::istream
   * @return std::vector<std::vector<float>>
   */
  std::vector<std::vector<float>> ReadSaveFileMatrix(std::istream& input);
  
  /**
   * Reads the training data into a vector of Images.
   * @param input 
   */
  void ReadDataFile(std::istream& input);
  
  /**
   * Computes the number of rows of each Image preemptively.
   * @param input std::istream
   * @return int
   */
  int ReadDataFileRows(std::istream& input);
  
};

}  // namespace naivebayes
