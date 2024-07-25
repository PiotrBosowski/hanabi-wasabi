#include <algorithm>
#include <chrono>
#include <random>

#include "hanabi.h"

Hanabi::Hanabi(int num_players, int cards_on_hand)
    : num_players{num_players}, rejected_pool{true},
      cards_on_hand{cards_on_hand}, played_cards{true},
      players_hands(num_players) {
  players = std::vector<Player>(num_players, Player{*this, cards_on_hand});
  for (int col = 0; col < FuzzyCard::NUM_COLORS; col++) {
    for (int val = 0; val < FuzzyCard::NUM_VALUES; val++) {
      auto repeats = mapping[val];
      while (repeats--) {
        hidden_pool.push_back(FuzzyCard(col, val));
      }
    }
  }
  // shuffle cards
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rng(seed);
  std::shuffle(std::begin(hidden_pool), std::end(hidden_pool), rng);

  // split among players
  for (int i = 0; i < num_players * cards_on_hand; i++) {
    give_player_a_card(i % num_players);
  }

  std::cout << "Making 2 moves" << std::endl;
  play_card(0, 0);
  play_card(0, 0);

  auto sum =
      std::accumulate(hidden_pool.begin(), hidden_pool.end(), FuzzyCard(true));
  std::cout << "Total counts of hidden cards (deck):" << std::endl;
  sum.print();
  std::cout << "Total counts of cards in rejected pool:" << std::endl;
  rejected_pool.print();

  std::cout << "Public knowledge:" << std::endl;
  public_knowledge().print();

  for (auto player : players) {
    player.print();
  }
}

FuzzyCard Hanabi::public_knowledge() const {
  /**
   * The knowledge available to everyone - can always be shared.
   * Is comprised of:
   * - rejected cards,
   * - played cards.
   */
  FuzzyCard public_knowledge = rejected_pool + played_cards;
  return public_knowledge;
}

void Hanabi::play_card(int player_id, int card_id) {
  auto the_card = players_hands[player_id][card_id];
  players_hands[player_id].erase(players_hands[player_id].begin() + card_id);
  auto postmove_result = played_cards + the_card;
  if (postmove_result.is_contiguous()) {
    std::cout << "Move accepted" << std::endl;
    played_cards = postmove_result;
  } else {
    mistakes_left--;
    rejected_pool += the_card;
    std::cout << "Move rejected (" << mistakes_left << " mistakes left)"
              << std::endl;
  }
  give_player_a_card(player_id);
  update_players_knowledge();
}

void Hanabi::give_player_a_card(int player_id) {
  FuzzyCard card = hidden_pool.back();
  players_hands[player_id].push_back(card);
  hidden_pool.pop_back();
  update_players_knowledge();
}

void Hanabi::update_players_knowledge() {
  for (int i = 0; i < num_players; i++) {
    std::vector<std::vector<FuzzyCard>> other_players_hands;
    for (int j = 0; j < players_hands.size(); j++) {
      if (j != i) {
        other_players_hands.push_back(players_hands[j]);
      }
    }
    players[i].update_knowledge(rejected_pool, played_cards,
                                other_players_hands);
  }
}
