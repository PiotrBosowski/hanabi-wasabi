/**
 * This class represents a knowledge about a given card or a set of cards.
 * The knowledge is spread across a matrix with #VALUES columns and #COLORS
 * rows. The matrix contains probabilities of the card being of certain
 * VALUE and COLOR. The name "Fuzzy" comes from the capabilities of represent
 * uncertainties between several cards.
 *
 * A trivial example: A card of a known COLOR and VALUE will ultimately be
 * represented as a zero-matrix with a single non-zero entry (1.0) at the
 * corresponding entry (of the coordinates COLOR,VALUE).
 *
 * Moreover, the class can also represent a knowledge about a set of cards.
 * For example, if the stack of the remaining cards contains YELLOW-1 and
 * BLUE-2, the matrix will have 2 non-zero entries: at the coordinates
 * (1, YELLOW) and (2, BLUE), both being equal to 0.5.
 *
 * There are also defined possible operations that cards can undergo:
 * - addition,
 * - multiplication.
 * In both cases the underlying operation is performed elemen-wise across both
 * matrices entries. After each of these the resulting matrix is ALWAYS
 * NORMALIZED (i.e., its entries sum up to 1.0). The implementation forbids
 * the matrix from being not normalized at any moment.
 */

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
