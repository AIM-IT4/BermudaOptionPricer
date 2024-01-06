
# Option Pricing Models

This repository contains implementations of two methods for option pricing: the Stochastic Mesh Method and the Stochastic Tree Method. These are used to estimate the no-arbitrage price of Bermudan options.

## Stochastic Mesh Method

This method involves generating multiple paths for the underlying asset price and then calculating the option's value at each step by considering both the exercise value and the expected future value.

File: `StochasticMeshMethod.cpp`

## Stochastic Tree Method

This method, distinct from the simple binomial tree, uses a more complex approach to generate a multi-step, non-binomial tree to model the underlying asset price and compute the option values.

File: `StochasticTreeMethod.cpp`

## Usage

Compile the C++ files using a C++ compiler and run the executable to see the estimated option values. These implementations are meant for educational purposes and do not include complexities of real-world financial modeling.

```
g++ StochasticMeshMethod.cpp -o StochasticMeshMethod
./StochasticMeshMethod

g++ StochasticTreeMethod.cpp -o StochasticTreeMethod
./StochasticTreeMethod
```

## Disclaimer

These code examples are simplified and intended for educational purposes. They do not account for various factors involved in real-world financial option pricing.
