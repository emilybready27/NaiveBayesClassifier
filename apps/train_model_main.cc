#include <iostream>
#include <ostream>

#include <core/model.h>

using naivebayes::Model;

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "Usage: ./train_model path-to-data path-to-save";
    return 1;
  }
  
//  std::string path_to_data = argv[1];
//  std::string path_to_save = argv[2];
  std::string path_to_data = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\training\trainingimagesandlabels.txt)";
  std::string path_to_save = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\saved\save_file.txt)";
  
  Model model = Model();
  
  // load in training data
  std::ifstream data_file(path_to_data);
  data_file >> model;

  model.Train();

  // save model in file
//  std::ofstream save_file(path_to_save);
//  save_file << model;
//
//  // load in saved model
//  std::ifstream save_file_read(path_to_save);
//  save_file_read >> model;
//  
//  model.PrintModel();

  // load in validator data
  std::string path_to_validate = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\validation\testimagesandlabels.txt)";
  std::ifstream validation_data(path_to_validate);
  validation_data >> model;

  std::cout << model.Validate() << std::endl;
  
  return 0;
}
