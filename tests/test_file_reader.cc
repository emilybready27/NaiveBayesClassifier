#include <catch2/catch.hpp>

#include <core/file_reader.h>

using naivebayes::FileReader;
using naivebayes::Image;
using naivebayes::NumberClass;

const std::string path_to_data_2 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\training\minitrainingimagesandlabels.txt)";
const std::string path_to_save = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\saved\mini_save_file.txt)";


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
  std::ifstream data_file(path_to_save);
  FileReader file_reader = FileReader(data_file);
  FileReader::FauxModel faux_model = file_reader.GetFauxModel();
  
  SECTION("Faux model has correct Laplace constant") {
    REQUIRE(faux_model.k_laplace == 1.0);
  }
  
  SECTION("Faux model has correct max class count constant") {
    REQUIRE(faux_model.k_max_class_count == 10);
  }
  
  SECTION("Faux model has correct total class count") {
    REQUIRE(faux_model.total_class_count == 4);
  }
  
  SECTION("Faux model has correct total image count") {
    REQUIRE(faux_model.total_image_count == 4);
  }
  
  SECTION("Faux model has correct row count") {
    REQUIRE(faux_model.row_count == 10);
  }
  
  SECTION("Faux model has correct column count") {
    REQUIRE(faux_model.column_count == 10);
  }
  
  SECTION("Faux model has correct class number counts") {
    std::vector<int> class_number_counts = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    REQUIRE(faux_model.class_number_counts == class_number_counts);
  }
  
  SECTION("Faux model has correct Number Classes") {
    std::vector<int> class_numbers = {
        faux_model.number_classes[0].GetClassNumber(),
        faux_model.number_classes[1].GetClassNumber(),
        faux_model.number_classes[2].GetClassNumber(),
        faux_model.number_classes[3].GetClassNumber()
    };
    REQUIRE(class_numbers == std::vector<int>{0, 1, 2, 3});
  }
  
  SECTION("Faux model has correct prior probabilities") {
    std::vector<float> prior_probs = {0.25, 0.25, 0.25, 0.25, 0, 0, 0, 0, 0, 0};  
    REQUIRE(faux_model.prior_probs == prior_probs);
  }  
}
