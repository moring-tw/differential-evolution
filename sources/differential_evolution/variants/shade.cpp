#include "../../../headers/differential_evolution/variants/shade.h"

namespace evolutionalgorithm{
	namespace differentialevolution {
		SHADE::SHADE() {

		}

		SHADE::~SHADE() {

		}

		void SHADE::NextRun() {
			shade_is_fitness_copied_ = false;
			shade_is_ri_produced_ = false;
			shade_is_delta_fitness_calculated_ = false;
			shade_insert_H_plus_1_ = false;
			Basic::lv_->shade_insert_h_ = 0;
			Basic::lv_->shade_archive_now_size_ = 0;
		}

		void SHADE::InitialSHADE_Archive() {
			Basic::lv_->archive_.Initial(Basic::lv_->ev_.GetArchiveSize());
			Basic::lv_->shade_archive_now_size_ = 0;
			Basic::ss_->SetArchive(&(Basic::lv_->archive_));
		}

		void SHADE::MallocSHADE_MemoryCR() {
			Basic::lv_->shade_memory_CR_ = (double*)malloc(sizeof(double) * Basic::lv_->ev_.GetSHADE_H());
		}

		/*void SHADE::DemallocSHADE_MemoryCR() {
			free(Basic::lv_->shade_memory_CR_);
			Basic::lv_->shade_memory_CR_ = nullptr;
		}*/

		void SHADE::MallocSHADE_MemoryF() {
			printf("--------------%d--------------\n", Basic::lv_->ev_.GetSHADE_H());
			Basic::lv_->shade_memory_F_ = (double*)malloc(sizeof(double) * Basic::lv_->ev_.GetSHADE_H());
		}

		/*void SHADE::DemallocSHADE_MemoryF() {
			free(Basic::lv_->shade_memory_F_);
			Basic::lv_->shade_memory_F_ = nullptr;
		}*/

		void SHADE::InitialSHADE_MemoryCR() {
			const size_t H = Basic::lv_->ev_.GetSHADE_H();
			for (size_t h_counter = 0; h_counter < H; ++h_counter) {
				Basic::lv_->shade_memory_CR_[h_counter] = 0.5;
			}
			Basic::lv_->shade_insert_h_ = 0;
		}

		void SHADE::InitialSHADE_MemoryF() {
			const size_t H = Basic::lv_->ev_.GetSHADE_H();
			for (size_t h_counter = 0; h_counter < H; ++h_counter) {
				Basic::lv_->shade_memory_F_[h_counter] = 0.5;
			}
			Basic::lv_->shade_insert_h_ = 0;
		}

		void SHADE::SelectSHADE_CR() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			SHADE::RandomRi();
			SHADE::CopyFitnessArray();
			for (size_t next_gen_np_counter = 0; next_gen_np_counter < next_gen_np; ++next_gen_np_counter) {
				Basic::lv_->next_generation_[next_gen_np_counter].SetCR(SHADE::ProduceCR(Basic::lv_->shade_memory_CR_[Basic::lv_->shade_ri_[next_gen_np_counter]]));
			}
		}
		
		void SHADE::SelectSHADE_F() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			SHADE::RandomRi();
			SHADE::CopyFitnessArray();
			for (size_t next_gen_np_counter = 0; next_gen_np_counter < next_gen_np; ++next_gen_np_counter) {
				Basic::lv_->next_generation_[next_gen_np_counter].SetF(SHADE::ProduceF(Basic::lv_->shade_memory_F_[Basic::lv_->shade_ri_[next_gen_np_counter]]));
			}
		}

		/*void SHADE::BeforeSelectionSHADE_MemoryCR() {
			Basic::lv_->shade_success_CR_.clear();
			Basic::lv_->delta_fitness_.clear();
		}

		void SHADE::BeforeSelectionSHADE_MemoryF() {
			Basic::lv_->shade_success_F_.clear();
			Basic::lv_->delta_fitness_.clear();
		}*/

		void SHADE::SuccessSelectionSHADE_MemoryCR() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			const size_t H = Basic::lv_->ev_.GetSHADE_H();
			SHADE::CalculateSuccessDeltaFitness();
			for (size_t next_gen_np_counter = 0; next_gen_np_counter < next_gen_np; ++next_gen_np_counter) {
				if (Basic::lv_->next_generation_[next_gen_np_counter].is_less_) {
					Basic::lv_->shade_success_CR_.push_back(Basic::lv_->next_generation_[next_gen_np_counter].GetCR());
				}
			}

			if (!Basic::lv_->shade_success_CR_.empty()) {
				Basic::lv_->shade_memory_CR_[Basic::lv_->shade_insert_h_ % H] = PublicFunction::WeightedArithmeticMean(Basic::lv_->delta_fitness_, Basic::lv_->shade_success_CR_);
				SHADE::shade_insert_H_plus_1_ = true;
			}
		}

		void SHADE::SuccessSelectionSHADE_MemoryF() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			const size_t H = Basic::lv_->ev_.GetSHADE_H();
			SHADE::CalculateSuccessDeltaFitness();
			for (size_t next_gen_np_counter = 0; next_gen_np_counter < next_gen_np; ++next_gen_np_counter) {
				if (Basic::lv_->next_generation_[next_gen_np_counter].is_less_) {
					Basic::lv_->shade_success_F_.push_back(Basic::lv_->next_generation_[next_gen_np_counter].GetF());
				}
			}

			if (!Basic::lv_->shade_success_F_.empty()) {
				Basic::lv_->shade_memory_F_[Basic::lv_->shade_insert_h_ % H] = PublicFunction::WeightedLenmerMean(Basic::lv_->delta_fitness_, Basic::lv_->shade_success_F_);
				SHADE::shade_insert_H_plus_1_ = true;
			}
		}

		void SHADE::SuccessSelectionSHADE_Archive() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			const size_t archive_size = Basic::lv_->ev_.GetArchiveSize();
			size_t parent;
			size_t replace_index;
			for (size_t next_gen_np_counter = 0; next_gen_np_counter < next_gen_np; ++next_gen_np_counter) {
				if (Basic::lv_->next_generation_[next_gen_np_counter].is_less_) {
					parent = Basic::lv_->next_generation_[next_gen_np_counter].GetComparedParent();
					if (Basic::lv_->shade_archive_now_size_ < archive_size) {
						replace_index = Basic::lv_->shade_archive_now_size_;
						//Basic::lv_->archive_[Basic::lv_->shade_archive_now_size_] = SHADE::copied_dimensions_[parent];
						Basic::lv_->archive_[replace_index] = Basic::lv_->wait_free_map_of_individual_dimension_[parent];
						++Basic::lv_->shade_archive_now_size_;
					} else {
						replace_index = PublicFunction::RandomInt(0, archive_size - 1);
						free(Basic::lv_->archive_[replace_index].GetDimensions());
						Basic::lv_->archive_[replace_index] = Basic::lv_->wait_free_map_of_individual_dimension_[parent];
					}
					if (Basic::lv_->archive_[replace_index].GetDimensions() == nullptr) {
						printf("shade archive recording error.\n");
						exit(0);
					}
					Basic::lv_->wait_free_map_of_individual_dimension_[parent] = nullptr; // prevents deallocating memory.
				}
			}
		}

		/*void SHADE::AfterSelectionSHADE_MemoryCR() {
			const size_t H = Basic::lv_->ev_.GetSHADE_H();
			if (!Basic::lv_->shade_success_CR_.empty()) {
				Basic::lv_->shade_memory_CR_[Basic::lv_->shade_insert_h_ % H] = PublicFunction::WeightedArithmeticMean(Basic::lv_->delta_fitness_ ,Basic::lv_->shade_success_CR_);
				SHADE::shade_insert_H_plus_1_ = true;
			}
		}*/

		//void SHADE::AfterSelectionSHADE_MemoryF() {
		//	const size_t H = Basic::lv_->ev_.GetSHADE_H();
		//	if (!Basic::lv_->shade_success_F_.empty()) {
		//		Basic::lv_->shade_memory_F_[Basic::lv_->shade_insert_h_ % H] = PublicFunction::WeightedLenmerMean(Basic::lv_->delta_fitness_, Basic::lv_->shade_success_F_);
		//		SHADE::shade_insert_H_plus_1_ = true;
		//	}
		//}

		void SHADE::NextGen() {
			if (SHADE::shade_insert_H_plus_1_) {
				++Basic::lv_->shade_insert_h_;
				shade_insert_H_plus_1_ = false;
			}

			Basic::lv_->shade_success_CR_.clear();
			Basic::lv_->shade_success_F_.clear();
			Basic::lv_->delta_fitness_.clear();

			shade_is_fitness_copied_ = false; // each generation copies fitness value
			shade_is_ri_produced_ = false; // each generation using different ri
			shade_is_delta_fitness_calculated_ = false; // each gereration calculates delta fitness
		}

		void SHADE::CopyFitnessArray() {
			const size_t NP = Basic::lv_->ev_.GetDE_NP();
			if (!SHADE::shade_is_fitness_copied_) {
				if (NP != SHADE::prev_np_ || copied_fitness_ == nullptr) {
					// if size of np changed or copied_fitness hasn't been malloc
					printf("REMALLOC COPY FITNESS\n");
					SHADE::prev_np_ = NP;
					free(SHADE::copied_fitness_);
					SHADE::copied_fitness_ = (double*)malloc(sizeof(double) * NP);
				}
				for (size_t np_counter = 0; np_counter < NP; ++np_counter) {
					SHADE::copied_fitness_[np_counter] = Basic::lv_->fitness_[np_counter];
				}
				SHADE::shade_is_fitness_copied_ = true;
			}
		}

		void SHADE::RandomRi() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			const size_t archive_size = Basic::lv_->ev_.GetArchiveSize();
			if (!SHADE::shade_is_ri_produced_) {
				if (next_gen_np != SHADE::prev_next_gen_np_ || Basic::lv_->shade_ri_ == nullptr) {
					SHADE::prev_next_gen_np_ = next_gen_np;
					free(Basic::lv_->shade_ri_);
					Basic::lv_->shade_ri_ = (size_t*)malloc(sizeof(size_t) * next_gen_np);
				}
				for (size_t next_gen_np_counter = 0; next_gen_np_counter < next_gen_np; ++next_gen_np_counter) {
					Basic::lv_->shade_ri_[next_gen_np_counter] = PublicFunction::RandomInt(0, archive_size - 1);
				}
				SHADE::shade_is_ri_produced_ = true;
			}
		}

		void SHADE::CalculateSuccessDeltaFitness() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			size_t parent = 0;
			if (!SHADE::shade_is_delta_fitness_calculated_) {
				for (size_t next_gen_np_counter = 0; next_gen_np_counter < next_gen_np; ++next_gen_np_counter) {
					if (Basic::lv_->next_generation_[next_gen_np_counter].is_less_) {
						parent = Basic::lv_->next_generation_[next_gen_np_counter].GetComparedParent();
						//
						// Because the is_less_ flag of the next gen individual was set to true, fitness values recorded in local variables at index(parent) had been repalced with the next generation individual.
						// and the copied_fitness had recorded the all fitness values of current generation, therefore we can calculte correct value of delta fitness value.
						//
						Basic::lv_->delta_fitness_.push_back(SHADE::copied_fitness_[parent] - Basic::lv_->fitness_[parent]);
					}
				}
				SHADE::shade_is_delta_fitness_calculated_ = true;
			}
		}

		void SHADE::RecycleMemory() {
			free(SHADE::copied_fitness_);
			SHADE::copied_fitness_ = nullptr;

			free(Basic::lv_->shade_ri_);
			Basic::lv_->shade_ri_ = nullptr;

			free(Basic::lv_->shade_memory_CR_);
			Basic::lv_->shade_memory_CR_ = nullptr;

			free(Basic::lv_->shade_memory_F_);
			Basic::lv_->shade_memory_F_ = nullptr;
		}
	} // namespace differentialevolution
} // namespace evolutionalgorithm