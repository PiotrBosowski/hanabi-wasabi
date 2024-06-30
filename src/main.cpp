#include "fuzzycard.h"
#include "hanabi.h"
#include <iostream>

int main() {
  FuzzyCard card;
  // Example of setting a color
  // card.setColor(2);

  // Example of getting a probability
  std::cout << "Probability of value 0, color 2: " << card.getProbability(0, 2)
            << std::endl;

  // Example of setting a value
  // card.setValue(1);

  // Print all probabilities
  std::cout << "All probabilities (normalized) after setting value:"
            << std::endl;
  card.print(true);

  Hanabi game = Hanabi();

  return 0;
}
