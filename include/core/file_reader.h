#include <string>
#include <fstream>
#include <vector>
#include "image.h"

namespace naivebayes {

class FileReader {
 public:
  FileReader() = default;

  FileReader(std::istream& input);
  
  std::vector<Image> GetImages() const;
  
 private:  
  std::vector<Image> images_;
};

}  // namespace naivebayes
