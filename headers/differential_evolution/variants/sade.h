#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_SADE_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_VATIANTS_SADE_H_
#include "basic.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		class SaDE : public Basic
		{
		public:
			SaDE();
			virtual ~SaDE();
			void NextRun();
			void MallocSaDE_StrategiesSelection();
			void DemallocSaDE_StrategiesSelection();
			void MallocSaDE_MemoryCR(const size_t);
			void DemallocSaDE_MemoryCR(const size_t);
			void InitialSaDE_StrategiesSelection();
			void InitialSaDE_MemoryCR(const size_t);

			void CalculateSaDE_StrategiesProbability();
			void SelectSaDE_Strategies();
			void CalculateSaDE_CRm(const size_t);
			void SelectSaDE_CR();
			
			void BeforeSelectionSaDE_StrategiesSelection();
			void SuccessSelectionSaDE_StrategiesSelection();
			void FailSelectionSaDE_StrategiesSelection();
			void SuccessSelectionSaDE_MemoryCR();
		private:
			size_t now_learn_ = 0;
			static inline void UnknowStrategyError(const corematerial::MutantAndCrossover strategy) {
				std::cout << "Unknown Strategy: "<< static_cast<size_t>(strategy)  << std::endl;
				exit(0);
			}
		};
	} // namesapce differentialevolution
} // namespace evolutionalgorithm

#endif // !EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_SADE_H_
