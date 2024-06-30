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
  Hanabi(int num_players = 3, int cards_on_hand = 5);
  void play_card(int player_id, int card_id);

private:
  std::vector<FuzzyCard> hidden_pool;
  // both rejected and played cards can be represented as a single FuzzyCard
  // (TM)
  FuzzyCard rejected_pool;
  FuzzyCard played_cards;
  int hints_left = 8;
  int mistakes_left = 3;
  int num_players;
  int cards_on_hand;
  std::vector<Player> players;
  std::vector<std::vector<FuzzyCard>> players_hands;
  void update_players_knowledge();
  bool check_played_integrity();
  void give_player_a_card(int player_id);
};

#endif
