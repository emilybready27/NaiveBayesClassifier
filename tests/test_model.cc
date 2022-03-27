#include <catch2/catch.hpp>

#include <core/model.h>
#include <core/image.h>

using naivebayes::Model;

TEST_CASE("Test extraction override") {
  Model model = Model();
  std::string path_to_data = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\minitrainingimagesandlabels.txt)";
  std::ifstream data_file(path_to_data);
  data_file >> model;
  
  SECTION("Images sorted correctly") {
    std::vector<int> class_numbers = {
          model.GetImages()[0][0].GetClassNumber(),
          model.GetImages()[1][0].GetClassNumber(),
          model.GetImages()[2][0].GetClassNumber(),
          model.GetImages()[3][0].GetClassNumber()
      };
    REQUIRE(class_numbers == std::vector<int>{0, 1, 2, 3});
  }
  
  SECTION("Class number counts derived correctly") {
    std::vector<int> class_number_counts = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    REQUIRE(model.GetClassNumberCounts() == class_number_counts);
  }
}