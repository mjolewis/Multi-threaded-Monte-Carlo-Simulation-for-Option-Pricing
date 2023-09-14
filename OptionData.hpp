// OptionData.hpp
//
// Encapsulate option data.
//
// (C) Datasim Education BV 2008-2016

#ifndef OptionData_HPP
#define OptionData_HPP

#include <algorithm> // for max()
#include <iostream>

#include <boost/parameter.hpp>

namespace OptionParams
{
	BOOST_PARAMETER_KEYWORD(Tag, strike)
	BOOST_PARAMETER_KEYWORD(Tag, expiration)
	BOOST_PARAMETER_KEYWORD(Tag, interestRate)
	BOOST_PARAMETER_KEYWORD(Tag, volatility)
    BOOST_PARAMETER_KEYWORD(Tag, spotPrice)
    BOOST_PARAMETER_KEYWORD(Tag, NSIM)
	BOOST_PARAMETER_KEYWORD(Tag, dividend)
	BOOST_PARAMETER_KEYWORD(Tag, optionType)
}


// Encapsulate all data in one place
struct OptionData
{ // Option data + behaviour

	double K;              // Strike price
	double T;              // Time to expiry in years
	double r;              // Interest rate
	double sig;            // Volatility
    double S;              // Spot price

	// Extra data
    unsigned long NSIM;	   // Number of simulations
	double D;		// dividend
	int type;		// 1 == call, -1 == put

	explicit constexpr OptionData(double strike, double expiration, double interestRate, double volatility,
                                  double spotPrice, unsigned long NSIM, double dividend, int PC)
		: K{strike}, T{expiration}, r{interestRate}, sig{volatility}, S{spotPrice}, NSIM{NSIM}, D{dividend}, type{PC}
	{

    }

	template <typename ArgPack>
	explicit OptionData(const ArgPack& args)
	{
		K = args[OptionParams::strike];
		T = args[OptionParams::expiration];
		r = args[OptionParams::interestRate];
		sig = args[OptionParams::volatility];
        S = args[OptionParams::spotPrice];
        NSIM = args[OptionParams::NSIM];
		D = args[OptionParams::dividend];
		type = args[OptionParams::optionType];

		std::cout << "K=" << K << ", T=" << T << ", r=" << r << std::endl;
		std::cout << "vol=" << sig << "S=" << S << "NSIM=" << NSIM << std::endl;
        std::cout << ", div=" << D << ",type=" << type << std::endl;
	}

	double myPayOffFunction(double S) const
	{ // Payoff function

		if (type == 1)
		{
            // Call
			return std::max(S - K, 0.0);
		}
		else
		{
            // Put
			return std::max (K - S, 0.0);
		}
	}
};


#endif