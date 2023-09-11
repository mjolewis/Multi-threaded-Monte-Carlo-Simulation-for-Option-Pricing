//
// Specifies the Random Engines that the systems supports for generating random numbers.
//
// Created by Michael Lewis on 9/10/23.
//

#include "EngineType.hpp"

/**
 * Overloaded equality operator. Two engines are said to be equal if their descriptions are the same.
 * @param other The description that represents another Engine
 * @return True if the two descriptions match. False otherwise.
 */
bool EngineType::operator==(const EngineType& other) const
{
    return this->getDesc() == other.getDesc();
}

/**
 * Assignment operator. Deeply copies the contents of another EngineType into this EngineType
 * @param other Another type of engine
 * @return This EngineType, whose members have been updated with the member data of the other engine
 */
EngineType& EngineType::operator=(const EngineType &other)
{
    if (this == &other) return *this;

    id = other.id;
    desc = other.desc;

    return *this;
}

/**
 * Utility function that allows clients to lookup EngineTypes by their description
 * @param desc The description of an engine
 * @return The type of engine that matches in incoming description
 */
EngineType EngineType::getEngineTypeFromString(const std::string& desc)
{
    if (desc == EngineType::MERSENNE_TWISTER.desc) return EngineType::MERSENNE_TWISTER;
    if (desc == EngineType::LAGGED_FIBONACCI.desc) return EngineType::LAGGED_FIBONACCI;
    if (desc == EngineType::LINEAR_CONGRUENTIAL.desc) return EngineType::LINEAR_CONGRUENTIAL;

    return EngineType::UNKNOWN;
}

/**
 * Utility function that allows clients to lookup EngineTypes by their id
 * @param id The id of an engine
 * @return The type of engine that matches the incoming id
 */
EngineType EngineType::getEngineById(unsigned int id)
{
    if (id == EngineType::MERSENNE_TWISTER.id) return EngineType::MERSENNE_TWISTER;
    if (id == EngineType::LAGGED_FIBONACCI.id) return EngineType::LAGGED_FIBONACCI;
    if (id == EngineType::LINEAR_CONGRUENTIAL.id) return EngineType::LINEAR_CONGRUENTIAL;

    return EngineType::UNKNOWN;
}
