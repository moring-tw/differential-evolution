#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_MEMORIZE_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_MEMORIZE_H_

#include <iostream>

#include "localvariables.h"
#include "../population.h"
#include "variants/de.h"
#include "behavior.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		class Memorize : public Behavior
		{
		public:
			Memorize();
			virtual ~Memorize();
			//void SetLocalVariables(LocalVariables*);
			void MallocNP_Rank();
			void InitialNP_Rank();
			void SortNP_Rank();
			void InitialDE_Population();
			void InitialDE_NextGeneration();
			void InitialDE_Fitness();
			void InitialDE_Strategy();
			void MallocSaDE_StrategiesSelection();
			//void MallocSaDE_MemoryCR(const size_t);
			void InitialSaDE_StrategiesSelection();
			//void InitialSaDE_MemoryCR(const size_t);
			void InitialSHADE_Archive();

			void RecycleNP_Rank();
			void RecycleDE_Fitness();
			void RecycleSaDE_StrategiesSelection();
			
		protected:
			static inline void VariableNotInitialedError(std::string failed_var, std::string var_name) {
				std::cout << "Failed to initial/malloc " << failed_var << ", due to " << var_name << " haven't been initialed." << std::endl;
				exit(0);
			}
		private:
			//LocalVariables* lv_ = nullptr;
		};
	}
}

#endif // !EA_HEADERS_DIFFERENTIAL_EVOLUTION_MEMORIZE_H_
