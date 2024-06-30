#include <algorithm>

#include "player.h"

void Player::update_knowledge(
    const FuzzyCard &rejected_pool, const FuzzyCard &played_cards,
    std::vector<std::vector<FuzzyCard>> other_players_hands) {
  private_knowledge = FuzzyCard(true);
  for (auto players_hand : other_players_hands) {
    private_knowledge += std::accumulate(players_hand.begin(),
                                         players_hand.end(), FuzzyCard(true));
  }
}

void Player::print() {
  std::cout << std::endl << "Player's private knowledge:" << std::endl;
  private_knowledge.print();
}
