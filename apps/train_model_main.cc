#include <iostream>
#include <istream>
#include <ostream>

#include <core/model.h>

using naivebayes::Model;

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "Usage: ./train_model path-to-data path-to-save";
    return 1;
  }
  
  std::string path_to_data = argv[1];
  std::string path_to_save = argv[2];
  
  Model model = Model();
  
  // load in training data
  std::ifstream data_file(path_to_data);
  data_file >> model;

  model.Train();

  // save model in file
  std::ofstream save_file(path_to_save);
  save_file << model;
  
  // load in saved model
  std::ifstream save_file_read(path_to_save);
  save_file_read >> model;
  

  for (size_t i = 0; i < 10; i++) {
    std::cout << model.GetPriorProbs()[i] << std::endl;
  }
  std::cout << std::endl;

  for (size_t i = 0; i < 10; i++) {
    if (model.GetClassNumberCounts()[i] == 0) {
      continue;
    }

    for (size_t j = 0; j < 10; j++) {
      for (size_t k = 0; k < 10; k++) {
//        if (model.GetFeatureProbsShaded(i)[j][k] <= 0.3) {
//          std::cout << " " << " ";
//        } else {
//          std::cout << " " << i;
//        }
        std::cout << model.GetFeatureProbsShaded(i)[j][k] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  
  return 0;
}
