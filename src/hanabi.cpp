#include "hanabi.h"

Hanabi::Hanabi() : hints_left{8} {
  for (int val = 0; val < NUM_VALUES; val++) {
    for (int col = 0; col < NUM_COLORS; col++) {
      auto repeats = mapping[val];
      while (repeats--) {
        hidden_deck.push_back(FuzzyCard(val, col));
      }
    }
  }
  auto sum = std::accumulate(hidden_deck.begin() + 1, hidden_deck.end(),
                             hidden_deck[0]);
  std::cout << "Total counts of cards:" << std::endl;
  sum.print();
}
