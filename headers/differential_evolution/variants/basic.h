#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_BASIC_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_BASIC_H_

#include <math.h>

#include <cmath>
#include <vector>

#include "../localvariables.h"
#include "../strategies.h"
#include "../../corematerial.h"
#include "../../../benchmark/inc/Benchmarks.h"

namespace evolutionalgorithm {
	namespace differentialevolution {

		class Basic
		{
		public:
			Basic();
			~Basic();
			void SetLocalVariables(LocalVariables*);
			void SetStrategies(Strategies*);
			virtual void NextRun();

			//
			// Every time using nextGen() means no matter the DE variants had been executed or not, it handles some variables which won't influence others DE variants.
			// Like delta_fitness_, shade_success_CR_ and shade_success_F_ etc., ONLY used by SHADE. But something like population, next_generation_ etc., which are widely used by DE variants
			// are not acceptable to be modified by NextGen().
			//
			virtual void NextGen();
		protected:
			LocalVariables* lv_ = nullptr;
			Benchmarks* fp_ = nullptr;
			Strategies* ss_ = nullptr;
			void CheckLV();
			void CheckFP();
			void StrategiesExecuter(size_t, corematerial::MutantAndCrossover, size_t number_of_vector_differences = 1);
			size_t FindStrategyIndex(const corematerial::MutantAndCrossover);
		private:
			static inline void UnknownStrategyError(const corematerial::MutantAndCrossover strategy) {
				std::cout << "Unknown Strategy: " << static_cast<size_t>(strategy) << std::endl;
				exit(0);
			}
		};
	}
}

#endif // !EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_BASIC_H_
