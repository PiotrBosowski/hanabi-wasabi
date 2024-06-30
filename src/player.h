#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "fuzzycard.h"

class Player {
  /**
   * The knowledge available only to the Player - can never be shared!
   * Is comprised of:
   * - all other players' hands (PRIVATE),
   */
  FuzzyCard private_knowledge;

public:
  void
  update_knowledge(const FuzzyCard &rejected_pool,
                   const FuzzyCard &played_cards,
                   std::vector<std::vector<FuzzyCard>> other_players_hands);
  void print();
};

#endif
