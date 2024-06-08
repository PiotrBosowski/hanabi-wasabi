#include "card.h"


Card::Card() : probabilities(NUM_VALUES, std::vector<double>(NUM_COLORS, 1.0 / (NUM_VALUES * NUM_COLORS))) {
    normalizeProbabilities();
}

void Card::setColor(int color){
    if (color >= 0 && color < NUM_COLORS) {
        for (int i = 0; i < NUM_VALUES; ++i) {
            for (int j = 0; j < NUM_COLORS; ++j) {
                if (j != color) {
                    probabilities[i][j] = 0.0;
                }
            }
        }
        normalizeProbabilities();
    } else {
        std::cerr << "Invalid color index" << std::endl;
    }
}


void Card::setValue(int value){
    if (value >= 0 && value < NUM_VALUES) {
        for (int j = 0; j < NUM_COLORS; ++j) {
            for (int i = 0; i < NUM_VALUES; ++i) {
                if (i != value) {
                    probabilities[i][j] = 0.0;
                }
            }
        }
        normalizeProbabilities();
    } else {
        std::cerr << "Invalid value index" << std::endl;
    }
}


double Card::getProbability(int value, int color) const {
        if (value >= 0 && value < NUM_VALUES && color >= 0 && color < NUM_COLORS) {
            return probabilities[value][color];
        } else {
            std::cerr << "Invalid value or color index" << std::endl;
            return -1.0;
        }
}


void Card::printProbabilities() const {
    for (const auto& row : probabilities) {
        for (double prob : row) {
            std::cout << std::setw(10) << prob << " ";
        }
        std::cout << std::endl;
    }
}


void Card::normalizeProbabilities() {
    double sum = 0.0;
    for (const auto& row : probabilities) {
        sum += std::accumulate(row.begin(), row.end(), 0.0);
    }

    if (sum == 0.0) {
        // If the sum is 0, set uniform distribution
        double uniform_prob = 1.0 / (NUM_VALUES * NUM_COLORS);
        for (auto& row : probabilities) {
            std::fill(row.begin(), row.end(), uniform_prob);
        }
    } else {
        for (auto& row : probabilities) {
            for (double& prob : row) {
                prob /= sum;
            }
        }
    }
}