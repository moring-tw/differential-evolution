#include "../../headers/differential_evolution/memorize.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		Memorize::Memorize()
		{
		}

		Memorize::~Memorize()
		{
		}

		/*void Memorize::SetLocalVariables(LocalVariables* lv) {
			if(lv == nullptr){
				std::cout << "Memorize doesn't accept nullptr of LocalVariables object pointer." << std::endl;
				exit(0);
			}
			Memorize::lv_ = lv;
		}*/

		void Memorize::MallocNP_Rank() {
			Memorize::CheckLV();
			if (Memorize::lv_->ev_.GetDE_NP() != 0) {
				de_->MallocNP_Rank();
			} else Memorize::VariableNotInitialedError("np_rank_", "np_");
		}

		void Memorize::InitialNP_Rank() {
			Memorize::CheckLV();
			if (Memorize::lv_->ev_.GetDE_NP() != 0) {
				de_->InitialNP_Rank();
			} else Memorize::VariableNotInitialedError("np_rank_", "np_");
		}

		void Memorize::SortNP_Rank() {
			Memorize::CheckLV();
			if (Memorize::lv_->fitness_ != nullptr) {
				if (Memorize::lv_->population_ != nullptr) {
					de_->SortNP_Rank();
				}
			}
		}

		void Memorize::InitialDE_Population() {
			Memorize::CheckLV();
			if (Memorize::lv_->ev_.GetDE_NP() != 0) {
				if (Memorize::lv_->ev_.GetDE_Dim() != 0) {
					if (Memorize::lv_->ev_.GetBoundMin() != nullptr) {
						if (Memorize::lv_->ev_.GetBoundMax() != nullptr) {
							de_->InitialPopulation();
						} else Memorize::VariableNotInitialedError("population_", "bound_max_");
					} else Memorize::VariableNotInitialedError("population_", "bound_min_");
				} else Memorize::VariableNotInitialedError("population_", "dim_");
			} else Memorize::VariableNotInitialedError("population_", "np_");
		}

		void Memorize::InitialDE_NextGeneration() {
			Memorize::CheckLV();
			if (Memorize::lv_->ev_.GetDE_NextGenNP() != 0) {
				de_->InitialNextGeneration();
			} else Memorize::VariableNotInitialedError("next_generation_", "np_");
		}

		void Memorize::InitialDE_Fitness() {
			Memorize::CheckLV();
			if (Memorize::lv_->ev_.GetDE_NP() != 0 && Memorize::lv_->ev_.GetDE_NP() != SIZE_MAX) {
				if (Memorize::lv_->fp_ != nullptr) {
					de_->InitialFitness();
				} else Memorize::VariableNotInitialedError("next_generation_", "fp_");
			} else Memorize::VariableNotInitialedError("next_generation_", "np_");
		}

		void Memorize::InitialDE_Strategy() {
			Memorize::CheckLV();
			if (Memorize::lv_->ev_.GetDE_NP() != 0) {
				Behavior::de_->InitialUseStrategy();
			} else Memorize::VariableNotInitialedError("use_strategy_", "np_");
		}

		void Memorize::MallocSaDE_StrategiesSelection() {
			Memorize::CheckLV();
			if (Memorize::lv_->ev_.GetSaDE_LP() > 0) {
				Behavior::sade_->MallocSaDE_StrategiesSelection();
			} else Memorize::VariableNotInitialedError("sade_success_memory_", "sade_LP_");
		}

		void Memorize::InitialSaDE_StrategiesSelection() {
			Memorize::CheckLV();
			Behavior::sade_->InitialSaDE_StrategiesSelection();
		}

		void Memorize::InitialSHADE_Archive() {
			Memorize::CheckLV();
			if (Memorize::lv_->ev_.GetArchiveSize() > 0) {
				Behavior::shade_->InitialSHADE_Archive();
			} else Memorize::VariableNotInitialedError("archive_", "archive_size_");
		}

		void Memorize::RecycleNP_Rank() {
			Behavior::de_->DemallocNP_Rank();
		}

		void Memorize::RecycleDE_Fitness() {
			Behavior::de_->DemallocFitness();
		}

		void Memorize::RecycleSaDE_StrategiesSelection() {
			Behavior::sade_->DemallocSaDE_StrategiesSelection();
		}
	}
}