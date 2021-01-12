#pragma warning(disable:6386; disable:6011)

#include "../../../headers/differential_evolution/variants/sade.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		SaDE::SaDE()
		{
		}

		SaDE::~SaDE()
		{
		}

		void SaDE::NextRun() {
			SaDE::now_learn_ = 0;
		}

		void SaDE::MallocSaDE_StrategiesSelection() {
			const size_t num_of_strategies = Basic::lv_->ev_.GetDE_NumOfStrategies();
			const size_t LP = Basic::lv_->ev_.GetSaDE_LP();
			
			Basic::lv_->sade_success_memory_ = (size_t**)malloc(sizeof(size_t*) * num_of_strategies);
			Basic::lv_->sade_success_memory_sum_ = (size_t*)malloc(sizeof(size_t) * num_of_strategies);
			Basic::lv_->sade_fail_memory_ = (size_t**)malloc(sizeof(size_t*) * num_of_strategies);
			Basic::lv_->sade_fail_memory_sum_ = (size_t*)malloc(sizeof(size_t) * num_of_strategies);
			Basic::lv_->strategies_probability_ = (double*)malloc(sizeof(double) * num_of_strategies);
			for (size_t strategies_counter = 0; strategies_counter < num_of_strategies; ++strategies_counter) {
				Basic::lv_->sade_success_memory_[strategies_counter] = (size_t*)malloc(sizeof(size_t) * LP);
				Basic::lv_->sade_fail_memory_[strategies_counter] = (size_t*)malloc(sizeof(size_t) * LP);
				for (size_t LP_counter = 0; LP_counter < LP; ++LP_counter) {
					Basic::lv_->sade_success_memory_[strategies_counter][LP_counter] = 0;
					Basic::lv_->sade_fail_memory_[strategies_counter][LP_counter] = 0;
				}
			}
		}

		void SaDE::DemallocSaDE_StrategiesSelection() {
			const size_t num_of_strategies = Basic::lv_->ev_.GetDE_NumOfStrategies();
			for (size_t strategies_counter = 0; strategies_counter < num_of_strategies; ++strategies_counter) {
				free(Basic::lv_->sade_success_memory_[strategies_counter]);
				Basic::lv_->sade_success_memory_[strategies_counter] = nullptr;
				free(Basic::lv_->sade_fail_memory_[strategies_counter]);
				Basic::lv_->sade_fail_memory_[strategies_counter] = nullptr;
			}
			free(Basic::lv_->sade_success_memory_);
			Basic::lv_->sade_success_memory_ = nullptr;
			free(Basic::lv_->sade_fail_memory_);
			Basic::lv_->sade_fail_memory_ = nullptr;
			free(Basic::lv_->sade_success_memory_sum_);
			Basic::lv_->sade_success_memory_sum_ = nullptr;
			free(Basic::lv_->sade_fail_memory_sum_);
			Basic::lv_->sade_fail_memory_sum_ = nullptr;
			free(Basic::lv_->strategies_probability_);
			Basic::lv_->strategies_probability_ = nullptr;
		}

		//
		// if num_of_memory is 1 which means every strategies record CR in the same vector when it is success to produce better individual.
		// if num_of_memory is equal to num of strategies, this will cause recording independently in different vectors which are respective to strategies.
		//
		void SaDE::MallocSaDE_MemoryCR(const size_t num_of_memory) { // num_of_memory only should be equal to 1 or num of strategies.
			const size_t LP = Basic::lv_->ev_.GetSaDE_LP();
			const size_t NP = Basic::lv_->ev_.GetDE_NP();
			Basic::lv_->sade_memory_CR_ = (std::vector<double>***)malloc(sizeof(std::vector<double>**) * num_of_memory);
			Basic::lv_->sade_CRm_ = (double*)malloc(sizeof(double) * num_of_memory);
			for (size_t strategies_counter = 0; strategies_counter < num_of_memory; ++strategies_counter) {
				Basic::lv_->sade_memory_CR_[strategies_counter] = (std::vector<double>**)malloc(sizeof(std::vector<double>*) * LP);
				for (size_t LP_counter = 0; LP_counter < LP; ++LP_counter) {
					Basic::lv_->sade_memory_CR_[strategies_counter][LP_counter] = new vector<double>();
				}
			}
		}

		void SaDE::DemallocSaDE_MemoryCR(const size_t num_of_memory) {
			const size_t LP = Basic::lv_->ev_.GetSaDE_LP();
			const size_t NP = Basic::lv_->ev_.GetDE_NP();
			for (size_t strategies_counter = 0; strategies_counter < num_of_memory; ++strategies_counter) {
				for (size_t LP_counter = 0; LP_counter < LP; ++LP_counter) {
					delete Basic::lv_->sade_memory_CR_[strategies_counter][LP_counter];
					Basic::lv_->sade_memory_CR_[strategies_counter][LP_counter] = nullptr;
				}
				free(Basic::lv_->sade_memory_CR_[strategies_counter]);
				Basic::lv_->sade_memory_CR_[strategies_counter] = nullptr;
			}
			free(Basic::lv_->sade_memory_CR_);
			Basic::lv_->sade_memory_CR_ = nullptr;
		}

		void SaDE::InitialSaDE_StrategiesSelection() {
			const size_t num_of_strategies = Basic::lv_->ev_.GetDE_NumOfStrategies();
			for (size_t strategies_counter = 0; strategies_counter < num_of_strategies; ++strategies_counter) {
				Basic::lv_->sade_success_memory_sum_[strategies_counter] = 0;
				Basic::lv_->sade_fail_memory_sum_[strategies_counter] = 0;
				Basic::lv_->strategies_probability_[strategies_counter] = 1.0 / static_cast<double>(num_of_strategies);
			}
		}

		//
		// if num_of_memory is 1 which means every strategies record CR in the same vector when it is success to produce better individual.
		// if num_of_memory is equal to num of strategies, this will cause recording independently in different vectors which are respective to strategies.
		//
		void SaDE::InitialSaDE_MemoryCR(const size_t num_of_memory) {
			const size_t LP = Basic::lv_->ev_.GetSaDE_LP();
			for (size_t strategies_counter = 0; strategies_counter < num_of_memory; ++strategies_counter) {
				Basic::lv_->sade_CRm_[strategies_counter] = 0.5;
				for (size_t LP_counter = 0; LP_counter < LP; ++LP_counter) {
					Basic::lv_->sade_memory_CR_[strategies_counter][LP_counter]->clear();
				}
			}
		}

		void SaDE::CalculateSaDE_StrategiesProbability() {
			if (Basic::lv_->now_gen_ >= Basic::lv_->ev_.GetSaDE_LP()) {
				double all_sum = 0.0;
				const size_t num_of_strategies = Basic::lv_->ev_.GetDE_NumOfStrategies();
				const double epsilion = Basic::lv_->ev_.GetSaDE_Epsilion();
				for (size_t strategies_counter = 0; strategies_counter < num_of_strategies; ++strategies_counter) {
					Basic::lv_->strategies_probability_[strategies_counter] = ((double)Basic::lv_->sade_success_memory_sum_[strategies_counter] /
						((double)Basic::lv_->sade_success_memory_sum_[strategies_counter] + (double)Basic::lv_->sade_fail_memory_sum_[strategies_counter])) +
						epsilion;
					all_sum += Basic::lv_->strategies_probability_[strategies_counter];
				}
				for (size_t strategies_counter = 0; strategies_counter < num_of_strategies; ++strategies_counter) {
					Basic::lv_->strategies_probability_[strategies_counter] /= all_sum;
					//std::cout <<"["<<strategies_counter<<"]" <<":"<<Basic::lv_->strategies_probability_[strategies_counter] << std::endl;
				}
			}
		}

		void SaDE::SelectSaDE_Strategies() {
			const size_t np = Basic::lv_->ev_.GetDE_NP();
			const double bias = 1.0 / np;
			double random_number = PublicFunction::RandomDouble(0, bias);
			double probability_upper_bound = 0;
			const corematerial::MutantAndCrossover evolution_pattern = Basic::lv_->ev_.GetDE_StrategiesPattern();
			corematerial::MutantAndCrossover now_strategy = corematerial::MutantAndCrossover::UNSET;
			size_t strategies_counter = 0;
			for (size_t np_counter = 0; np_counter < np; ++np_counter) {
				if (random_number == 0 || random_number > probability_upper_bound) {
					probability_upper_bound += Basic::lv_->strategies_probability_[strategies_counter];
					++strategies_counter;
					do {
						if (now_strategy != 0) {
							now_strategy <<= 1;
						} else {
							now_strategy = static_cast<corematerial::MutantAndCrossover>(0x01);
						}
					} while ((evolution_pattern & now_strategy) == 0);
				}
				Basic::lv_->next_generation_[np_counter].use_strategy_ = now_strategy;
				Basic::lv_->next_generation_[np_counter].use_strategy_index_ = (strategies_counter - 1);
				//Basic::lv_->next_generation_[np_counter].use_strategy_index_ = Basic::FindStrategyIndex(now_strategy);
				random_number += bias;
			}
		}

		void SaDE::CalculateSaDE_CRm(const size_t num_of_memory) {
			const size_t LP = Basic::lv_->ev_.GetSaDE_LP();
			if (Basic::lv_->now_gen_ >= LP) {
				SaDE::now_learn_ = Basic::lv_->now_gen_ % LP;
				size_t total_size = 0;
				for (size_t strategies_counter = 0; strategies_counter < num_of_memory; ++strategies_counter) {
					for (size_t LP_counter = 0; LP_counter < LP; ++LP_counter) {
						if (SaDE::now_learn_ == LP_counter) continue;
						for (size_t memory_CR_counter = 0; memory_CR_counter < Basic::lv_->sade_memory_CR_[strategies_counter][LP_counter]->size(); ++memory_CR_counter) {
							// gather successful CRs of last LP generations into SaDE::now_learn_ vector.
							Basic::lv_->sade_memory_CR_[strategies_counter][SaDE::now_learn_]->push_back((*Basic::lv_->sade_memory_CR_[strategies_counter][LP_counter])[memory_CR_counter]);
						}
					}
					sort(Basic::lv_->sade_memory_CR_[strategies_counter][SaDE::now_learn_]->begin(), Basic::lv_->sade_memory_CR_[strategies_counter][SaDE::now_learn_]->end());
					total_size = Basic::lv_->sade_memory_CR_[strategies_counter][SaDE::now_learn_]->size();
					if (total_size % 2 == 0 && total_size != 0) {
						Basic::lv_->sade_CRm_[strategies_counter] = ((*Basic::lv_->sade_memory_CR_[strategies_counter][SaDE::now_learn_])[total_size / 2 - 1] + (*Basic::lv_->sade_memory_CR_[strategies_counter][now_learn_])[total_size / 2]) / 2;
					} else if (total_size % 2 == 1) {
						Basic::lv_->sade_CRm_[strategies_counter] = (*Basic::lv_->sade_memory_CR_[strategies_counter][SaDE::now_learn_])[total_size / 2];
					}
					Basic::lv_->sade_memory_CR_[strategies_counter][SaDE::now_learn_]->clear();
					//std::cout <<strategies_counter << " CRM = "<< Basic::lv_->sade_CRm_[strategies_counter] << "\t";
				}
				//std::cout << std::endl;
			}
		}

		void SaDE::SelectSaDE_CR() {
			size_t using_strategy_index = 0;
			size_t strategy = 0x01;
			//corematerial::MutantAndCrossover now_use_strategy;
			const size_t NP = Basic::lv_->ev_.GetDE_NP();
			for (size_t np_counter = 0; np_counter < NP; ++np_counter) {
				using_strategy_index = Basic::lv_->next_generation_[np_counter].use_strategy_index_;
				do {
					Basic::lv_->next_generation_[np_counter].SetCR(PublicFunction::NormalDistributionRandom(Basic::lv_->sade_CRm_[using_strategy_index], 0.1));
				} while (Basic::lv_->next_generation_[np_counter].GetCR() < 0 || Basic::lv_->next_generation_[np_counter].GetCR() > 1);
			}
		}

		void SaDE::BeforeSelectionSaDE_StrategiesSelection() {
			const size_t LP = Basic::lv_->ev_.GetSaDE_LP();
			SaDE::now_learn_ = Basic::lv_->now_gen_ % LP;
			const size_t num_of_strategies = Basic::lv_->ev_.GetDE_NumOfStrategies();
			for (size_t strategies_counter = 0; strategies_counter < num_of_strategies; ++strategies_counter) {
				if (Basic::lv_->now_gen_ >= LP) {
					Basic::lv_->sade_success_memory_sum_[strategies_counter] -= Basic::lv_->sade_success_memory_[strategies_counter][now_learn_];
					Basic::lv_->sade_fail_memory_sum_[strategies_counter] -= Basic::lv_->sade_fail_memory_[strategies_counter][now_learn_];
				}
				Basic::lv_->sade_success_memory_[strategies_counter][now_learn_] = 0;
				Basic::lv_->sade_fail_memory_[strategies_counter][now_learn_] = 0;
			}
		}

		void SaDE::SuccessSelectionSaDE_StrategiesSelection() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			for (size_t np_counter = 0; np_counter < next_gen_np; ++np_counter) {
				if (Basic::lv_->next_generation_[np_counter].is_less_ || Basic::lv_->next_generation_[np_counter].is_equal_) {
					//std::cout << np_counter << " is successful to next gen with strategy[" << Basic::lv_->next_generation_[np_counter].use_strategy_index_ << "]\n";
					++Basic::lv_->sade_success_memory_[Basic::lv_->next_generation_[np_counter].use_strategy_index_][now_learn_];
					++Basic::lv_->sade_success_memory_sum_[Basic::lv_->next_generation_[np_counter].use_strategy_index_];
				}
			}
			/*std::cout << Basic::lv_->sade_success_memory_sum_[0] << "\n";
			std::cout << Basic::lv_->sade_success_memory_sum_[1] << "\n";
			std::cout << Basic::lv_->sade_success_memory_sum_[2] << "\n";
			std::cout << Basic::lv_->sade_success_memory_sum_[3] << "\n";*/
		}

		void SaDE::FailSelectionSaDE_StrategiesSelection() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			for (size_t np_counter = 0; np_counter < next_gen_np; ++np_counter) {
				if (Basic::lv_->next_generation_[np_counter].is_larger_) {
					++Basic::lv_->sade_fail_memory_[Basic::lv_->next_generation_[np_counter].use_strategy_index_][now_learn_];
					++Basic::lv_->sade_fail_memory_sum_[Basic::lv_->next_generation_[np_counter].use_strategy_index_];
				}
			}
			/*std::cout << Basic::lv_->sade_fail_memory_sum_[0] << "\n";
			std::cout << Basic::lv_->sade_fail_memory_sum_[1] << "\n";
			std::cout << Basic::lv_->sade_fail_memory_sum_[2] << "\n";
			std::cout << Basic::lv_->sade_fail_memory_sum_[3] << "\n";
			system("PAUSE");*/
		}

		void SaDE::SuccessSelectionSaDE_MemoryCR() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			for (size_t np_counter = 0; np_counter < next_gen_np; ++np_counter) {
				if (Basic::lv_->next_generation_[np_counter].is_less_ || Basic::lv_->next_generation_[np_counter].is_equal_) {
					Basic::lv_->sade_memory_CR_[Basic::lv_->next_generation_[np_counter].use_strategy_index_][now_learn_]->push_back(Basic::lv_->next_generation_[np_counter].GetCR());
				}
			}
		}
	} // namespace differenatialevolution
} // namespace evolutionalgorithm