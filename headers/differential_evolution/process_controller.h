#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_PROCESS_CONTROLLER_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_PROCESS_CONTROLLER_H_

#include <iostream>

#include "../../benchmark/inc/Benchmarks.h"
#include "../executivevariables.h"
#include "../publicfunction.h"
#include "strategies.h"
#include "memorize.h"
#include "evolve.h"
#include "select.h"
#include "parameter_control.h"
#include "localvariables.h"
#include "variants/de.h"

//
// Controls the algorithm flow of which features should be executed
//
namespace evolutionalgorithm {
	namespace differentialevolution {
		class ProcessController {
		public:
			ProcessController();
			virtual ~ProcessController();
			void NextRun();
			void Execute();
			void SetExecutiveVariables(ExecutiveVariables&);
			void SetBenchmark(Benchmarks*);
			double GetBest();
		protected:

		private:
			void SetBehaviors(Behavior&);
			void SetVariants(Basic&);
			void InitialVariants(Basic&);
			void BeforeInitial();
			void Initial();
			void AfterInitial();
			void BeforeEvolution();
			void Evolution();
			void AfterEvolution();
			void BeforeSelection();
			void Selection();
			void AfterSelection();
			void NextGen();
			bool ReachStopCriterion();
			void RecycleMemory();
			bool is_initialed_ = false;
			bool debug_ = false;
			
			// behaviors
			Memorize memory_;
			ParameterControl parameter_control_;
			Evolve evolve_;
			Select select_;
			// local variables
			LocalVariables lv_;
			// strategies
			Strategies ss_;
			// variants
			DE de_;
			SaDE sade_;
			SHADE shade_;
			Random random_;

			static inline void parameter_control_error(std::string which_parameter) {
				std::cout << "Cannot control parameter "<< which_parameter<<" without specified method."<<std::endl;
				exit(0);
			}
		};
	} // namespace differentialevolution
} // namespace evolutionalgorithm
#endif // !EA_HEADERS_DIFFERENTIAL_EVOLUTION_PROCESS_CONTROLLER_H_
