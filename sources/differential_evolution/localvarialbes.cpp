#include "../../headers/differential_evolution/localvariables.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		LocalVariables::LocalVariables()
		{
		}

		LocalVariables::~LocalVariables()
		{
		}

		void LocalVariables::NextRun() {
			LocalVariables::now_best_ = DBL_MAX;
			LocalVariables::now_best_individual_ = SIZE_MAX;
			LocalVariables::now_ffe_ = 0;
			LocalVariables::now_gen_ = 0;
		}
	}

}