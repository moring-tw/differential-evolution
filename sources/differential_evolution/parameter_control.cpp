#include "../../headers/differential_evolution/parameter_control.h"


namespace evolutionalgorithm {
	namespace differentialevolution {
		ParameterControl::ParameterControl() {

		}
		ParameterControl::~ParameterControl() {

		}
		void ParameterControl::InitialDE_CR() {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetDE_NP() != 0) {
				Behavior::de_->InitialUseCR();
			} else ParameterControl::ParameterControlNotInitialedError("use_CR_", "np_");
		}

		void ParameterControl::InitialDE_F() {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetDE_NP() != 0) {
				Behavior::de_->InitialUseF();
			} else ParameterControl::ParameterControlNotInitialedError("use_F_", "np_");
		}

		void ParameterControl::InitialDE_K() {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetDE_NP() != 0) {
				Behavior::de_->InitialUseK();
			} else ParameterControl::ParameterControlNotInitialedError("use_K_", "np_");
		}

		void ParameterControl::InitialDE_P() {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetDE_NP() != 0) {
				Behavior::de_->InitialUseP();
			} else ParameterControl::ParameterControlNotInitialedError("use_P_", "np_");
		}
		void ParameterControl::MallocSaDE_MemoryCR(const size_t num_of_memory) {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetSaDE_LP() > 0) {
				if (Behavior::lv_->ev_.GetDE_NP() > 0) {
					if (num_of_memory == 1 || num_of_memory == Behavior::lv_->ev_.GetDE_NumOfStrategies()) {
						Behavior::sade_->MallocSaDE_MemoryCR(num_of_memory);
					} else ParameterControl::ParameterControlNotInitialedError("sade_memory_CR_", "num_of_memory");
				} else ParameterControl::ParameterControlNotInitialedError("sade_selected_CR_", "de_NP_");
			} else ParameterControl::ParameterControlNotInitialedError("sade_memory_CR_", "sade_LP_");
		}

		void ParameterControl::DemallocSaDE_MemoryCR(const size_t num_of_memory) {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetSaDE_LP() > 0) {
				if (Behavior::lv_->ev_.GetDE_NP() > 0) {
					if (num_of_memory == 1 || num_of_memory == Behavior::lv_->ev_.GetDE_NumOfStrategies()) {
						Behavior::sade_->DemallocSaDE_MemoryCR(num_of_memory);
					} else ParameterControl::ParameterControlDemallocError("sade_memory_CR_", "num_of_memory");
				} else ParameterControl::ParameterControlDemallocError("sade_memory_CR_", "de_NP_");
			} else ParameterControl::ParameterControlDemallocError("sade_memory_CR_", "sade_LP_");
		}

		void ParameterControl::InitialSaDE_MemoryCR(const size_t num_of_memory) {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetSaDE_LP() > 0) {
				if (num_of_memory == 1 || num_of_memory == Behavior::lv_->ev_.GetDE_NumOfStrategies()) {
					Behavior::sade_->InitialSaDE_MemoryCR(num_of_memory);
				} else ParameterControl::ParameterControlNotInitialedError("sade_memory_CR_", "num_of_memory");
			} else ParameterControl::ParameterControlNotInitialedError("sade_memory_CR_", "sade_LP_");
		}

		void ParameterControl::MallocSHADE_MemoryCR() {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetSHADE_H() > 0) {
				Behavior::shade_->MallocSHADE_MemoryCR();
			} else ParameterControl::ParameterControlNotInitialedError("shade_memory_CR_", "shade_H_");
		}

		void ParameterControl::InitialSHADE_MemoryCR() {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetSHADE_H() > 0) {
				Behavior::shade_->InitialSHADE_MemoryCR();
			} else ParameterControl::ParameterControlNotInitialedError("shade_memory_CR_", "shade_H_");
		}

		void ParameterControl::MallocSHADE_MemoryF() {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetSHADE_H() > 0) {
				Behavior::shade_->MallocSHADE_MemoryF();
			} else ParameterControl::ParameterControlNotInitialedError("shade_memory_F_", "shade_H_");
		}

		void ParameterControl::InitialSHADE_MemoryF() {
			Behavior::CheckLV();
			if (Behavior::lv_->ev_.GetSHADE_H() > 0) {
				Behavior::shade_->InitialSHADE_MemoryF();
			} else ParameterControl::ParameterControlNotInitialedError("shade_memory_F_", "shade_H_");

		}
	}
}