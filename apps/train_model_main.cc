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
  

  for (int i = 0; i < model.GetTotalClassCount(); i++) {
    std::cout << model.GetPriorProbs()[i] << std::endl;
  }
  std::cout << std::endl;

  for (int i = 0; i < model.GetTotalClassCount(); i++) {
    for (int j = 0; j < model.GetRowCount(); j++) {
      for (int k = 0; k < model.GetColumnCount(); k++) {
        std::cout << model.GetFeatureProbsShaded(i)[j][k] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  
  return 0;
}
