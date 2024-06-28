#ifndef HANABI_H
#define HANABI_H

#include "card.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

class Hanabi {
public:
  Hanabi();

private:
  std::vector<FuzzyCard> hidden_deck;
  int hints_left;
};

#endif
