
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

// Parameters
const int n = 100; // Number of paths
const int M = 3; // Number of time steps
const double S0 = 100.0; // Initial stock price
const double r = 0.05; // Risk-free rate
const double dt = 1.0; // Time step size
const double volatility = 0.2; // Volatility

// Random number generator
std::default_random_engine generator;
std::normal_distribution<double> distribution(0.0, 1.0);

// Function to simulate a stochastic tree
std::vector<std::vector<double>> generateStochasticTree() {
    std::vector<std::vector<double>> tree(n, std::vector<double>(M + 1, S0));

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= M; ++j) {
            double Z = distribution(generator);
            tree[i][j] = tree[i][j - 1] * exp((r - 0.5 * volatility * volatility) * dt + volatility * sqrt(dt) * Z);
        }
    }

    return tree;
}

// Function to calculate the option payoff
double payoff(double stockPrice) {
    double strikePrice = 100.0; // Example strike price
    return std::max(stockPrice - strikePrice, 0.0);
}

// Main function
int main() {
    std::vector<std::vector<double>> tree = generateStochasticTree();

    // Calculate option values
    for (int j = M; j > 0; --j) {
        for (int i = 0; i < n; ++i) {
            double exerciseValue = payoff(tree[i][j]);
            double expectedValue = 0.0;
            for (int k = 0; k < n; ++k) {
                expectedValue += payoff(tree[k][j - 1]) / n;
            }
            tree[i][j] = std::max(exerciseValue, expectedValue * exp(-r * dt));
        }
    }

    // Calculate the initial option value
    double initialOptionValue = 0.0;
    for (int i = 0; i < n; ++i) {
        initialOptionValue += tree[i][1] / n;
    }

    std::cout << "Estimated initial option value: " << initialOptionValue << std::endl;

    return 0;
}
