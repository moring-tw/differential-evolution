#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_EVOLUTION_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_EVOLUTION_H_

#include "behavior.h"

//
// Check parameter then execute.
//
namespace evolutionalgorithm {
	namespace differentialevolution {
		class Evolve :public Behavior
		{
		public:
			Evolve();
			~Evolve();

			void BeforeEvolveDE_RandomP();
			void EvolveDE();
			void BeforeEvolveSaDE_StrategiesSelection();
			void BeforeEvolveSaDE_CR_Selection(const size_t);

			void BeforeEvolveSHADE_CR_Selection();
			void BeforeEvolveSHADE_F_Selection();
		protected:
			static inline void EvolvingError(std::string var_name) {
				std::cout << "Failed to evolve. Please check " << var_name << " has a valid value." << std::endl;
				exit(0);
			}
		private:

		};
	} // namespace evolutionalgorithm
} // namespace differentialevolution


#endif // !EA_HEADERS_DIFFERNETIAL_EVOLUTION_EVOLUTION_H_