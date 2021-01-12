#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_DE_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_DE_H_

#include "basic.h"
#include "../behavior.h"
#include "../localvariables.h"
#include "../../publicfunction.h"

namespace evolutionalgorithm {
	namespace differentialevolution{
		class DE : public Basic
		{
		public:
			DE();
			~DE();
			void MallocNP_Rank();
			void DemallocNP_Rank();
			void InitialNP_Rank();
			void InitialPopulation();
			void InitialNextGeneration();
			void InitialFitness();
			void DemallocFitness();
			void InitialUseStrategy();
			void InitialUseCR();
			void InitialUseF();
			void InitialUseK();
			void InitialUseP();
			void SortNP_Rank();
			void Evolution();
			void Selection();
			void AfterSelection();
			void NextGen();
		private:
		};
	} // namespace evolutionalgorithm
} // namespace differentialevolution
#endif // !EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_DE_H_
