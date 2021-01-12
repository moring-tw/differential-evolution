#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_LOCAL_VARIABLES_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_LOCAL_VARIABLES_H_

#include "../population.h"
#include "../../benchmark/inc/Benchmarks.h"
#include "../executivevariables.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		class LocalVariables
		{
		public:
			LocalVariables();
			~LocalVariables();
			void NextRun();

		private:
			// widely used
			Population population_;
			Population next_generation_;
			Benchmarks* fp_ = nullptr;
			ExecutiveVariables ev_;
			double* fitness_ = nullptr;
			double now_best_ = DBL_MAX;
			size_t now_best_individual_ = SIZE_MAX;
			unsigned now_ffe_ = 0;
			unsigned now_gen_ = 0;
			size_t* np_rank = nullptr;
			std::map<size_t, double*> wait_free_map_of_individual_dimension_;
			// END widely used

			bool is_initialed_ = false;

			// SaDE
			size_t** sade_success_memory_, * sade_success_memory_sum_, ** sade_fail_memory_, * sade_fail_memory_sum_;
			double* strategies_probability_, * sade_CRm_;
			std::vector<double>*** sade_memory_CR_;
			// END SaDE

			// SHADE
			Population archive_;
			size_t shade_insert_h_ = 0, shade_archive_now_size_ = 0;
			size_t * shade_ri_ = nullptr;
			double* shade_memory_CR_, * shade_memory_F_; // fixed H
			std::vector<double> delta_fitness_; // clear each generation
			std::vector<double> shade_success_CR_, shade_success_F_; // clear each generation
			// END SHADE


			friend class Random;
			friend class DE;
			friend class SaDE;
			friend class SHADE;
			friend class ProcessController;
			friend class Memorize;
			friend class Evolve;
			friend class Select;
			friend class Basic;
			friend class ParameterControl;
			friend class Strategies;
		};
	}
}



#endif // !EA_HEADERS_DIFFERENTIAL_EVOLUTION_LOCAL_VARIABLES_H_
