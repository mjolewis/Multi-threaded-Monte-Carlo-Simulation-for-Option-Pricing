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
	BOOST_PARAMETER_KEYWORD(Tag, dividend)
	BOOST_PARAMETER_KEYWORD(Tag, optionType)
}


// Encapsulate all data in one place
struct OptionData
{ // Option data + behaviour

	double K;
	double T;
	double r;
	double sig;

	// Extra data 
	double D;		// dividend
	
	int type;		// 1 == call, -1 == put

	explicit constexpr OptionData(double strike, double expiration, double interestRate,
									double volatility, double dividend, int PC)
		: K(strike), T(expiration), r(interestRate), sig(volatility), D(dividend), type(PC)
	{}

	template <typename ArgPack>
	explicit OptionData(const ArgPack& args)
	{
		K = args[OptionParams::strike];
		T = args[OptionParams::expiration];
		r = args[OptionParams::interestRate];
		sig = args[OptionParams::volatility];
		D = args[OptionParams::dividend];
		type = args[OptionParams::optionType];

		std::cout << "K " << K << ", T " << T << ",r " << r << std::endl;
		std::cout << "vol " << sig << ", div " << D << ",type " << type << std::endl;
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