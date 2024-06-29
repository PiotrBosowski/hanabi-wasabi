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
  Hanabi(int num_players);

private:
  std::vector<FuzzyCard> hidden_pool;
  std::vector<FuzzyCard> rejected_pool;
  int hints_left;
};

#endif
