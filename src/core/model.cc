#include "core/model.h"
#include "core/file_writer.h"
#include <numeric>
#include <map>

namespace naivebayes {

Model::Model() {
  total_class_count_ = 0;
  total_class_count_ = 0;
}

void Model::Train() {
  ComputePriorProbs();
  ComputeFeatureProbsShaded();
}

std::istream& operator>> (std::istream& input, Model& model) {
  model.file_reader_ = FileReader(input);
  
  if (model.file_reader_.IsSaveFile()) {
    const FileReader::FauxModel& faux_model = model.file_reader_.GetFauxModel();
    model.ConstructSavedModel(faux_model);
  } else {
    std::vector<Image> images = model.file_reader_.GetData();
    model.SetClassNumberCounts(images);
    model.ConstructNumberClasses(images);
  }
  
  return input;
}

std::ostream& operator<< (std::ostream& output, Model& model) {
  model.file_writer_ = FileWriter(output,
                                  model.kLaplace,
                                  model.kMaxClassCount,
                                  model.total_class_count_,
                                  model.total_image_count_,
                                  model.row_count_,
                                  model.column_count_,
                                  model.class_number_counts_,
                                  model.number_classes_,
                                  model.prior_probs_);
  return output;
}

void Model::ConstructSavedModel(const FileReader::FauxModel& faux_model) {
  total_class_count_ = faux_model.total_class_count;
  total_image_count_ = faux_model.total_image_count;
  row_count_ = faux_model.row_count;
  column_count_ = faux_model.column_count;
  class_number_counts_ = faux_model.class_number_counts;
  number_classes_ = faux_model.number_classes;
  prior_probs_ = faux_model.prior_probs;
}

void Model::SetClassNumberCounts(const std::vector<Image>& images) {
  class_number_counts_ = std::vector<int>(kMaxClassCount, 0);
  for (const Image& image : images) {
    int class_number = image.GetClassNumber();
    class_number_counts_[class_number]++;
  }
  
  for (const int class_number_count : class_number_counts_) {
    if (class_number_count > 0) {
      total_class_count_++;
    }
  }
}

void Model::ConstructNumberClasses(const std::vector<Image>& images) {
  // initialize number classes
  // don't store this map because more difficult to save
  std::map<int, int> class_numbers;
  int count = 0;
  for (int i = 0; i < kMaxClassCount; i++) {
    // only build non-empty number classes
    if (class_number_counts_[i] != 0) {
      number_classes_.emplace_back(i);
      class_numbers[i] = count++;
    }
  }
  
  for (const Image& image : images) {
    int class_number = image.GetClassNumber();
    // add image to corresponding number class
    number_classes_[class_numbers[class_number]].AddImage(image);
  }
  
  row_count_ = number_classes_[0].GetRowCount();
  column_count_ = number_classes_[0].GetColumnCount();
}

void Model::ComputePriorProbs() {
  total_image_count_ = std::accumulate(class_number_counts_.begin(),
                                       class_number_counts_.end(), 0);
  
  for (const int class_number_count : class_number_counts_) {
    // only compute prior probability for non-empty classes
    if (class_number_count != 0) {
      float prob = (class_number_count + kLaplace) /
                   (total_image_count_ + (total_class_count_ * kLaplace));
      prior_probs_.push_back(prob);
    }
  }
}

void Model::ComputeFeatureProbsShaded() {
  for (NumberClass& number_class : number_classes_) {
    number_class.ComputeFeatureProbsShaded(kLaplace);
  }
}

float Model::GetKLaplace() const {
  return kLaplace;
}

int Model::GetKMaxClassCount() const {
  return kMaxClassCount;
}

int Model::GetTotalClassCount() const {
  return total_class_count_;
}

int Model::GetTotalImageCount() const {
  return total_image_count_;
}

int Model::GetRowCount() const {
  return row_count_;
}

int Model::GetColumnCount() const {
  return column_count_;
}

std::vector<int> Model::GetClassNumberCounts() const {
  return class_number_counts_;
}

std::vector<NumberClass> Model::GetNumberClasses() const {
  return number_classes_;
}

std::vector<float> Model::GetPriorProbs() const {
  return prior_probs_;
}

std::vector<std::vector<float>>
Model::GetFeatureProbsShaded(int class_number) const {
  return number_classes_[class_number].GetFeatureProbsShaded();
}

} // namespace naivebayes
