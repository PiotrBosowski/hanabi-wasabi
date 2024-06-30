#ifndef PLAYER_H
#define PLAYER_H

#include "fuzzycard.h"
#include <vector>

class Player {
  /**
   * The knowledge available only to the Player - can never be shared!
   * Is comprised of:
   * - all other players' hands (PRIVATE),
   * - rejected cards,
   * - played cards.
   */
  std::vector<FuzzyCard> private_knowledge;

  /**
   * The knowledge available to everyone - can always be shared.
   * Is comprised of:
   * - rejected cards,
   * - played cards.
   */
  std::vector<FuzzyCard> public_knowledge;

  // actual hand of cards - not visible to the player in Hanabi
  std::vector<FuzzyCard> hand;

public:
  void
  update_knowledge(const FuzzyCard &rejected_pool,
                   const FuzzyCard &played_cards,
                   std::vector<std::vector<FuzzyCard>> other_players_hands);
};

#endif
