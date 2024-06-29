#ifndef PLAYER_H
#define PLAYER_H

#include "fuzzycard.h"
#include <vector>

class Player {
  // the knowledge available only to the Player - can never be shared!
  std::vector<FuzzyCard> private_knowledge;
  // the knowledge available to everyone - can always be shared
  std::vector<FuzzyCard> public_knowledge;
  // actual hand of cards - not visible to the player in Hanabi
  std::vector<FuzzyCard> deck;
};

#endif
