#include <algorithm>

#include "hanabi.h"
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
  std::cout << std::endl
            << "Player's beliefs about the cards on hand:" << std::endl;
  for (auto beliefs : beliefs_about_hand) {
    (beliefs - game.public_knowledge()).print(true);
    std::cout << std::endl;
  }
}

Player::Player(const Hanabi &game, int cards_on_hand)
    : game{game}, cards_on_hand{cards_on_hand} {
  beliefs_about_hand = std::vector<FuzzyCard>(cards_on_hand, FuzzyCard(false));
}
