#include "../headers/executivevariables.h"

namespace evolutionalgorithm {
	ExecutiveVariables::ExecutiveVariables() {
		Variables::ReInitialGlobalVariable();
	}

	ExecutiveVariables::~ExecutiveVariables() {

	}

	void ExecutiveVariables::UpdateDE_CR(double new_CR) {
		Variables::de_CR_ = new_CR;
	}

	double ExecutiveVariables::GetDE_CR() {
		return Variables::de_CR_;
	}

	void ExecutiveVariables::UpdateDE_NP(size_t new_NP) {
		Variables::de_NP_ = new_NP;
	}

	size_t ExecutiveVariables::GetDE_NP() {
		return Variables::de_NP_;
	}

	void ExecutiveVariables::UpdateDE_NextGenNP(size_t new_next_gen_NP) {
		Variables::de_next_gen_NP_ = new_next_gen_NP;
	}

	size_t ExecutiveVariables::GetDE_NextGenNP() {
		return Variables::de_next_gen_NP_;
	}

	void ExecutiveVariables::UpdateDE_Dim(unsigned new_dim) {
		Variables::de_dim_ = new_dim;
	}

	unsigned ExecutiveVariables::GetDE_Dim() {
		return Variables::de_dim_;
	}

	void ExecutiveVariables::UpdateDE_F(double new_F) {
		Variables::de_F_ = new_F;
	}

	double ExecutiveVariables::GetDE_F() {
		return Variables::de_F_;
	}

	void ExecutiveVariables::UpdateDE_K(double new_K) {
		Variables::de_K_ = new_K;
	}

	double ExecutiveVariables::GetDE_K() {
		return Variables::de_K_;
	}

	void ExecutiveVariables::UpdateOut_B(bool new_out_b) {
		Variables::out_b = new_out_b;
	}

	bool ExecutiveVariables::GetOut_B() {
		return Variables::out_b;
	}

	size_t ExecutiveVariables::GetDE_PMin() {
		return Variables::random_P_min_;
	}

	double ExecutiveVariables::GetDE_PMaxScale() {
		return Variables::random_P_max_scale_;
	}

	size_t ExecutiveVariables::GetArchiveSize() {
		return Variables::archive_size_;
	}

	void ExecutiveVariables::UpdateDE_P(double new_P) {
		Variables::de_P_ = new_P;
	}

	double ExecutiveVariables::GetDE_P() {
		return Variables::de_P_;
	}

	double* ExecutiveVariables::GetBoundMin() {
		return Variables::bound_min_;
	}

	double* ExecutiveVariables::GetBoundMax() {
		return Variables::bound_max_;
	}

	double ExecutiveVariables::GetBoundMin(unsigned dim) {
		return Variables::bound_min_[dim];
	}

	double ExecutiveVariables::GetBoundMax(unsigned dim) {
		return Variables::bound_max_[dim];
	}

	size_t ExecutiveVariables::GetDE_NumOfStrategies() {
		return Variables::de_num_of_strategies_;
	}

	unsigned ExecutiveVariables::GetDE_MaxFE() {
		return Variables::max_fe_;
	}

	unsigned ExecutiveVariables::GetDE_MaxGen() {
		return Variables::max_gen_;
	}

	double ExecutiveVariables::GetDE_Optimal_() {
		return Variables::optimal_;
	}

	std::map<corematerial::MutantAndCrossover, size_t>* ExecutiveVariables::GetDE_StrategiesIndexMap() {
		return &(Variables::strategy_index_);
	}

	// SaDE
	size_t ExecutiveVariables::GetSaDE_LP() {
		return Variables::sade_LP_;
	}

	double ExecutiveVariables::GetSaDE_Epsilion() {
		return Variables::sade_epsilion_;
	}

	// END SaDE

	// SHADE
	size_t ExecutiveVariables::GetSHADE_H() {
		return Variables::shade_H_;
	}

	// END SHADE

	corematerial::InitialPopulation ExecutiveVariables::GetDE_InitialPopulationPattern() {
		return Variables::de_initial_pattern_;
	}

	corematerial::Archive ExecutiveVariables::GetDE_ArchivePattern() {
		return Variables::de_archive_pattern_;
	}

	corematerial::Memory ExecutiveVariables::GetDE_Memory_Pattern() {
		return Variables::de_memory_pattern_;
	}

	corematerial::MemoryCR ExecutiveVariables::GetDE_MemoryCR_Pattern() {
		return Variables::de_memory_CR_pattern_;
	}

	corematerial::MemoryCR_Setting ExecutiveVariables::GetDE_MemoryCR_SettingPattern() {
		return Variables::de_memory_CR_setting_pattern_;
	}

	corematerial::MemoryF ExecutiveVariables::GetDE_MemoryF_Pattern() {
		return Variables::de_memory_F_pattern_;
	}

	corematerial::MutantAndCrossover ExecutiveVariables::GetDE_StrategiesPattern() {
		return Variables::de_mutant_and_crossover_pattern_;
	}

	corematerial::OutBoundHandler ExecutiveVariables::GetDE_OutBoundHandlerPattern() {
		return Variables::de_out_bound_handler_pattern_;
	}

	corematerial::InitialPopulation ExecutiveVariables::GetInitialPopulationPattern() {
		return Variables::de_initial_pattern_;
	}

	corematerial::StopCriterion ExecutiveVariables::GetStopCriterionPattern() {
		return Variables::de_stop_criterion_pattern_;
	}

	corematerial::StrategiesSelection ExecutiveVariables::GetDE_StrategiesSelectionPattern() {
		return Variables::de_strategies_selection_pattern_;
	}

	corematerial::Selection ExecutiveVariables::GetDE_SelectionPattern() {
		return Variables::de_selection_pattern_;
	}

	corematerial::ParametersControl ExecutiveVariables::GetParametersControlPattern() {
		return Variables::parameters_control_pattern_;
	}

	corematerial::ParametersControlMethod ExecutiveVariables::GetParametersControlMethodPattern() {
		return Variables::parameters_control_method_pattern_;
	}
}