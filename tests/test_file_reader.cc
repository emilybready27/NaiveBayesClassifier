#include <catch2/catch.hpp>

#include <core/file_reader.h>

using naivebayes::FileReader;
using naivebayes::Image;
using naivebayes::NumberClass;

const std::string path_to_data_2 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\minitrainingimagesandlabels.txt)";
const std::string path_to_save_2 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\mini_save_file.txt)";


TEST_CASE("Test reading from data file") {
  std::ifstream data_file(path_to_data_2);
  FileReader file_reader = FileReader(data_file);
  std::vector<Image> images = file_reader.GetData();

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

TEST_CASE("Test reading from save file") {
  std::ifstream data_file(path_to_save_2);
  FileReader file_reader = FileReader(data_file);
  FileReader::FauxModel faux_model = file_reader.GetFauxModel();
  
  SECTION("Faux model has correct total image count") {
    REQUIRE(faux_model.total_image_count == 4);
  }
  
  SECTION("Faux model has correct row count") {
    REQUIRE(faux_model.row_count == 10);
  }
  
  SECTION("Faux model has correct column count") {
    REQUIRE(faux_model.column_count == 10);
  }
  
  SECTION("Faux model has correct number of NumberClasses") {
    REQUIRE(faux_model.number_classes.size() == 4);
  }

  SECTION("Faux model has correct number of nonempty NumberClasses") {
    int count = 0;
    for (const NumberClass& number_class : faux_model.number_classes) {
      if (number_class.GetClassNumberCount() > 0) {
        count++;
      }
    }
    
    REQUIRE(count == 4);
  }
  
}
