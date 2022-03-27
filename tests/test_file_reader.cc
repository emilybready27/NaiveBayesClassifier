#include <catch2/catch.hpp>

#include <core/file_reader.h>

using naivebayes::FileReader;
using naivebayes::Image;

TEST_CASE("Test reading from data file") {
  std::string path_to_data = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\minitrainingimagesandlabels.txt)";
  std::ifstream data_file(path_to_data);
  FileReader file_handler = FileReader(data_file);
  std::vector<Image> images = file_handler.GetImages();

  SECTION("Correct vector size") {
    REQUIRE(images.size() == 4);
  }
  
  SECTION("Image 1 correct") {
    std::vector<std::string> pixels = {
        "          ",
        "          ",
        "          ",
        "   +#+    ",
        "   +#+    ",
        "   +#+    ",
        "   +#+    ",
        "   +#+    ",
        "          ",
        "          "
    };
    Image image_1 = Image(pixels, 1);
    REQUIRE(images[0].GetPixels() == image_1.GetPixels());
  }
  
  SECTION("Image 2 correct") {
    std::vector<std::string> pixels = {
        "          ",
        "          ",
        "          ",
        "  +###+   ",
        " +#+ +#+  ",
        "     +#+  ",
        "   +#+    ",
        " +#####+  ",
        "          ",
        "          "
    };
    Image image_2 = Image(pixels, 2);
    REQUIRE(images[1].GetPixels() == image_2.GetPixels());
  }
  
  SECTION("Image 3 correct") {
    std::vector<std::string> pixels = {
        "          ",
        "          ",
        "          ",
        "  +####+  ",
        " +#+  +#+ ",
        "     +##+ ",
        " +#+  +#+ ",
        "  +####+  ",
        "          ",
        "          "
    };
    Image image_3 = Image(pixels, 3);
    REQUIRE(images[2].GetPixels() == image_3.GetPixels());
  }
  
  SECTION("Image 4 correct") {
    std::vector<std::string> pixels = {
        "          ",
        "          ",
        "          ",
        "   +##+   ",
        " +#+  +#+ ",
        " +#+  +#+ ",
        " +#+  +#+ ",
        "   +##+   ",
        "          ",
        "          "
    };
    Image image_4 = Image(pixels, 0);
    REQUIRE(images[3].GetPixels() == image_4.GetPixels());
  }
}
