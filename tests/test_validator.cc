#include <catch2/catch.hpp>

#include <core/model.h>
#include <core/validator.h>

using naivebayes::Validator;
using naivebayes::Model;
using naivebayes::Image;

TEST_CASE("Test validation method") {
  Image image1 = Image({"## ",
                        " # ",
                        " # "}, 1);
  std::vector<Image> images = {image1};
  Validator validator = Validator(images, 10);
  validator.Compare(1, 1);
  validator.Validate();
  
  SECTION("Has correct accuracy") {
    REQUIRE(validator.GetAccuracy() == 1);
  }
  
  SECTION("Has correct accuracy vector") {
    std::vector<float> accuracies(10, 0.0);
    accuracies[1] = 1.0;
    REQUIRE(validator.GetAccuracies() == accuracies);
  }
}