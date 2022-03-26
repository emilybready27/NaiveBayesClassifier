#include <catch2/catch.hpp>

#include <core/image.h>

using naivebayes::Image;

TEST_CASE("Test Image GetPixelColor") {
  std::vector<std::string> pixels = {
      "   +##+   ",
      " +#+  +#+ ",
      " +#+  +#+ ",
      " +#+  +#+ ",
      "   +##+   ",
  };
  Image image = Image(pixels, 0);
  
  SECTION("' ' pixels are unshaded") {
    REQUIRE(image.GetPixelColor(0,0) == "unshaded");
  }
  
  SECTION("'+' pixels are shaded") {
    REQUIRE(image.GetPixelColor(0,3) == "shaded");
  }
  
  SECTION("'#' pixels are shaded") {
    REQUIRE(image.GetPixelColor(0,4) == "shaded");
  }
}