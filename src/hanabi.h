#ifndef HANABI_H
#define HANABI_H

#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

#include "fuzzycard.h"
#include "player.h"

class Hanabi {
public:
  Hanabi(int num_players = 2);
  void play_card(FuzzyCard);

private:
  std::vector<FuzzyCard> hidden_pool;
  // both rejected and played cards can be represented as a single FuzzyCard
  // (TM)
  FuzzyCard rejected_pool;
  FuzzyCard played_cards;
  int hints_left;
  int num_players;
  std::vector<Player> players;
  std::vector<std::vector<FuzzyCard>> players_hands;
  void update_players_knowledge();
};

#endif
