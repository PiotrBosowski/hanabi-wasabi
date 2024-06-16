#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

class FuzzyCard {
public:
  static const int NUM_VALUES = 6;
  static const int NUM_COLORS = 4;

  FuzzyCard();
  void setColor(int color);
  void setValue(int value);
  double getProbability(int value, int color) const;
  void printProbabilities() const;

private:
  std::vector<std::vector<double>> probabilities;

  void normalizeProbabilities();

  FuzzyCard operator+(const FuzzyCard &other) const {
    FuzzyCard result;
    for (int i = 0; i < NUM_VALUES; ++i) {
      for (int j = 0; j < NUM_COLORS; ++j) {
        result.probabilities[i][j] =
            this->probabilities[i][j] + other.probabilities[i][j];
      }
    }
    result.normalizeProbabilities();
    return result;
  }

  FuzzyCard operator*(const FuzzyCard &other) const {
    FuzzyCard result;
    for (int i = 0; i < NUM_VALUES; ++i) {
      for (int j = 0; j < NUM_COLORS; ++j) {
        result.probabilities[i][j] =
            this->probabilities[i][j] * other.probabilities[i][j];
      }
    }
    result.normalizeProbabilities();
    return result;
  }
};
