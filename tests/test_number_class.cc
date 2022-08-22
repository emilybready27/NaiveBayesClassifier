#include <catch2/catch.hpp>

#include <core/number_class.h>
#include <core/image.h>

using naivebayes::NumberClass;
using naivebayes::Image;

TEST_CASE("Test shaded feature probability computation") {
  std::vector<std::string> pixels = {
      "     ",
      " ### ",
      " # # ",
      " ### ",
      "     ",
  };
  Image image = Image(pixels, 0);
  
  NumberClass number_class = NumberClass(0, 5, 5);
  number_class.AddImage(image);
  number_class.ComputeFeatureProbsShaded(1.0);
  
  SECTION("First row") {
    REQUIRE(number_class.GetFeatureProbsShaded(0,0) == Approx(0.33333));
  }
  SECTION("Second row") {
    REQUIRE(number_class.GetFeatureProbsShaded(1,1) == Approx(0.66667));
  }
  SECTION("Third row") {
    REQUIRE(number_class.GetFeatureProbsShaded(2,2) == Approx(0.33333));
  }
  SECTION("Fourth row") {
    REQUIRE(number_class.GetFeatureProbsShaded(3,3) == Approx(0.66667));
  }
  SECTION("Fifth row") {
    REQUIRE(number_class.GetFeatureProbsShaded(4,4) == Approx(0.33333));
  }
}