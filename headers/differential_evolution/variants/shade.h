#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_SHADE_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_SHADE_H_

#include <vector>

#include "basic.h"
namespace evolutionalgorithm{
	namespace differentialevolution {
		class SHADE : public Basic {
		public:
			SHADE();
			virtual ~SHADE();
			void NextRun();
			//void InitialSHADE_Archive();
			void MallocSHADE_MemoryCR();
			//void DemallocSHADE_MemoryCR();
			void MallocSHADE_MemoryF();
			//void DemallocSHADE_MemoryF();
			void InitialSHADE_MemoryCR();
			void InitialSHADE_MemoryF();
			void InitialSHADE_Archive();
			void SelectSHADE_CR();
			void SelectSHADE_F();

			/*void BeforeSelectionSHADE_MemoryCR();
			void BeforeSelectionSHADE_MemoryF();*/
			//void BeforeSelectionSHADE_DeltaFitness(); // calculates and records individuals delta_fitness_.

			void SuccessSelectionSHADE_MemoryCR();
			void SuccessSelectionSHADE_MemoryF();
			void SuccessSelectionSHADE_Archive();
			
			/*void AfterSelectionSHADE_MemoryCR();
			void AfterSelectionSHADE_MemoryF();*/
			void NextGen();
			void RecycleMemory();
		protected:

		private:
			void CopyFitnessArray();
			void RandomRi();
			void CalculateSuccessDeltaFitness();
			static inline double ProduceCR(double mean) {
				double cr = PublicFunction::NormalDistributionRandom(mean, 0.1);
				if (cr > 1) cr = 1;
				else if (cr < 0) cr = 0;
				return cr;
			}

			static inline double ProduceF(double mean) {
				double f = PublicFunction::CauchyDistributionRandom(mean, 0.1);
				if (f > 1) f = 1;
				while (f <= 0) f = PublicFunction::CauchyDistributionRandom(mean, 0.1);
				return f;
			}


			double* copied_fitness_ = nullptr;
			size_t prev_np_ = 0, prev_next_gen_np_ = 0;

			bool shade_insert_H_plus_1_ = false;
			bool shade_is_fitness_copied_ = false;
			bool shade_is_ri_produced_ = false;
			bool shade_is_delta_fitness_calculated_ = false;
		};
	} // namespace differentialevolution
} // namespace evolutionalgorithm
#endif // !EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_SHADE_H_
