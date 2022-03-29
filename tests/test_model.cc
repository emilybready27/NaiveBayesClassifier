#include <catch2/catch.hpp>

#include <core/model.h>
#include <core/image.h>

using naivebayes::Model;

const std::string path_to_data_1 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\tinytrainingimagesandlabels.txt)";
const std::string path_to_data_2 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\minitrainingimagesandlabels.txt)";
const std::string path_to_data_3 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\trainingimagesandlabels.txt)";
const std::string path_to_save_1 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\tiny_save_file.txt)";
const std::string path_to_save_2 = R"(C:\Users\Mary\Desktop\Cinder\my-projects\naivebayes-ebready2\data\mini_save_file.txt)";

TEST_CASE("Test prior probabilities 3x3 images") {
  Model model = Model();
  std::ifstream data_file(path_to_data_1);
  data_file >> model;
  model.Train();
  
  SECTION("Correct P(class = 0)") {
    REQUIRE(model.GetPriorProbs()[0] == Approx(0.4));
  }
  SECTION("Correct P(class = 1)") {
    REQUIRE(model.GetPriorProbs()[1] == Approx(0.6));
  }
}

TEST_CASE("Test prior probabilities 10x10 images") {
  Model model = Model();
  std::ifstream data_file(path_to_data_2);
  data_file >> model;
  model.Train();
  
  SECTION("Correct P(class = 0)") {
    REQUIRE(model.GetPriorProbs()[0] == Approx(0.25));
  }
  SECTION("Correct P(class = 1)") {
    REQUIRE(model.GetPriorProbs()[1] == Approx(0.25));
  }
  SECTION("Correct P(class = 2)") {
    REQUIRE(model.GetPriorProbs()[2] == Approx(0.25));
  }
  SECTION("Correct P(class = 3)") {
    REQUIRE(model.GetPriorProbs()[3] == Approx(0.25));
  }
}

TEST_CASE("Test feature probabilities shaded given class 0 3x3") {
  Model model = Model();
  std::ifstream data_file(path_to_data_1);
  data_file >> model;
  model.Train();
  auto F = model.GetFeatureProbsShaded(0);
  
  SECTION("At (0,0)") {
    REQUIRE(F[0][0] == Approx(0.66667));
  }
  SECTION("At (0,1)") {
    REQUIRE(F[0][1] == Approx(0.66667));
  }
  SECTION("At (0,2)") {
    REQUIRE(F[0][2] == Approx(0.66667));
  }
  SECTION("At (1,0)") {
    REQUIRE(F[1][0] == Approx(0.66667));
  }
  SECTION("At (1,1)") {
    REQUIRE(F[1][1] == Approx(0.33333));
  }
  SECTION("At (1,2)") {
    REQUIRE(F[1][2] == Approx(0.66667));
  }
  SECTION("At (2,0)") {
    REQUIRE(F[2][0] == Approx(0.66667));
  }
  SECTION("At (2,1)") {
    REQUIRE(F[2][1] == Approx(0.66667));
  }
  SECTION("At (2,2)") {
    REQUIRE(F[2][2] == Approx(0.66667));
  }
}

TEST_CASE("Test feature probabilities shaded given class 1 3x3") {
  Model model = Model();
  std::ifstream data_file(path_to_data_1);
  data_file >> model;
  model.Train();
  auto F = model.GetFeatureProbsShaded(1);
  
  SECTION("At (0,0)") {
    REQUIRE(F[0][0] == Approx(0.5));
  }
  SECTION("At (0,1)") {
    REQUIRE(F[0][1] == Approx(0.75));
  }
  SECTION("At (0,2)") {
    REQUIRE(F[0][2] == Approx(0.25));
  }
  SECTION("At (1,0)") {
    REQUIRE(F[1][0] == Approx(0.25));
  }
  SECTION("At (1,1)") {
    REQUIRE(F[1][1] == Approx(0.75));
  }
  SECTION("At (1,2)") {
    REQUIRE(F[1][2] == Approx(0.25));
  }
  SECTION("At (2,0)") {
    REQUIRE(F[2][0] == Approx(0.5));
  }
  SECTION("At (2,1)") {
    REQUIRE(F[2][1] == Approx(0.75));
  }
  SECTION("At (2,2)") {
    REQUIRE(F[2][2] == Approx(0.5));
  }
}

TEST_CASE("Test extraction operator overload with data file") {
  Model model = Model();
  std::ifstream data_file(path_to_data_2);
  data_file >> model;
  model.Train();
  
  SECTION("Total class count derived correctly") {
    REQUIRE(model.GetTotalClassCount() == 4);
  }
  SECTION("Total image count derived correctly") {
    REQUIRE(model.GetTotalImageCount() == 4);
  }
  SECTION("Row count derived correctly") {
    REQUIRE(model.GetRowCount() == 10);
  }
  SECTION("Column count derived correctly") {
    REQUIRE(model.GetColumnCount() == 10);
  }
  SECTION("Class number counts derived correctly") {
    std::vector<int> class_number_counts = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    REQUIRE(model.GetClassNumberCounts() == class_number_counts);
  }
  
  SECTION("Number Classes derived and sorted correctly") {
    std::vector<int> class_numbers = {
        model.GetNumberClasses()[0].GetClassNumber(),
        model.GetNumberClasses()[1].GetClassNumber(),
        model.GetNumberClasses()[2].GetClassNumber(),
        model.GetNumberClasses()[3].GetClassNumber()
    };
    REQUIRE(class_numbers == std::vector<int>{0, 1, 2, 3});
  }
}

TEST_CASE("Test extraction operator overload with save file") {
  Model model = Model();
  std::ifstream save_file_read(path_to_save_2);
  save_file_read >> model;
  
  SECTION("Total class count derived correctly") {
    REQUIRE(model.GetTotalClassCount() == 4);
  }
  SECTION("Total image count derived correctly") {
    REQUIRE(model.GetTotalImageCount() == 4);
  }
  SECTION("Row count derived correctly") {
    REQUIRE(model.GetRowCount() == 10);
  }
  SECTION("Column count derived correctly") {
    REQUIRE(model.GetColumnCount() == 10);
  }
  SECTION("Class number counts derived correctly") {
    std::vector<int> class_number_counts = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    REQUIRE(model.GetClassNumberCounts() == class_number_counts);
  }
  
  SECTION("Number Classes derived and sorted correctly") {
    std::vector<int> class_numbers = {
        model.GetNumberClasses()[0].GetClassNumber(),
        model.GetNumberClasses()[1].GetClassNumber(),
        model.GetNumberClasses()[2].GetClassNumber(),
        model.GetNumberClasses()[3].GetClassNumber()
    };
    REQUIRE(class_numbers == std::vector<int>{0, 1, 2, 3});
  }
  
  SECTION("Prior probabilities derived correctly") {
    REQUIRE(model.GetPriorProbs().size() == 4);
  }
  
  SECTION("Feature probabilities shaded derived correctly class 0") {
    REQUIRE(model.GetFeatureProbsShaded(0).size() == 10);
  }
  SECTION("Feature probabilities shaded derived correctly class 1") {
    REQUIRE(model.GetFeatureProbsShaded(1).size() == 10);
  }
  SECTION("Feature probabilities shaded derived correctly class 2") {
    REQUIRE(model.GetFeatureProbsShaded(2).size() == 10);
  }
  SECTION("Feature probabilities shaded derived correctly class 3") {
    REQUIRE(model.GetFeatureProbsShaded(3).size() == 10);
  }
}

TEST_CASE("Test insertion operator overload") {
  Model model1 = Model();
  std::ifstream data_file(path_to_data_2);
  data_file >> model1;
  model1.Train();
  
  std::ofstream save_file(path_to_save_2);
  save_file << model1;
  
  Model model2 = Model();
  std::ifstream save_file_read(path_to_save_2);
  save_file_read >> model2;
  
  SECTION("Two models have same total class image count") {
    REQUIRE(model1.GetTotalClassCount() == model2.GetTotalClassCount());
  }
  
  SECTION("Two models have same total image count") {
    REQUIRE(model1.GetTotalImageCount() == model2.GetTotalImageCount());
  }
  
  SECTION("Two models have same row count") {
    REQUIRE(model1.GetRowCount() == model2.GetRowCount());
  }
  
  SECTION("Two models have same column count") {
    REQUIRE(model1.GetColumnCount() == model2.GetColumnCount());
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
}

TEST_CASE("Test loading 28x28 training images") {
  Model model = Model();
  std::ifstream data_file(path_to_data_3);
  data_file >> model;
  model.Train();
  
  SECTION("Correct total class count") {
    REQUIRE(model.GetTotalClassCount() == 10);
  }
  
  SECTION("Correct total image count") {
    REQUIRE(model.GetTotalImageCount() == 5000);
  }
  
  SECTION("Correct row count") {
    REQUIRE(model.GetRowCount() == 28);
  }
  
  SECTION("Correct column count") {
    REQUIRE(model.GetColumnCount() == 28);
  }
  
  SECTION("Correct class number counts") {
    std::vector<int> counts = {
        479, 563, 488, 493, 535, 434, 501, 550, 462, 495
    };
    REQUIRE(model.GetClassNumberCounts() == counts);
  }
  
  SECTION("Correct number of NumberClasses") {
    REQUIRE(model.GetNumberClasses().size() == 10);
  }
} 
