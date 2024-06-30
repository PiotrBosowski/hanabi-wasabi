#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "fuzzycard.h"

class Hanabi;

class Player {
  /**
   * The knowledge available only to the Player - can never be shared!
   * Is comprised of:
   * - all other players' hands (PRIVATE),
   */
  FuzzyCard private_knowledge;
  std::vector<FuzzyCard> beliefs_about_hand;
  int cards_on_hand;
  const Hanabi &game;

public:
  Player(const Hanabi &game, int cards_on_hand);
  void
  update_knowledge(const FuzzyCard &rejected_pool,
                   const FuzzyCard &played_cards,
                   std::vector<std::vector<FuzzyCard>> other_players_hands);
  void print();
};

#endif
