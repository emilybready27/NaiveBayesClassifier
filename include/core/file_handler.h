#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "image.h"

namespace naivebayes {

class File_Handler {
 public:
  /**
   *
   * @param path_to_data std::string path to data file
   * @param path_to_save std::string path to file for saving model
   */
  File_Handler(const std::string& path_to_data);

  /**
   *
   * @return std::vector<Image> for each Image
   */
  std::vector<Image> ReadDataFile();


 private:
  std::string path_to_data_;
//  std::string path_to_save_;
};

}  // namespace naivebayes
