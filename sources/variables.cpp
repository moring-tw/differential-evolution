#include "../headers/variables.h"

namespace evolutionalgorithm {
    Variables::Variables() {
        ReInitialGlobalVariable();
    }

    unsigned int Variables::GetProblemAmount() {
        return Variables::problem_amount_;
    }

    bool Variables::IsProblemExecuting(size_t problem_index) {
        return Variables::problem_set_[problem_index];
    }

    void Variables::ReInitialGlobalVariable() {
        debug_pattern_ = corematerial::Debug::UNSET;
        de_algorithm_pattern_ = corematerial::Algorithm::kCustom;
        de_initial_pattern_ = corematerial::InitialPopulation::kRandom;
        de_memory_pattern_ = corematerial::Memory::UNSET;
        de_archive_pattern_ = corematerial::Archive::UNSET;
        de_memory_CR_pattern_ = corematerial::MemoryCR::kSaDE_CR;
        de_memory_CR_setting_pattern_ = corematerial::MemoryCR_Setting::UNSET;
        de_memory_F_pattern_ = corematerial::MemoryF::kSHADE_F;
        parameters_control_method_pattern_ = corematerial::ParametersControlMethod::UNSET;
        de_mutant_and_crossover_pattern_ = corematerial::MutantAndCrossover::UNSET;
        de_strategies_selection_pattern_ = corematerial::StrategiesSelection::kSaDE_ss;
        de_selection_pattern_ = corematerial::Selection::kCompetition;
        de_stop_criterion_pattern_ = corematerial::StopCriterion::kMaxFE;
        de_out_bound_handler_pattern_ = corematerial::OutBoundHandler::kRerandomDimension;
        parameters_control_pattern_ = corematerial::ParametersControl::UNSET;
        de_CR_ = -1;
        de_F_ = -1;
        de_K_ = -1;
        de_NP_ = 0;
        de_next_gen_NP_ = 0;
        de_dim_ = 0;
        de_num_of_strategies_ = 0;
        bound_max_ = nullptr;
        bound_min_ = nullptr;
        shade_H_ = 0;
        de_P_ = -1;
        sade_LP_ = 0;
        sade_epsilion_ = 0;
        max_fe_ = 0;
        max_gen_ = 0;
        optimal_ = 0;
        normal_F_mean_ = DBL_MIN;
        normal_F_stddev_ = DBL_MIN;
        random_P_max_scale_ = 0;
        random_P_min_ = 0;
        archive_size_ = 0;
        problem_amount_ = 0;
        problem_set_ = nullptr;
    }
} // namespace evolutionalgorithm