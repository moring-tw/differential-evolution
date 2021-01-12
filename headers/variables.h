#pragma once
#ifndef EA_HEADERS_VARIABLES_H_
#define EA_HEADERS_VARIABLES_H_

#include <limits>

#include "corematerial.h"

namespace evolutionalgorithm {
	class Variables {
    public:
        Variables();
        void ReInitialGlobalVariable();
        unsigned int GetProblemAmount();
        bool IsProblemExecuting(size_t);
        friend class ReadConfig;

    protected:
        corematerial::Debug debug_pattern_;
        //unsigned int debug_pattern_;
        corematerial::Algorithm de_algorithm_pattern_;
        //unsigned int de_algorithm_pattern_;
        corematerial::InitialPopulation de_initial_pattern_;
        //unsigned int de_initial_pattern_;
        corematerial::Memory de_memory_pattern_;
        //unsigned int de_memory_pattern_;
        corematerial::Archive de_archive_pattern_;
        //unsigned int de_archive_pattern_;
        corematerial::MemoryCR de_memory_CR_pattern_;
        //unsigned int de_memory_CR_pattern_;
        corematerial::MemoryCR_Setting de_memory_CR_setting_pattern_;
        //unsigned int de_memory_CR_setting_pattern_;
        corematerial::MemoryF de_memory_F_pattern_;
        //unsigned int de_memory_F_pattern_;
        corematerial::ParametersControlMethod parameters_control_method_pattern_;
        //unsigned int parameters_control_pattern_;
        corematerial::MutantAndCrossover de_mutant_and_crossover_pattern_;// Changing INITIAL value is also affecting "de_num_of_strategies" INITIAL value.
                                                                // INITIAL value is NOT default value.
        //unsigned int de_mutant_and_crossover_pattern_;   
        corematerial::StrategiesSelection de_strategies_selection_pattern_;
        //unsigned int de_strategies_selection_pattern_;

        corematerial::Selection de_selection_pattern_;

        corematerial::StopCriterion de_stop_criterion_pattern_;
        //unsigned int de_stop_criterion_pattern_;
        corematerial::OutBoundHandler de_out_bound_handler_pattern_;
        //unsigned int de_out_bound_handler_pattern_;
        corematerial::ParametersControl parameters_control_pattern_;
        double de_CR_;
        double de_F_;
        double de_K_;
        size_t de_NP_;
        size_t de_next_gen_NP_;
        //unsigned int de_dim_;
        size_t de_dim_;
        size_t de_num_of_strategies_; // This INITIAL value is associated to "de_mutant_and_crossover_pattern_".
        double* bound_min_;
        double* bound_max_;
        unsigned shade_H_;
        double de_P_;
        size_t sade_LP_;
        double sade_epsilion_;
        unsigned int max_fe_;
        unsigned int max_gen_;
        double optimal_;
        double normal_F_mean_;
        double normal_F_stddev_;
        double random_P_max_scale_;
        unsigned int random_P_min_;
        size_t archive_size_;
        size_t problem_amount_;
        bool* problem_set_;

        bool out_b;
        std::map<corematerial::MutantAndCrossover, size_t> strategy_index_;
    private:

	};
} // namespace evolutionalgorithm

#endif // !EA_HEADERS_VARIABLES_H_
