#pragma once
#ifndef EA_HEADERS_PUBLICFUNCTION_H_
#define EA_HEADERS_PUBLICFUNCTION_H_

#include <sys/timeb.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <map>
#include <random>

namespace evolutionalgorithm {
	class PublicFunction
	{
	public:
		PublicFunction();
		virtual ~PublicFunction();
		//convert enum class value to its underlying type
		template <typename UT>
		static constexpr typename std::underlying_type<UT>::type to_underlying(UT ut) noexcept {
			return static_cast<typename std::underlying_type<UT>::type>(ut);
		}

		static double RandomDouble(double, double);
		static int RandomInt(int, int);
		static unsigned* ShufflePopulation(size_t);
		static unsigned* ShufflePopulation(size_t, size_t, unsigned);
		static void SortPopulation(double*, unsigned*, size_t, size_t left = 0);
		static void SortIndividual(double*, unsigned*, size_t, size_t);
		static double NormalDistributionRandom(double, double);
		static double CauchyDistributionRandom(double, double);
		static double WeightedArithmeticMean(std::vector<double>&, std::vector<double>&);
		static double WeightedLenmerMean(std::vector<double>&, std::vector<double>&);
		static double CalculateStandardDeviation(double*, double, unsigned);
		static double RoundToDecimalPlace(double, unsigned);

	protected:
		static std::random_device rd_;
		static std::mt19937 generator_;
	private:


	};
}//namespace evolutionalgorithm


#endif // EA_HEADERS_PUBLICFUNCTION_H_