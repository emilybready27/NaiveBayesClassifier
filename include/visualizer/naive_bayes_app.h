#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sketchpad.h"
#include "core/model.h"

namespace naivebayes {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class NaiveBayesApp : public ci::app::App {
 public:
  NaiveBayesApp();

  void setup() override;
  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowSize = 875;
  const double kMargin = 100;
  const size_t kImageDimension = 28;

 private:
  /**
   * Contains the pixelated information.
   */
  Sketchpad sketchpad_;
  
  /**
   * Contains the Naive Bayes Model for classification.
   */
  Model model_;
  
  /**
   * The prediction of the number drawn.
   */
  int current_prediction_ = -1;
};

}  // namespace visualizer

}  // namespace naivebayes
