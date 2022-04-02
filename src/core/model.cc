#include "core/model.h"
#include "core/file_writer.h"
#include <numeric>
#include <math.h>
#include <algorithm>
#include <iostream>

namespace naivebayes {

Model::Model() {
  total_class_count_ = 0;
  total_image_count_ = 0;
  row_count_ = 0;
  column_count_ = 0;
}

void Model::Train() {
  ComputePriorProbs();
  ComputeFeatureProbsShaded();
}

int Model::Classify(const Image& image) {
  std::vector<float> log_likelihoods = ComputeLogLikelihoods(image);
  
  auto max_it = std::max_element(log_likelihoods.begin(),
                                 log_likelihoods.end());
  return std::distance(log_likelihoods.begin(), max_it);
}

float Model::Validate() {
  for (const Image& image : validator_.GetImages()) {
    int actual_class_number = Classify(image);
    int expected_class_number = image.GetClassNumber();
    validator_.Compare(expected_class_number, actual_class_number);
  }
  
  return validator_.Validate();
}

std::istream& operator>> (std::istream& input, Model& model) {
  model.file_reader_ = FileReader(input);
  
  if (model.file_reader_.IsSaveFile()) {
    // store FauxModel state needed for saved Model instance
    const FileReader::FauxModel& faux_model = model.file_reader_.GetFauxModel();
    model.ConstructSavedModel(faux_model);
  } else {
    // process Images into the complete Model
    std::vector<Image> images = model.file_reader_.GetData();
    
    // continue building Model if not already complete
    // otherwise, initialize a Validator to test the Model
    if (model.number_classes_.size() == 0) {
      model.ConstructNumberClasses(images);
    } else {
      model.validator_ = Validator(images, model.kMaxClassCount);
    }
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

void Model::ConstructNumberClasses(const std::vector<Image>& images) {
  // row_count_ and column_count_ same for all images
  row_count_ = images[0].GetRowCount();
  column_count_ = images[0].GetColumnCount();
  
  for (int i = 0; i < kMaxClassCount; i++) {
    number_classes_.emplace_back(i,
                                 row_count_,
                                 column_count_);
    class_number_counts_.push_back(0);
    prior_probs_.push_back(0.0);
  }
  
  // add image to corresponding number class
  for (const Image& image : images) {
    int class_number = image.GetClassNumber();
    number_classes_[class_number].AddImage(image);
  }
  
  //
  for (int i = 0; i < kMaxClassCount; i++) {
    class_number_counts_[i] = number_classes_[i].GetClassNumberCount();
    if (class_number_counts_[i] > 0) {
      total_class_count_++;
    }
  }
}

void Model::ComputePriorProbs() {
  total_image_count_ = std::accumulate(class_number_counts_.begin(),
                                       class_number_counts_.end(), 0);
  
  for (int i = 0; i < kMaxClassCount; i++) {
    // only compute prior probability for nonempty classes
    if (class_number_counts_[i] > 0) {
      float prob = (class_number_counts_[i] + kLaplace) /
                   (total_image_count_ + (total_class_count_ * kLaplace));
      prior_probs_[i] = prob;
    }
  }
}

void Model::ComputeFeatureProbsShaded() {
  for (NumberClass& number_class : number_classes_) {
    number_class.ComputeFeatureProbsShaded(kLaplace);
  }
}

std::vector<float> Model::ComputeLogLikelihoods(const Image& image) {
  std::vector<float> log_likelihoods(kMaxClassCount, 0);
  for (int i = 0; i < kMaxClassCount; i++) {
    // empty NumberClasses not considered
    if (class_number_counts_[i] <= 0) {
      log_likelihoods[i] = -1 * std::numeric_limits<float>::infinity();
    } else {
      // add log of prior probability for class i
      log_likelihoods[i] += logf(prior_probs_[i]);
      
      // add log of feature probabilities based on shade of each pixel
      for (int j = 0; j < image.GetRowCount(); j++) {
        for (int k = 0; k < image.GetColumnCount(); k++) {
          if (image.IsPixelShaded(j, k)) {
            log_likelihoods[i] += logf(GetFeatureProbsShaded(i, j, k));
          } else {
            log_likelihoods[i] += logf(1 - GetFeatureProbsShaded(i, j, k));
          }
        }
      }
    }
  }
  return log_likelihoods;
}

void Model::PrintModel() const {
  for (int i = 0; i < kMaxClassCount; i++) {
    std::cout << prior_probs_[i] << " " << std::endl;
  }
  std::cout << std::endl;
  
  for (int k = 0; k < kMaxClassCount; k++) {
    for (int i = 0; i < row_count_; i++) {
      for (int j = 0; j < column_count_; j++) {
        std::cout << GetFeatureProbsShaded(k, i, j) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
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

const std::vector<int>& Model::GetClassNumberCounts() const {
  return class_number_counts_;
}

const std::vector<NumberClass>& Model::GetNumberClasses() const {
  return number_classes_;
}

const std::vector<float>& Model::GetPriorProbs() const {
  return prior_probs_;
}

float Model::GetFeatureProbsShaded(int class_number, int row,
                                        int column) const {
  return number_classes_[class_number].GetFeatureProbsShaded(row, column);
}

} // namespace naivebayes
