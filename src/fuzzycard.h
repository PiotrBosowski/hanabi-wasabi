#ifndef FUZZYCARD_H
#define FUZZYCARD_H

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
 * In both cases the underlying operation is performed element-wise across both
 * matrices entries. After each of these the resulting matrix is ALWAYS
 * NORMALIZED (i.e., its entries sum up to 1.0). The implementation forbids
 * the matrix from being not normalized at any moment.
 */

#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

const std::vector<int> mapping = {3, 2, 2, 2, 1};

class FuzzyCard {
public:
  FuzzyCard(bool empty = false);
  FuzzyCard(int color, int value);
  void setColor(int color);
  void setValue(int value);
  double getProbability(int color, int value) const;
  void print(bool probs = false) const;

  FuzzyCard operator+(const FuzzyCard &other) const {
    FuzzyCard result(true);
    for (int i = 0; i < NUM_COLORS; ++i) {
      for (int j = 0; j < NUM_VALUES; ++j) {
        result.counts[i][j] = this->counts[i][j] + other.counts[i][j];
      }
    }
    return result;
  }

  FuzzyCard operator-(const FuzzyCard &other) const {
    FuzzyCard result(true);
    for (int i = 0; i < NUM_COLORS; ++i) {
      for (int j = 0; j < NUM_VALUES; ++j) {
        result.counts[i][j] = this->counts[i][j] - other.counts[i][j];
      }
    }
    return result;
  }

  FuzzyCard operator*(const FuzzyCard &other) const {
    FuzzyCard result(true);
    for (int i = 0; i < NUM_COLORS; ++i) {
      for (int j = 0; j < NUM_VALUES; ++j) {
        result.counts[i][j] = this->counts[i][j] * other.counts[i][j];
      }
    }
    return result;
  }

  FuzzyCard operator=(const FuzzyCard &other) {
    for (int i = 0; i < NUM_COLORS; ++i) {
      for (int j = 0; j < NUM_VALUES; ++j) {
        counts[i][j] = other.counts[i][j];
      }
    }
    return *this;
  }

  FuzzyCard operator+=(const FuzzyCard &other) {
    for (int i = 0; i < NUM_COLORS; ++i) {
      for (int j = 0; j < NUM_VALUES; ++j) {
        counts[i][j] += other.counts[i][j];
      }
    }
    return *this;
  }

  static const int NUM_COLORS = 4;
  static const int NUM_VALUES = 5;

private:
  std::vector<std::vector<int>> counts;

  std::vector<std::vector<double>> get_probabilities() const;
};

#endif
