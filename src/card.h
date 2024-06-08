#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>

class Card {
public:
    static const int NUM_VALUES = 5;
    static const int NUM_COLORS = 5;

    Card();
    void setColor(int color);
    void setValue(int value);
    double getProbability(int value, int color) const;
    void printProbabilities() const;

private:
    std::vector<std::vector<double>> probabilities;

    void normalizeProbabilities() {
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
};

int main() {
    Card card;

    // Example of setting a color
    card.setColor(2);

    // Example of getting a probability
    std::cout << "Probability of value 0, color 2: " << card.getProbability(0, 2) << std::endl;

    // Print all probabilities
    std::cout << "All probabilities (normalized):" << std::endl;
    card.printProbabilities();

    // Example of setting a value
    card.setValue(1);

    // Print all probabilities
    std::cout << "All probabilities (normalized) after setting value:" << std::endl;
    card.printProbabilities();

    return 0;
}
