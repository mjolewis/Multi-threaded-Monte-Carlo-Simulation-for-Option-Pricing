//
// Exposes multiple APIs to allow either users or programmatic clients to customize the option data that will
// later be used by the Pricer
//
// Created by Michael Lewis on 9/11/23.
//

#include <iostream>
#include <exception>
#include <utility>

#include "Input.hpp"
#include "OptionData.hpp"

/**
 * Default ctor that creates OptionData with default values.
 * Parameter ordering: K, T, r, sig, S, NSIM, D, type
 */
Input::Input() : optionData{100, 0.25, 0.1, 0.1, 110, 100'000, 0, 1}
{
}

/**
 * Copy ctor. Deeply copies the OptionData from the other Input to this Input's OptionData
 * @param other Another Input object whose OptionData will be deeply copied
 */
Input::Input(const Input& other) : optionData{other.optionData.K, other.optionData.T, other.optionData.r,
                                              other.optionData.sig, other.optionData.S, other.optionData.NSIM,
                                              other.optionData.D, other.optionData.type}
{

}

/**
 * Move ctor. Moves the OptionData from the other Input to this Input's OptionData
 * @param other Another Input object whose OptionData will be moved
 */
Input::Input(Input&& other) noexcept : optionData{std::move(other.optionData.K), std::move(other.optionData.T),
                                                  std::move(other.optionData.r), std::move(other.optionData.sig),
                                                  std::move(other.optionData.S), std::move(other.optionData.NSIM),
                                                  std::move(other.optionData.D), std::move(other.optionData.type)}
{

}

/**
 * Overloaded ctor.
 * @param optionData OptionData object whose data members will be assigned to the members of this OptionData object
 */
Input::Input(const OptionData& optionData) : optionData{optionData.K, optionData.T, optionData.r,
                                                        optionData.sig, optionData.S, optionData.NSIM,
                                                        optionData.D, optionData.type}
{

}

/**
 * Overloaded ctor for LValues
 * @param K Strike
 * @param T Expiry
 * @param r Interest rate
 * @param sig Volatility
 * @param S Spot price
 * @param NSIM Number of simulations
 * @param D Dividend
 * @param type Option type 1 for Call and -1 for Put
 */
Input::Input(double &K, double &T, double &r, double &sig, double &S, unsigned long &NSIM, double &D, int &type)
    : optionData{K, T, r, sig, S, NSIM, D, type}
{

}

/**
 * Overloaded ctor for RValues. These values are trivally copyable, so move semantics is unnecessary.
 * @param K Strike
 * @param T Expiry
 * @param r Interest rate
 * @param sig Volatility
 * @param S Spot price
 * @param NSIM Number of simulations
 * @param D Dividend
 * @param type Option type 1 for Call and -1 for Put
 */
Input::Input(double &&K, double &&T, double &&r, double &&sig, double &&S, unsigned long &&NSIM, double &&D, int &&type)
    : optionData{K, T, r, sig, S, NSIM, D, type}
{

}

/**
 * Copy assignment
 * @param other An Input object whose OptionData will be deeply copied into this Input's OptionData
 * @return Input
 */
Input& Input::operator=(const Input &other)
{
    // Avoid self assignment
    if (this == &other) return *this;

    optionData.K = other.optionData.K;
    optionData.T = other.optionData.T;
    optionData.r = other.optionData.r,
    optionData.sig = other.optionData.sig,
    optionData.S = other.optionData.S,
    optionData.NSIM = other.optionData.NSIM,
    optionData.D = other.optionData.D,
    optionData.type = other.optionData.type;

    return *this;
}

/**
 * Move assignment.
 * @param other An Input object whose OptionData will be moved into this Input's OptionData
 * @return Input
 */
Input& Input::operator=(Input&& other) noexcept
{
    // Avoid self assignment
    if (this == &other) return *this;

    optionData.K = std::move(other.optionData.K);
    optionData.T = std::move(other.optionData.T);
    optionData.r = std::move(other.optionData.r),
    optionData.sig = std::move(other.optionData.sig),
    optionData.S = std::move(other.optionData.S),
    optionData.NSIM = std::move(other.optionData.NSIM),
    optionData.D = std::move(other.optionData.D),
    optionData.type = std::move(other.optionData.type);

    return *this;
}

/**
 * Accessor for this Inputs OptionData
 * @return OptionData
 */
OptionData Input::getOptionData() const
{
    return optionData;
}

/**
 * Modifies the OptionData values
 * @param K Strike
 * @param T Expiry
 * @param r Interest rate
 * @param sig Volatility
 * @param S Spot price
 * @param NSIM Number of simulations
 * @param D Dividend
 * @param type Option type 1 for Call and -1 for Put
 */
void Input::setOptionData(double &K, double &T, double &r, double &sig, double &S,
                          unsigned long &NSIM, double &D, int &type)
{
    optionData.K = K;
    optionData.T = T;
    optionData.r = r;
    optionData.sig = sig;
    optionData.S = S;
    optionData.NSIM = NSIM;
    optionData.D = D;
    optionData.type = type;
}

/**
 * Reset the fail bit and clear the buffer when user provided input can't be converted to the correct type
 */
void Input::resetInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * Exposes a console interface for the user to enter Strike
 */
void Input::setStrike()
{
    try
    {
        optionData.K = 0;
        while(std::cin.fail() || optionData.K <= 0)
        {
            resetInputBuffer();
            std::cout << "Enter Strike Price: ";
            std::cin >> optionData.K;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Unable to set Strike - " << e.what();
    }
}

/**
 * Exposes a console interface for the user to enter Expiry
 */
void Input::setExpiry()
{
    try
    {
        optionData.T = -1;
        while (std::cin.fail() || optionData.T < 0)
        {
            resetInputBuffer();
            std::cout << "Enter Expiry: ";
            std::cin >> optionData.T;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to set Expiry - " << e.what();
    }
}

/**
 * Exposes a console interface for the user to enter Interest Rate
 */
void Input::setInterestRate()
{
    try
    {
        optionData.r = -1;
        while (std::cin.fail() || optionData.r < 0)
        {
            resetInputBuffer();
            std::cout << "Enter Interest Rate: ";
            std::cin >> optionData.r;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Unable to set Interest Rate - " << e.what();
    }
}

/**
 * Exposes a console interface for the user to enter Volatility
 */
void Input::setVolatility()
{
    try
    {
        optionData.sig = -1;
        while (std::cin.fail() || optionData.sig < 0)
        {
            resetInputBuffer();
            std::cout << "Enter Volatility: ";
            std::cin >> optionData.sig;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Unable to set Volatility - " << e.what();
    }
}

/**
 * Exposes a console interface for the user to enter Spot
 */
void Input::setSpot()
{
    try
    {
        optionData.S = -1;
        while (std::cin.fail() || optionData.S < 0)
        {
            resetInputBuffer();
            std::cout << "Enter Spot Price: ";
            std::cin >> optionData.S;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Unable to set Spot Price - " << e.what();
    }
}

/**
 * Exposes a console interface for the user to enter NSIM
 */
void Input::setNSIM()
{
    try
    {
        optionData.NSIM = 0;
        while (std::cin.fail() || optionData.NSIM <= 0)
        {
            resetInputBuffer();
            std::cout << "Enter NSIM: ";
            std::cin >> optionData.NSIM;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Unable to set NSIM - " << e.what();
    }
}

/**
 * Exposes a console interface for the user to enter Dividend
 */
void Input::setDividend()
{
    try
    {
        optionData.D = -1;
        while (std::cin.fail() || optionData.D < 0)
        {
            resetInputBuffer();
            std::cout << "Enter Dividend: ";
            std::cin >> optionData.D;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Unable to set Dividend - " << e.what();
    }
}

/**
 * Exposes a console interface for the user to enter Option Type
 */
void Input::setType()
{
    try
    {
        optionData.type = 0;
        while (std::cin.fail() || (optionData.type != -1 && optionData.type != 1))
        {
            resetInputBuffer();
            std::cout << "Enter Type (Put = -1 and Call = 1): ";
            std::cin >> optionData.type;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Unable to set Option Type - " << e.what();
    }
}

/**
 * A Template Method that provides a console interface so users can provide the OptionData. This function
 * is final to prevent any derived classes from overriding the control flow. However, derived class
 * are allowed to customize the implementation details of each option data setter.
 * @return OptionData
 */
OptionData Input::setOptionData()
{
    setStrike();
    setExpiry();
    setInterestRate();
    setVolatility();
    setSpot();
    setNSIM();
    setDividend();
    setType();
}