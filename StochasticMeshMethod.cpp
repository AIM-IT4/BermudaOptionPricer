
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// Parameters for the model
const int n = 100;   // Number of paths
const int M = 3;     // Number of time steps (e.g., 3 years)
const double S0 = 100.0; // Initial stock price
const double r = 0.05;   // Risk-free rate
const double dt = 1.0;   // Time step size
const double volatility = 0.2; // Volatility

// Function to simulate stock price paths
std::vector<std::vector<double>> generatePaths() {
    std::vector<std::vector<double>> paths(n, std::vector<double>(M + 1));
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    for (int j = 0; j < n; ++j) {
        paths[j][0] = S0;
        for (int k = 1; k <= M; ++k) {
            double Z = distribution(generator);
            paths[j][k] = paths[j][k - 1] * exp((r - 0.5 * volatility * volatility) * dt + volatility * sqrt(dt) * Z);
        }
    }

    return paths;
}

// Function to calculate the payoff (example: European Call Option)
double payoff(double stockPrice) {
    double strikePrice = 100.0; // Example strike price
    return std::max(stockPrice - strikePrice, 0.0);
}

// Main function
int main() {
    std::vector<std::vector<double>> paths = generatePaths();

    // Backward induction
    for (int k = M - 1; k >= 0; --k) {
        for (int i = 0; i < n; ++i) {
            double exerciseValue = payoff(paths[i][k]);
            double continuationValue = 0.0;
            for (int j = 0; j < n; ++j) {
                continuationValue += payoff(paths[j][k + 1]) / n;
            }
            paths[i][k] = std::max(exerciseValue, continuationValue * exp(-r * dt));
        }
    }

    // Calculate the initial option value
    double initialOptionValue = 0.0;
    for (int i = 0; i < n; ++i) {
        initialOptionValue += paths[i][0] / n;
    }

    std::cout << "Estimated initial option value: " << initialOptionValue << std::endl;

    return 0;
}
