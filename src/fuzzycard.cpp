#include "fuzzycard.h"

FuzzyCard::FuzzyCard(bool empty)
    : counts(NUM_COLORS, std::vector<int>(NUM_VALUES, 0)) {
  if (!empty) {
    for (int col = 0; col < NUM_COLORS; col++) {
      for (int val = 0; val < NUM_VALUES; val++) {
        int count = mapping[val];
        counts[col][val] = count;
      }
    }
  }
}

FuzzyCard::FuzzyCard(int color, int value)
    : counts(NUM_COLORS, std::vector<int>(NUM_VALUES, 0)) {
  counts[color][value] = 1.;
}

void FuzzyCard::setColor(int color) {
  if (color >= 0 && color < NUM_COLORS) {
    for (int j = 0; j < NUM_COLORS; ++j) {
      for (int i = 0; i < NUM_VALUES; ++i) {
        if (j != color) {
          counts[j][i] = 0;
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
          counts[j][i] = 0;
        }
      }
    }
  } else {
    std::cerr << "Invalid value index" << std::endl;
  }
}

double FuzzyCard::getProbability(int color, int value) const {
  std::vector<std::vector<double>> probs = get_probabilities();
  return probs[color][value];
}

void FuzzyCard::print(bool probs) const {
  auto probs_values = get_probabilities();
  for (int val = 0; val < NUM_VALUES; val++) {
    for (int col = 0; col < NUM_COLORS; col++) {
      auto item = (probs) ? probs_values[col][val] : counts[col][val];
      std::cout << std::fixed << std::setprecision(3) << std::setw(7) << item
                << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<std::vector<double>> FuzzyCard::get_probabilities() const {
  std::vector<std::vector<double>> probabilities(
      NUM_COLORS, std::vector<double>(NUM_VALUES, 0.));
  double sum = 0.0;
  for (const auto &row : counts) {
    sum += std::accumulate(row.begin(), row.end(), 0.0);
  }
  for (int col = 0; col < NUM_COLORS; col++) {
    for (int val = 0; val < NUM_VALUES; val++) {
      probabilities[col][val] = counts[col][val] / sum;
    }
  }
  return probabilities;
}

bool FuzzyCard::is_contiguous() const {
  for (int col = 0; col < NUM_COLORS; col++) {
    bool color_continue = true;
    for (int val = 0; val < NUM_VALUES; val++) {
      auto current = counts[col][val];
      if (current > 1)
        return false;
      if (color_continue) {
        if (!current) {
          color_continue = false;
        }
      } else {
        if (current)
          return false;
      }
    }
  }
  return true;
}
