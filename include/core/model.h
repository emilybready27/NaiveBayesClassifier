#pragma once

#include "number_class.h"
#include "file_reader.h"
#include "file_writer.h"
#include "validator.h"

namespace naivebayes {

/**
 * Model that stores the Image information and probabilities needed
 * to compute the classification probabilities.
 */
class Model {
 public:
  /**
   * Default constructor.
   */
  Model();
  
  /**
   * Computes the prior and feature probabilities.
   */
  void Train();

  /**
   * Classifies the given new Image as a digit (0-9) using the
   * log-likelihoods provided by the calling Model.
   * @param image Image
   * @return int
   */
  int Classify(const Image& image);
  
  /**
   * Computes the log-likelihoods that the given Image belongs to
   * each of the different NumberClasses.
   * @param image Image
   * @return std::vector<float>
   */
  std::vector<float> ComputeLogLikelihoods(const Image& image);
  
  /**
   * Tests the accuracy of the calling Model by returning an overall accuracy.
   */
  float Validate();
  
  /**
   * Extracts the input from the given stream and continues construction
   * of the given Model.
   * @param in std::istream
   * @param model Model
   * @return std::istream
   */
  friend std::istream& operator>> (std::istream& in, Model& model);
  
  /**
   * Inserts the Model state into the given output stream.
   * @param out std::ostream
   * @param model Model
   * @return std::ostream
   */
  friend std::ostream& operator<< (std::ostream& out, Model& model);
  
  void PrintModel() const;
  
  /**
   * Getters for Model state.
   */
  float GetKLaplace() const;
  int GetKMaxClassCount() const;
  int GetTotalClassCount() const;
  int GetTotalImageCount() const;
  int GetRowCount() const;
  int GetColumnCount() const;
  std::vector<int> GetClassNumberCounts() const;
  std::vector<NumberClass> GetNumberClasses() const;
  std::vector<float> GetPriorProbs() const;
  std::vector<std::vector<float>> GetFeatureProbsShaded(int class_number) const;
  float GetFeatureProbsShadedPixel(int class_number, int row, int column) const;

 private:
  /**
   * Used to read the input file stream into the Model.
   */
  FileReader file_reader_;
  
  /**
   * Used to write to an output file to save for later.
   */
  FileWriter file_writer_;
  
  /**
   * Used to validate the accuracy of the Model's classifications.
   */
  Validator validator_;
  
  /**
   * Smoothing constant to prevent probabilities from being zero.
   */
  constexpr const static float kLaplace = 1.0;
  
  /**
   * Number of Number Classes (when each is represented at least once).
   */
  const static int kMaxClassCount = 10;
  
  /**
   * Number of Number Classes (may be less than or equal to 10).
   */
  int total_class_count_;
  
  /**
   * Number of images loaded in from training data.
   */
  int total_image_count_;
  
  /**
   * Number of rows in each Image / in each probability matrix.
   */
  int row_count_;
  
  /**
   * Number of columns in each Image / in each probability matrix.
   */
  int column_count_;
  
  /**
   * Stores a list of size kMaxClassCount where each index corresponds to
   * the number of images of that particular class number.
   */
  std::vector<int> class_number_counts_;
  
  /**
   * Stores a list of total_class_count_ different classes of numbers.
   */
  std::vector<NumberClass> number_classes_;
  
  /**
   * Stores a list of total_class_count_ prior probabilities.
   */
  std::vector<float> prior_probs_;
  
  /**
   * Extracts the state stored by the FauxModel struct to to store
   * in the reconstructed Model.
   * @param faux_model FileReader::FauxModel
   */
  void ConstructSavedModel(const FileReader::FauxModel& faux_model);
  
  /**
   * Builds the vector of NumberClasses from the given vector of Images.
   * @param images std::vector<Image>
   */
  void ConstructNumberClasses(const std::vector<Image>& images);
  
  /**
   * Computes the prior probabilities and stores them internally.
   */
  void ComputePriorProbs();
  
  /**
   * Computes the feature probabilities of shaded pixels and stores them
   * within the vector of NumberClasses.
   * Note that the feature probabilities of unshaded pixels is derived by
   * 1 - feature probabilities of shaded pixels, so storage isn't necessary.
   */
  void ComputeFeatureProbsShaded();
};

} // namespace naivebayes