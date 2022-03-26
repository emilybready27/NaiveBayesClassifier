#pragma once

#include "file_reader.h"

namespace naivebayes {

class Model {
 public: 
  Model();
  
  friend std::istream& operator>> (std::istream& in, Model& model);
  
 private:
  FileReader file_reader_;
  
};



} // namespace naivebayes