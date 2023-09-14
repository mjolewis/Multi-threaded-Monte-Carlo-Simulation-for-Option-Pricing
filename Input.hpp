//
// Exposes multiple APIs to allow either users or programmatic clients to customize the option data that will
// later be used by the Pricer
//
// Created by Michael Lewis on 9/11/23.
//

#ifndef MULTI_THREADED_MONTE_CARLO_SIMULATION_FOR_OPTION_PRICING_INPUT_HPP
#define MULTI_THREADED_MONTE_CARLO_SIMULATION_FOR_OPTION_PRICING_INPUT_HPP

#include "OptionData.hpp"

class Input
{
private:
    OptionData optionData;

public:
    Input();
    Input(const Input& other);
    Input(Input&& other) noexcept;
    explicit Input(const OptionData& optionData);
    Input(double& K, double& T, double& r, double& sig, double& S, unsigned long& NSIM, double& D, int& type);
    Input(double&& K, double&& T, double&& r, double&& sig, double&& S, unsigned long&& NSIM, double&& D, int&& type);
    virtual ~Input() = default;

    // Operator Overloading
    Input& operator=(const Input& other);
    Input& operator=(Input&& other) noexcept;

    // Accessors and Mutators
    OptionData getOptionData() const;
    void setOptionData(double& K, double& T, double& r, double& sig, double& S, unsigned long& NSIM, double& D, int& type);

    // Utilities
    static void resetInputBuffer() ;

    // Template Method
    virtual void setStrike();
    virtual void setExpiry();
    virtual void setInterestRate();
    virtual void setVolatility();
    virtual void setSpot();
    virtual void setNSIM();
    virtual void setDividend();
    virtual void setType();
    virtual OptionData setOptionData() final;
};


#endif //MULTI_THREADED_MONTE_CARLO_SIMULATION_FOR_OPTION_PRICING_INPUT_HPP
