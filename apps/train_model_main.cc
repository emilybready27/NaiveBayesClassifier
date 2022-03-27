#include <iostream>
#include <istream>
#include <ostream>

#include <core/model.h>

using naivebayes::Model;

// TODO: You may want to change main's signature to take in argc and argv
int main() {
  // TODO: Replace this with code that reads the training data, trains a model,
  // and saves the trained model to a file.

  Model model = Model();
  std::string path_to_data = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\minitrainingimagesandlabels.txt)";
  std::ifstream data_file(path_to_data);
  data_file >> model;
  
  std::string path_to_save = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\save_file.txt)";
  std::ofstream save_file(path_to_save);
  save_file << model;
  
  // load in save_file 
  
//  for (size_t i = 0; i < 5; i++) {
//    for (size_t j = 0; j < 10; j++) {
//      std::cout << " " << model.GetPriorProbs()[i];
//    }
//    std::cout << std::endl;
//  }
  
//  for (size_t i = 0; i < 10; i++) {
//    
//    if (model.GetClassNumberCounts()[i] == 0) {
//      //std::cout << std::endl;
//      continue;
//    }
//    
//    for (size_t j = 0; j < 10; j++) {
//      for (size_t k = 0; k < 10; k++) {
//        if (model.GetFeatureProbsShaded(i)[j][k] <= 0.34) {
//          std::cout << " " << " ";
//        } else {
//          std::cout << " " << 1;
//        }
//        //std::cout << " " << model.GetFeatureProbs1()[i][j];
//      }
//      std::cout << std::endl;
//    }
//    std::cout << std::endl;
//  }
  
  return 0;
}
