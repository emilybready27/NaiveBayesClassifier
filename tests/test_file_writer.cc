#include <catch2/catch.hpp>
#include <iostream>

#include <core/file_writer.h>
#include <core/model.h>

using naivebayes::FileWriter;
using naivebayes::Model;

const std::string path_to_data = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\minitrainingimagesandlabels.txt)";
const std::string path_to_save = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\mini_save_file_2.txt)";

TEST_CASE("Test output to file") {
  Model model = Model();
  std::ifstream data_file(path_to_data);
  data_file >> model;
  
  model.Train();

  std::ofstream save_file(path_to_save);
  FileWriter file_writer = FileWriter(save_file,
                                      model.GetNumberClasses(),
                                      model.GetTotalImageCount(),
                                      model.GetRowCount(),
                                      model.GetColumnCount());

  std::string line;
  std::ifstream read_file(path_to_save);
  
  std::getline(read_file, line);
  SECTION("Prefixed with save indicator") {
    REQUIRE(line == "save");
  }
  
  std::getline(read_file, line);
  SECTION("Stores correct total image count") {
    REQUIRE(line == "4");
  }
  
  std::getline(read_file, line);
  SECTION("Stores correct row count") {
    REQUIRE(line == "10");
  }
  
  std::getline(read_file, line);
  SECTION("Stores correct column count") {
    REQUIRE(line == "10");
  }
  
  std::getline(read_file, line);
  SECTION("Stores correct number class name") {
    REQUIRE(line == "0");
  }
  
  std::getline(read_file, line);
  SECTION("Stores correct number class count") {
    REQUIRE(line == "1");
  }
  
  std::getline(read_file, line);
  SECTION("Stores correct matrix first row") {
    std::string row = "0.333333 0.333333 0.333333 0.333333 0.333333 "
        "0.333333 0.333333 0.333333 0.333333 0.333333 ";
    REQUIRE(line == row);
  }
  
  SECTION("Stores correct number of matrix rows") {
    int count = 1;
    while (std::getline(read_file, line) && line.size() != 1) {
      count++;
    }
    
    REQUIRE(count == model.GetRowCount());
  }
}