#include "fuzzycard.h"

FuzzyCard::FuzzyCard(bool empty)
    : counts(NUM_VALUES, std::vector<int>(NUM_COLORS, 0)) {
  // if no arguments, we initialize blindly taking mapping into account
  if (!empty) {
    for (int val = 0; val < NUM_VALUES; val++) {
      // Determine the value based on the mapping
      int count = mapping[val];
      // Assign the value to all rows in the current column
      for (int col = 0; col < NUM_COLORS; col++) {
        counts[val][col] = count;
      }
    }
  }
}

FuzzyCard::FuzzyCard(int color, int value)
    : counts(NUM_VALUES, std::vector<int>(NUM_COLORS, 0)) {
  counts[color][value] = 1.;
}

void FuzzyCard::setColor(int color) {
  if (color >= 0 && color < NUM_COLORS) {
    for (int i = 0; i < NUM_VALUES; ++i) {
      for (int j = 0; j < NUM_COLORS; ++j) {
        if (j != color) {
          counts[i][j] = 0;
        }
      }
    }
  } else {
    std::cerr << "Invalid color index" << std::endl;
  }
}

void FuzzyCard::setValue(int value) {
  if (value >= 0 && value < NUM_VALUES) {
    for (int j = 0; j < NUM_COLORS; ++j) {
      for (int i = 0; i < NUM_VALUES; ++i) {
        if (i != value) {
          counts[i][j] = 0;
        }
      }
    }
  } else {
    std::cerr << "Invalid value index" << std::endl;
  }
}

double FuzzyCard::getProbability(int value, int color) const {
  std::vector<std::vector<double>> probs = get_probabilities();
  if (value >= 0 && value < NUM_VALUES && color >= 0 && color < NUM_COLORS) {
    return probs[value][color];
  } else {
    std::cerr << "Invalid value or color index" << std::endl;
    return -1.0;
  }
}

void FuzzyCard::print(bool probs) const {
  if (probs) {
    auto probs_values = get_probabilities();
    for (const auto &row : probs_values) {
      for (auto prob : row) {
        std::cout << std::setw(10) << prob << " ";
      }
      std::cout << std::endl;
    }
  } else {
    for (const auto &row : counts) {
      for (auto prob : row) {
        std::cout << std::setw(10) << prob << " ";
      }
      std::cout << std::endl;
    }
  }
}

std::vector<std::vector<double>> FuzzyCard::get_probabilities() const {
  std::vector<std::vector<double>> probabilities(
      NUM_VALUES, std::vector<double>(NUM_COLORS, 0.));
  double sum = 0.0;
  for (const auto &row : counts) {
    sum += std::accumulate(row.begin(), row.end(), 0.0);
  }
  for (int val = 0; val < NUM_VALUES; val++) {
    for (int col = 0; col < NUM_COLORS; col++) {
      probabilities[val][col] = counts[val][col] / sum;
    }
  }
  return probabilities;
}
