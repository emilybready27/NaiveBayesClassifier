# Naive Bayes Classifier
Handwriting recognition is the ability of a computer to interpret handwritten text as unicode characters. This C++ application attempts to recognize numbers from images using a Naive Bayes classifier.

Naive Bayes classifiers are a family of probabilistic classifiers that are based on Bayes’ Theorem. These algorithms work by combining the probabilities that an instance belongs to a class based on the value of a set of features. In this case, we classify images of handwritten digits, where each image depicts a number between 0 to 9, inclusive.

### Objective
Using your mouse or touchpad, draw a digit within the white grid space. Press Enter to see the prediction at the bottom of the window. Press Delete to clear or make a new drawing.

For example:
![Screenshot 2022-08-22 140542](https://user-images.githubusercontent.com/85314134/185999590-daf0d4a1-2ed6-4fb6-aaf0-fac496d5c6f6.jpg)

### Dependencies
This program takes advantage of the Cinder C++ open source library, available to macOS and Windows users. As such, you will need to:
* First make sure you have an IDE for C++ downloaded and installed (CLion by JetBrains recommended: https://www.jetbrains.com/clion/download/)
* Download Cinder for your platform: https://libcinder.org/download.
* Perform the initial build of libcinder in the IDE.
* Download this repository into the folder my-projects to complete the setup.

For more information, visit https://www.libcinder.org/docs/guides/.
