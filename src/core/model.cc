#include "core/model.h"
#include "core/file_writer.h"
#include <numeric>
#include <map>
#include <math.h>
#include <algorithm>

namespace naivebayes {

Model::Model() {
  total_class_count_ = 0;
  total_image_count_ = 0;
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



std::istream& operator>> (std::istream& input, Model& model) {
  model.file_reader_ = FileReader(input);
  
  if (model.file_reader_.IsSaveFile()) {
    // store FauxModel state needed for saved Model instance
    const FileReader::FauxModel& faux_model = model.file_reader_.GetFauxModel();
    model.ConstructSavedModel(faux_model);
  } else {
    // process Images into the complete Model
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
  // map nonempty class numbers to index in number_classes_ vector
  std::map<int, int> class_numbers;
  int count = 0;
  for (int i = 0; i < kMaxClassCount; i++) {
    // only build nonempty number classes
    if (class_number_counts_[i] != 0) {
      number_classes_.emplace_back(i);
      class_numbers[i] = count++;
    }
  }
  
  // add image to corresponding number class
  for (const Image& image : images) {
    int class_number = image.GetClassNumber();
    number_classes_[class_numbers[class_number]].AddImage(image);
  }
  
  // row_count_ and column_count_ same for all images
  row_count_ = number_classes_[0].GetRowCount();
  column_count_ = number_classes_[0].GetColumnCount();
}

void Model::ComputePriorProbs() {
  total_image_count_ = std::accumulate(class_number_counts_.begin(),
                                       class_number_counts_.end(), 0);
  
  for (const int class_number_count : class_number_counts_) {
    // only compute prior probability for nonempty classes
    if (class_number_count > 0) {
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
            log_likelihoods[i] += logf(GetFeatureProbsShadedPixel(i, j, k));
          } else {
            log_likelihoods[i] += logf(1 - GetFeatureProbsShadedPixel(i, j, k));
          }
        }
      }
    }
  }
  return log_likelihoods;
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

float Model::GetFeatureProbsShadedPixel(int class_number, int row,
                                        int column) const {
  return number_classes_[class_number].GetFeatureProbsShaded()[row][column];
}

} // namespace naivebayes
