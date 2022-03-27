#include <catch2/catch.hpp>

#include <core/model.h>
#include <core/image.h>

using naivebayes::Model;

TEST_CASE("Test image storage") {
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

TEST_CASE("Test prior probability computation") {
  Model model = Model();
  std::string path_to_data = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\minitrainingimagesandlabels.txt)";
  std::ifstream data_file(path_to_data);
  data_file >> model;
  
  SECTION("First element") {
    REQUIRE(model.GetPriorProbs()[0] == Approx(0.14286).epsilon(0.01));
  }
  SECTION("Second element") {
    REQUIRE(model.GetPriorProbs()[1] == Approx(0.14286).epsilon(0.01));
  }
  SECTION("Third element") {
    REQUIRE(model.GetPriorProbs()[2] == Approx(0.14286).epsilon(0.01));
  }
  SECTION("Fourth element") {
    REQUIRE(model.GetPriorProbs()[3] == Approx(0.14286).epsilon(0.01));
  }
  SECTION("Fifth element") {
    REQUIRE(model.GetPriorProbs()[4] == Approx(0.07143).epsilon(0.01));
  }
  SECTION("Sixth element") {
    REQUIRE(model.GetPriorProbs()[5] == Approx(0.07143).epsilon(0.01));
  }
  SECTION("Seventh element") {
    REQUIRE(model.GetPriorProbs()[6] == Approx(0.07143).epsilon(0.01));
  }
  SECTION("Eighth element") {
    REQUIRE(model.GetPriorProbs()[7] == Approx(0.07143).epsilon(0.01));
  }
  SECTION("Ninth element") {
    REQUIRE(model.GetPriorProbs()[8] == Approx(0.07143).epsilon(0.01));
  }
  SECTION("Tenth element") {
    REQUIRE(model.GetPriorProbs()[9] == Approx(0.07143).epsilon(0.01));
  }
  
  
}