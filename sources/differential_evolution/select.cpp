#include "../../headers/differential_evolution/select.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		Select::Select()
		{
		}

		Select::~Select()
		{
		}

		void Select::SelectDE() {
			if (Behavior::lv_->ev_.GetDE_NP() == Behavior::lv_->ev_.GetDE_NextGenNP()) {
				Behavior::de_->Selection();
			} else {
				std::cout << "DE selection cannot execute until np equal to next generation np."<<std::endl;
				exit(0);
			}
		}

		void Select::AfterSelectDE() {
			Behavior::de_->AfterSelection();
		}

		void Select::BeforeSelectSaDE_StrategiesSelection() {
			if (Behavior::lv_->ev_.GetSaDE_LP() > 0) {
				if (Behavior::lv_->ev_.GetDE_NumOfStrategies() > 1) {
					if (Behavior::lv_->sade_success_memory_sum_ != nullptr && Behavior::lv_->sade_success_memory_ != nullptr 
						&& Behavior::lv_->sade_fail_memory_sum_ != nullptr && Behavior::lv_->sade_fail_memory_ != nullptr) {
						Behavior::sade_->BeforeSelectionSaDE_StrategiesSelection();
					} else Select::SelectionError("SaDE strategies selection", "sade_success_memory_sum_, sade_success_memory_, sade_fail_memory_sum_ or sade_fail_memory_");
				} else Select::SelectionError("SaDE strategies selection", "num of strategies");
			} else Select::SelectionError("SaDE strategies selection", "LP(Learning Period)");
		}

		void Select::AfterSelectSaDE_SuccessStrategiesSelection() {
			if (Behavior::lv_->ev_.GetDE_NextGenNP() > 0) {
				Behavior::sade_->SuccessSelectionSaDE_StrategiesSelection();
			} else Select::SelectionError("SaDE success strategies selection", "next gen NP");
		}

		void Select::AfterSelectSaDE_FailStrategiesSelection() {
			if (Behavior::lv_->ev_.GetDE_NextGenNP() > 0) {
				Behavior::sade_->FailSelectionSaDE_StrategiesSelection();
			} else Select::SelectionError("SaDE fail strategies selection", "next gen NP");
		}

		void Select::AfterSelectSaDE_SuccessMemoryCR() {
			if (Behavior::lv_->ev_.GetDE_NextGenNP() > 0) {
				Behavior::sade_->SuccessSelectionSaDE_MemoryCR();
			} else Select::SelectionError("SaDE success memory CR", "next gen NP");
		}

		void Select::AfterSelectSHADE_SuccessMemoryCR() {
			if (Behavior::lv_->ev_.GetDE_NextGenNP() > 0) {
				if (Behavior::lv_->ev_.GetSHADE_H() > 0) {
					Behavior::shade_->SuccessSelectionSHADE_MemoryCR();
				} else Select::SelectionError("SHADE success memory CR", "memery H");
			} else Select::SelectionError("SHADE success memory CR", "next gen NP");
		}

		void Select::AfterSelectSHADE_SuccessMemoryF() {
			if (Behavior::lv_->ev_.GetDE_NextGenNP() > 0) {
				if (Behavior::lv_->ev_.GetSHADE_H() > 0) {
					Behavior::shade_->SuccessSelectionSHADE_MemoryF();
				} else Select::SelectionError("SHADE success memory F", "memery H");
			} else Select::SelectionError("SHADE success memory F", "next gen NP");
		}

		void Select::AfterSelectSHADE_SuccessArchive() {
			if (Behavior::lv_->ev_.GetDE_NextGenNP() > 0) {
				if (Behavior::lv_->ev_.GetArchiveSize() > 0) {
					Behavior::shade_->SuccessSelectionSHADE_Archive();
				} else Select::SelectionError("SHADE success Archive", "archive size");
			} else Select::SelectionError("SHADE success Archive", "next gen NP");
		}
	}
}