#pragma once
#ifndef EA_HEADERS_STRATEGIES_H_
#define EA_HEADERS_STRATEGIES_H_

#include <cmath>

#include "../publicfunction.h"
#include "../population.h"
#include "../executivevariables.h"
#include "localvariables.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		class Strategies {
		public:
			Strategies();
			virtual ~Strategies();
			double* DE_Rand(Population&, size_t, unsigned number_of_vector_differences = 1);
			double* DE_Best(Population&, unsigned, unsigned, unsigned number_of_vector_differences = 1);
			double* DE_Cur_To_Rand(Population&, unsigned, unsigned number_of_vector_differences = 1);
			double* DE_Cur_To_Best(Population&, unsigned, unsigned, unsigned number_of_vector_differences = 1);
			double* DE_Cur_To_PBest(Population&, unsigned, unsigned*, unsigned number_of_vector_differences = 1);
			void SetArchive(Population*);
			void SetExecutiveVariables(ExecutiveVariables&);
			void SetLocalVariables(LocalVariables&);
		protected:
			bool IsOutBound(double, unsigned);
			void OutBoundHandler(Population&, unsigned, double*, unsigned);
			std::vector<std::pair<unsigned, unsigned>> VectorDifferencesPair(unsigned*, unsigned);
			Population* archive_ = nullptr;
			bool archive_is_set_ = false;

			static inline void CheckArchiveIsSet(size_t archive_size, bool is_set) {
				if (archive_size > 0) {
					if (!is_set) {
						std::cout << "Before using DE/Current-to-pBest, Archive must be set if setting of Archive size in config file is larger than 0." << std::endl;
						exit(0);
					}
				}
			}

			static inline double* CreateTrailIndividual(const size_t dim) {
				if (dim == 0) {
					std::cout << "Unable to malloc trail_individual when DE_Rand(). Dim value:" << dim << std::endl;
					exit(0);
				}
				double* trail_individual = (double*)malloc(sizeof(double) * dim);
				if (trail_individual == nullptr || dim == 0) {
					std::cout << "Unable to malloc trail_individual when DE_Rand(). Dim value:" << dim << std::endl;
					exit(0);
				}
				return trail_individual;
			}
		private:
			ExecutiveVariables* ev_ = nullptr;
			LocalVariables* lv_ = nullptr;
			void ExecutiveVariablesCheck();
		};
	} // namespace differentialevolution
} // namespace evolutionalgorithm

#endif // EA_HEADERS_STRATEGIES_H_