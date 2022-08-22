#include <catch2/catch.hpp>

#include <core/model.h>
#include <core/validator.h>

using naivebayes::Validator;
using naivebayes::Model;
using naivebayes::Image;

const std::string path_to_data_1 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\training\tinytrainingimagesandlabels.txt)";
const std::string path_to_data_2 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\training\minitrainingimagesandlabels.txt)";
const std::string path_to_data_3 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\training\trainingimagesandlabels.txt)";

TEST_CASE("Test validation method 3x3") {
  SECTION("With one correct image") {
    Image image = Image({"## ",
                          " # ",
                          " # "}, 1);
    std::vector<Image> images = {image};
    Validator validator = Validator(images, 10);
    validator.Compare(1, 1);
    
    REQUIRE(validator.Validate() == 1);
  }
  
  SECTION("With one correct image, one incorrect image") {
    Image image1 = Image({"## ",
                          " # ",
                          " # "}, 1);
    Image image2 = Image({"###",
                          "  #",
                          "  #"}, 7);
    std::vector<Image> images = {image1, image2};
    Validator validator = Validator(images, 10);
    validator.Compare(1, 1);
    validator.Compare(7, 1);
    
    REQUIRE(validator.Validate() == 0.5);
  }
}

TEST_CASE("Test validation method 10x10") {
  SECTION("With one correct image") {
    Image image = Image({"          ",
                         "          ",
                         "          ",
                         "  +###+   ",
                         " +   +##+ ",
                         "   +##+   ",
                         " +   +##+ ",
                         "  +###+   ",
                         "          ",
                         "          "}, 3);
    std::vector<Image> images = {image};
    Validator validator = Validator(images, 10);
    validator.Compare(3, 3);
    
    REQUIRE(validator.Validate() == 1);
  }
  
  
  SECTION("With one correct image, one incorrect image") {
    Image image1 = Image({"          ",
                          "          ",
                          "          ",
                          "  +###+   ",
                          " +   +##+ ",
                          "   +##+   ",
                          " +   +##+ ",
                          "  +###+   ",
                          "          ",
                          "          "}, 3);
    Image image2 = Image({"          ",
                          "          ",
                          "          ",
                          "  +###+   ",
                          " +#+  +#+ ",
                          "  +####+  ",
                          " +#+  +#+ ",
                          "  +####+  ",
                          "          ",
                          "          "}, 8);
    std::vector<Image> images = {image1, image2};
    Validator validator = Validator(images, 10);
    validator.Compare(3, 3);
    validator.Compare(8, 3);
    
    REQUIRE(validator.Validate() == 0.5);
  }
}