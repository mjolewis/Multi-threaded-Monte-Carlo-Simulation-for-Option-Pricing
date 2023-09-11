//
// Specifies the Random Engines that the systems supports for generating random numbers.
//
// Created by Michael Lewis on 9/10/23.
//

#ifndef MULTI_THREADED_MONTE_CARLO_SIMULATION_FOR_OPTION_PRICING_ENGINETYPE_HPP
#define MULTI_THREADED_MONTE_CARLO_SIMULATION_FOR_OPTION_PRICING_ENGINETYPE_HPP

#include <string>
#include <utility>

class EngineType
{
private:
    int id;
    std::string desc;
    EngineType(int _id, std::string _desc) : id{_id}, desc{std::move(_desc)} {}

public:
    // Synthetic Enum declarations
    static const EngineType MERSENNE_TWISTER;
    static const EngineType LAGGED_FIBONACCI;
    static const EngineType LINEAR_CONGRUENTIAL;
    static const EngineType UNKNOWN;

    // Operator Overloads
    EngineType& operator=(const EngineType& other);
    bool operator==(const EngineType& other) const;

    static EngineType getEngineTypeFromString(const std::string& _EngineType);
    static EngineType getEngineById(unsigned int id);
    inline std::string getDesc() const {return this->desc;}
};

// Enum definitions
inline const EngineType EngineType::MERSENNE_TWISTER = EngineType{1, "Mersenne Twister"};
inline const EngineType EngineType::LAGGED_FIBONACCI = EngineType{2, "Lagged Fibonacci"};
inline const EngineType EngineType::LINEAR_CONGRUENTIAL = EngineType{3, "Linear Congruential"};
inline const EngineType EngineType::UNKNOWN = EngineType{4, "Unknown"};


#endif //MULTI_THREADED_MONTE_CARLO_SIMULATION_FOR_OPTION_PRICING_ENGINETYPE_HPP
