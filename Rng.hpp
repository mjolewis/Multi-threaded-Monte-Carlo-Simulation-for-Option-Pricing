//
// Random number generator. Currently, supports Mersenne Twister, Lagged Fibonacci, and Linear Congruential engines.
//
// Created by Michael Lewis on 9/10/23.
//

#ifndef MULTI_THREADED_MONTE_CARLO_SIMULATION_FOR_OPTION_PRICING_RNG_HPP
#define MULTI_THREADED_MONTE_CARLO_SIMULATION_FOR_OPTION_PRICING_RNG_HPP

#include <functional>
#include <string>
#include <utility>

// Alias for universal function wrapper that will cache the random number generator
using RngFunction = std::function<double (void)>;

class RNG
{
private:
    RngFunction rng;

    // Engines for Random Number Generator
    static double mersenneTwisterEngine();
    static double laggedFibonacciEngine();
    static double linearCongruentialEngine();

public:
    explicit RNG() = default;
    RNG(RngFunction _rng);
    RNG(const RNG& other) = default;
    RNG(RNG&& other) noexcept;
    virtual ~RNG() = default;

    // Operator Overloads
    RNG& operator=(const RNG& other);
    RNG& operator=(RNG&& other) noexcept;

    // Engine API
    std::pair<RngFunction, std::string> buildEngine();
};


#endif //MULTI_THREADED_MONTE_CARLO_SIMULATION_FOR_OPTION_PRICING_RNG_HPP
