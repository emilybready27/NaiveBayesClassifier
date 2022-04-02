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
  validator.Compare(1);
  
  SECTION("Has correct accuracy") {
    REQUIRE(validator.Validate() == 1);
  }
}