#include "hanabi.h"

Hanabi::Hanabi(int num_players) : hints_left{8} {
  for (int val = 0; val < FuzzyCard::NUM_VALUES; val++) {
    for (int col = 0; col < FuzzyCard::NUM_COLORS; col++) {
      auto repeats = mapping[val];
      while (repeats--) {
        hidden_pool.push_back(FuzzyCard(val, col));
      }
    }
  }
  auto sum = std::accumulate(hidden_pool.begin() + 1, hidden_pool.end(),
                             FuzzyCard(true));
  std::cout << "Total counts of cards:" << std::endl;
  sum.print();
}
