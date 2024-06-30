#include <algorithm>
#include <chrono>
#include <random>

#include "hanabi.h"

Hanabi::Hanabi(int num_players)
    : hints_left{8}, num_players{num_players}, rejected_pool{true},
      played_cards{true} {
  for (int val = 0; val < FuzzyCard::NUM_VALUES; val++) {
    for (int col = 0; col < FuzzyCard::NUM_COLORS; col++) {
      auto repeats = mapping[val];
      while (repeats--) {
        hidden_pool.push_back(FuzzyCard(val, col));
      }
    }
  }
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rng(seed);
  std::shuffle(std::begin(hidden_pool), std::end(hidden_pool), rng);

  for (int i = 0; i < 5; i++) {
    rejected_pool += hidden_pool.back();
    hidden_pool.pop_back();
  }

  auto sum =
      std::accumulate(hidden_pool.begin(), hidden_pool.end(), FuzzyCard(true));
  std::cout << "Total counts of cards in deck:" << std::endl;
  sum.print();
  std::cout << "Total counts of cards in rejected pool:" << std::endl;
  rejected_pool.print();
}

void Hanabi::play_card(FuzzyCard card) {
  played_cards += card;
  update_players_knowledge();
}

void Hanabi::update_players_knowledge() {
  for (int i = 0; i < num_players; i++) {
    std::vector<std::vector<FuzzyCard>> other_players_hands;
    for (int j = 0; j < players_hands.size(); ++j) {
      if (j != i) {
        other_players_hands.push_back(players_hands[i]);
      }
    }
    players[i].update_knowledge(rejected_pool, played_cards,
                                other_players_hands);
  }
}
