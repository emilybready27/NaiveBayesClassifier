#include <catch2/catch.hpp>

#include <core/model.h>
#include <core/image.h>

using naivebayes::Model;

const std::string path_to_data = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\minitrainingimagesandlabels.txt)";
const std::string path_to_data_2 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\trainingimagesandlabels.txt)";
const std::string path_to_save = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\mini_save_file.txt)";

TEST_CASE("Test extraction operator overload with data file") {
  Model model = Model();
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

TEST_CASE("Test extraction operator overload with save file") {
  Model model = Model();
  std::ifstream save_file_read(path_to_save);
  save_file_read >> model;
  
  SECTION("Total image count derived correctly") {
    REQUIRE(model.GetTotalImageCount() == 4);
  }
  
  SECTION("Class number counts derived correctly") {
    std::vector<int> class_number_counts = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    REQUIRE(model.GetClassNumberCounts() == class_number_counts);
  }
  
  SECTION("Prior probability derived correctly for class 0") {
    REQUIRE(model.GetPriorProbs()[0] == Approx(0.142857));
  }
  
  SECTION("Prior probability derived correctly for class 5") {
    REQUIRE(model.GetPriorProbs()[5] == Approx(0.0714286));
  }
  
  SECTION("Feature probability derived correctly for shaded class 0") {
    REQUIRE(model.GetFeatureProbsShaded(0)[0][0] == Approx(0.333333));
  }
  
  SECTION("Feature probability derived correctly for unshaded for class 0") {
    REQUIRE(1 - model.GetFeatureProbsShaded(0)[0][0] == Approx(0.666667));
  }
  
  SECTION("Feature probability derived correctly for class 5") {
    REQUIRE(model.GetFeatureProbsShaded(5).empty() == true);
  }
}

TEST_CASE("Test insertion operator overload") {
  Model model1 = Model();
  std::ifstream data_file(path_to_data);
  data_file >> model1;
  model1.Train();
  
  std::ofstream save_file(path_to_save);
  save_file << model1;
  
  Model model2 = Model();
  std::ifstream save_file_read(path_to_save);
  save_file_read >> model2;
  
  SECTION("Two models have same total image count") {
    REQUIRE(model1.GetTotalImageCount() == model2.GetTotalImageCount());
  }
  
  SECTION("Two models have same class number counts") {
    REQUIRE(model1.GetClassNumberCounts() == model2.GetClassNumberCounts());
  }
  
  SECTION("Two models have same prior probabilities") {
    REQUIRE(model1.GetPriorProbs() == model2.GetPriorProbs());
  }
  
  SECTION("Two models have same feature probs shaded for class 0") {
    REQUIRE(model1.GetFeatureProbsShaded(0)[0][0]
            == Approx(model2.GetFeatureProbsShaded(0)[0][0]));
  }
  
  SECTION("Two models have same feature probs shaded for class 5") {
    REQUIRE(model1.GetFeatureProbsShaded(5)
            == model2.GetFeatureProbsShaded(5));
  }
}

TEST_CASE("Test prior probability computation") {
  Model model = Model();
  std::ifstream data_file(path_to_data);
  data_file >> model;
  model.Train();
  
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

TEST_CASE("Test feature probability computation") {
  Model model = Model();
  std::ifstream data_file(path_to_data);
  data_file >> model;
  model.Train();
  
  SECTION("First class nonempty") {
    float p1 = 0.333333f;
    float p2 = 0.666667f;
    
    std::vector<float> row_1 = {p1, p1, p1, p1, p1, p1, p1, p1, p1, p1};
    std::vector<float> row_2 = {p1, p1, p1, p2, p2, p2, p2, p1, p1, p1};
    std::vector<float> row_3 = {p1, p2, p2, p2, p1, p1, p2, p2, p2, p1};
  
    std::vector<std::vector<float>> matrix = {
        row_1, row_1, row_1, row_2, row_3, row_3, row_3, row_2, row_1, row_1
    };
    
    REQUIRE(model.GetFeatureProbsShaded(0)[0][0] == Approx(matrix[0][0]));
  }
  
  SECTION("Fifth class empty") {
    REQUIRE(model.GetFeatureProbsShaded(4).empty() == true);
  }

}

TEST_CASE("Test loading training images") {
  Model model = Model();
  std::ifstream data_file(path_to_data_2);
  data_file >> model;
  model.Train();
  
  SECTION("Correct total image count") {
    REQUIRE(model.GetTotalImageCount() == 5000);
  }
  
  SECTION("Correct row count") {
    REQUIRE(model.GetRowCount() == 28);
  }
  
  SECTION("Correct column count") {
    REQUIRE(model.GetColumnCount() == 28);
  }
  
  SECTION("Correct number of NumberClasses") {
    REQUIRE(model.GetNumberClasses().size() == 10);
  }
  
  SECTION("Correct number class counts") {
    std::vector<int> counts = {
      479, 563, 488, 493, 535, 434, 501, 550, 462, 495
    };
    REQUIRE(model.GetClassNumberCounts() == counts);
  }
  
  
} 