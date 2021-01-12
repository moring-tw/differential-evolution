#include "../../headers/differential_evolution/process_controller.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		ProcessController::ProcessController() {

		}
		ProcessController::~ProcessController() {

		}

		void ProcessController::SetBehaviors(Behavior& b) {
			b.SetDE(&(ProcessController::de_));
			b.SetSaDE(&(ProcessController::sade_));
			b.SetSHADE(&(ProcessController::shade_));
			b.SetRandom(&(ProcessController::random_));
			b.SetLocalVariables(&(ProcessController::lv_));
		}

		void ProcessController::SetVariants(Basic& b) {
			b.SetStrategies(&(ProcessController::ss_));
			b.SetLocalVariables(&(ProcessController::lv_));
		}

		void ProcessController::NextRun() {
			if (!ProcessController::is_initialed_) {
				ProcessController::SetVariants(ProcessController::de_);
				ProcessController::SetVariants(ProcessController::sade_);
				ProcessController::SetVariants(ProcessController::shade_);
				ProcessController::SetVariants(ProcessController::random_);
				ProcessController::SetBehaviors(ProcessController::memory_);
				ProcessController::SetBehaviors(ProcessController::parameter_control_);
				ProcessController::SetBehaviors(ProcessController::evolve_);
				ProcessController::SetBehaviors(ProcessController::select_);
				ProcessController::is_initialed_ = true;
			}
			ProcessController::de_.NextRun();
			ProcessController::sade_.NextRun();
			ProcessController::shade_.NextRun();
			ProcessController::lv_.NextRun();
		}

		void ProcessController::Execute() {
			ProcessController::BeforeInitial();
			ProcessController::Initial();
			ProcessController::AfterInitial();
			while (!ProcessController::ReachStopCriterion()) {
				//printf("now gen: %d\n", lv_.now_gen_);
				ProcessController::BeforeEvolution();
				ProcessController::Evolution();
				ProcessController::AfterEvolution();

				ProcessController::BeforeSelection();
				ProcessController::Selection();
				ProcessController::AfterSelection();
				ProcessController::NextGen();
				if (ProcessController::debug_)
					std::cout << "temporarily stop here." << std::endl;
			}
			printf("stop here\n");
			ProcessController::RecycleMemory();
		}

		void ProcessController::SetBenchmark(Benchmarks* fp) {
			ProcessController::lv_.fp_ = fp;
		}

		void ProcessController::SetExecutiveVariables(ExecutiveVariables& ev) {
			ProcessController::lv_.ev_ = ev;
		}

		double ProcessController::GetBest() {
			return ProcessController::lv_.now_best_;
		}

		void ProcessController::BeforeInitial() { // malloc
			// Strategies Selection
			if (ProcessController::lv_.ev_.GetDE_NumOfStrategies() >= 2) {
				switch (ProcessController::lv_.ev_.GetDE_StrategiesSelectionPattern()) {
				case corematerial::StrategiesSelection::kSaDE_ss:
					if (ProcessController::debug_)
						std::cout << "MallocSaDE_StrategiesSelection" << std::endl;
					memory_.MallocSaDE_StrategiesSelection();
					break;
				default:
					std::cout << "Unknown Strategies selection pattern." << std::endl;
					exit(0);
				}
			}
			// NP Rank
			if ((ProcessController::lv_.ev_.GetDE_Memory_Pattern() & corematerial::Memory::kNPRank) == corematerial::Memory::kNPRank) {
				memory_.MallocNP_Rank();
			}
			// parameter control CR
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kCR) == corematerial::ParametersControl::kCR) {
				// memory CR
				if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kMemoryCR) == corematerial::ParametersControlMethod::kMemoryCR) {
					switch (ProcessController::lv_.ev_.GetDE_MemoryCR_Pattern()) {
					case(corematerial::MemoryCR::kSaDE_CR):
						if ((ProcessController::lv_.ev_.GetDE_MemoryCR_SettingPattern() & corematerial::MemoryCR_Setting::kMemoryByEachStrategy) == corematerial::MemoryCR_Setting::kMemoryByEachStrategy) {
							if (ProcessController::debug_)
								std::cout << "MallocSaDE_MemoryCR(N)" << std::endl;
							parameter_control_.MallocSaDE_MemoryCR(ProcessController::lv_.ev_.GetDE_NumOfStrategies());
						} else {
							if (ProcessController::debug_)
								std::cout << "MallocSaDE_MemoryCR(1)" << std::endl;
							parameter_control_.MallocSaDE_MemoryCR(1);
						}
						break;
					case(corematerial::MemoryCR::kSHADE_CR):
						parameter_control_.MallocSHADE_MemoryCR();
						break;
					default:
						std::cout << "Unknown memory CR pattern." << std::endl;
						exit(0);
					}
				}
			}
			//parameter control F
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kF) == corematerial::ParametersControl::kF){
				// memory F
				if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kMemoryF) == corematerial::ParametersControlMethod::kMemoryF) {
					switch (ProcessController::lv_.ev_.GetDE_MemoryF_Pattern()) {
					case(corematerial::MemoryF::kSHADE_F):
						parameter_control_.MallocSHADE_MemoryF();
						break;
					default:
						printf("Unknown memory F parrern.");
						exit(0);
					}
				}
			}
		}

		void ProcessController::Initial() { // initial value
			switch (ProcessController::lv_.ev_.GetDE_InitialPopulationPattern()) {
			case corematerial::InitialPopulation::kRandom:
				ProcessController::memory_.InitialDE_Population();
				ProcessController::memory_.InitialDE_NextGeneration();
				ProcessController::memory_.InitialDE_Fitness();
				break;
			case corematerial::InitialPopulation::kLHD:
				break;
			default:
				std::cout << "Unknown initial pattern of DE." << std::endl;
				exit(0);
			}
			// np rank
			if ((ProcessController::lv_.ev_.GetDE_Memory_Pattern() & corematerial::Memory::kNPRank) == corematerial::Memory::kNPRank) {
				memory_.InitialNP_Rank();
			}
		}

		void ProcessController::AfterInitial() {
			// Strategies Selection
			if (ProcessController::lv_.ev_.GetDE_NumOfStrategies() == 1) {
				memory_.InitialDE_Strategy();
			} else if (ProcessController::lv_.ev_.GetDE_NumOfStrategies() >= 2) {
				switch (ProcessController::lv_.ev_.GetDE_StrategiesSelectionPattern())
				{
				case corematerial::StrategiesSelection::kSaDE_ss:
					if (ProcessController::debug_)
						std::cout << "InitialSaDE_StrategiesSelection" << std::endl;
					memory_.InitialSaDE_StrategiesSelection();
					break;
				default:
					std::cout << "Unknown Strategies selection pattern." << std::endl;
					exit(0);
				}
			}
			// NP Rank
			if ((ProcessController::lv_.ev_.GetDE_Memory_Pattern() & corematerial::Memory::kNPRank) == corematerial::Memory::kNPRank) {
				memory_.SortNP_Rank();
			}

			// parameter control CR
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kCR) != corematerial::ParametersControl::kCR) {
				// fixed CR
				parameter_control_.InitialDE_CR();
			} else {
				// Memory CR
				if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kMemoryCR) == corematerial::ParametersControlMethod::kMemoryCR) {
					switch (ProcessController::lv_.ev_.GetDE_MemoryCR_Pattern()) {
					case(corematerial::MemoryCR::kSaDE_CR):
						// SaDE 
						if ((ProcessController::lv_.ev_.GetDE_MemoryCR_SettingPattern() & corematerial::MemoryCR_Setting::kMemoryByEachStrategy) == corematerial::MemoryCR_Setting::kMemoryByEachStrategy) {
							if (ProcessController::debug_)
								std::cout << "InitialSaDE_MemoryCR(N)" << std::endl;
							parameter_control_.InitialSaDE_MemoryCR(ProcessController::lv_.ev_.GetDE_NumOfStrategies());
						} else {
							if (ProcessController::debug_)
								std::cout << "InitialSaDE_MemoryCR(1)" << std::endl;
							parameter_control_.InitialSaDE_MemoryCR(1);
						}
						break;
					case(corematerial::MemoryCR::kSHADE_CR):
						// SHADE
						parameter_control_.InitialSHADE_MemoryCR();
						break;
					default:
						std::cout << "Unknown memory CR pattern." << std::endl;
						exit(0);
					}
				}
			}

			// parameter control F
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kF) != corematerial::ParametersControl::kF) {
				// fixed F
				parameter_control_.InitialDE_F();
			} else {
				if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kMemoryF) == corematerial::ParametersControlMethod::kMemoryF) {
					switch (ProcessController::lv_.ev_.GetDE_MemoryF_Pattern()) {
					case(corematerial::MemoryF::kSHADE_F):
						// SHADE
						parameter_control_.InitialSHADE_MemoryF();
						break;
					default:
						std::cout << "Unknown memory F pattern." << std::endl;
						exit(0);
					}
				} else if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kNormalF) == corematerial::ParametersControlMethod::kNormalF) {
					// F with Normal distribution 
				}
			}
			// parameter control K
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kK) != corematerial::ParametersControl::kK) {
				// fixed K
				parameter_control_.InitialDE_K();
			}
			// parameter control P
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kP) != corematerial::ParametersControl::kP) {
				// fixed P
				parameter_control_.InitialDE_P();
			}

			// archive
			if ((ProcessController::lv_.ev_.GetDE_Memory_Pattern() & corematerial::Memory::kArchive) == corematerial::Memory::kArchive) {
				switch (ProcessController::lv_.ev_.GetDE_ArchivePattern()) {
				case(corematerial::Archive::kSHADE_Archive):
					ProcessController::memory_.InitialSHADE_Archive();
					break;
				default:
					printf("Unknown archive pattern.");
					exit(0);
				}
			}
		}

		void ProcessController::BeforeEvolution() {
			// Strategies Selection
			if (ProcessController::lv_.ev_.GetDE_NumOfStrategies() >= 2) {
				switch (ProcessController::lv_.ev_.GetDE_StrategiesSelectionPattern()) {
				case corematerial::StrategiesSelection::kSaDE_ss:
					if (ProcessController::debug_)
						std::cout << "BeforeEvolveSaDE_StrategiesSelection" << std::endl;
					evolve_.BeforeEvolveSaDE_StrategiesSelection();
					break;
				default:
					std::cout << "Unknown Strategies selection pattern when evolving." << std::endl;
					exit(0);
				}
			} else if(ProcessController::lv_.ev_.GetDE_NumOfStrategies() != 1){
				std::cout << "num_of_strategies_ is less than 1, please check." << std::endl;
				exit(0);
			}
			// parameter control CR
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kCR) == corematerial::ParametersControl::kCR) {
				if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kMemoryCR) == corematerial::ParametersControlMethod::kMemoryCR) {
					// Memory CR
					switch (ProcessController::lv_.ev_.GetDE_MemoryCR_Pattern()) {
					case corematerial::MemoryCR::kSaDE_CR:
						// SaDE
						if ((ProcessController::lv_.ev_.GetDE_MemoryCR_SettingPattern() & corematerial::MemoryCR_Setting::kMemoryByEachStrategy) == corematerial::MemoryCR_Setting::kMemoryByEachStrategy) {
							if (ProcessController::debug_)
								std::cout << "BeforeEvolveSaDE_CR_Selection(N)" << std::endl;
							evolve_.BeforeEvolveSaDE_CR_Selection(ProcessController::lv_.ev_.GetDE_NumOfStrategies());
						} else {
							if (ProcessController::debug_)
								std::cout << "BeforeEvolveSaDE_CR_Selection(1)" << std::endl;
							evolve_.BeforeEvolveSaDE_CR_Selection(1);
						}
						break;
					case corematerial::MemoryCR::kSHADE_CR:
						// SHADE
						evolve_.BeforeEvolveSHADE_CR_Selection();
						break;
					default:
						std::cout << "Unavailable de_memory_CR_pattern setting at Evaluation(). Please check." << std::endl;
						exit(0);
					}
				} else parameter_control_error("CR");
			}
			// parameter control F
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kF) == corematerial::ParametersControl::kF) {
				if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kMemoryF) == corematerial::ParametersControlMethod::kMemoryF) {
					// Memory F
					switch (ProcessController::lv_.ev_.GetDE_MemoryF_Pattern()) {
					case corematerial::MemoryF::kSHADE_F:
						// SHADE
						evolve_.BeforeEvolveSHADE_F_Selection();
						break;
					default:
						std::cout << "Unavailable de_memory_F_pattern setting at Evaluation(). Please check." << std::endl;
						exit(0);
					}
				} else if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kNormalF) == corematerial::ParametersControlMethod::kNormalF) {
					// generate F with Normal distribution
				} else parameter_control_error("F");
			}
			//parameter control K
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kK) == corematerial::ParametersControl::kK) {
				parameter_control_error("K");
			}
			// parameter control P
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kP) == corematerial::ParametersControl::kP) {
				if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kRandomP) == corematerial::ParametersControlMethod::kRandomP) {
					evolve_.BeforeEvolveDE_RandomP();
				} else parameter_control_error("P");
			}
		}

		void ProcessController::Evolution() {
			if (ProcessController::lv_.ev_.GetDE_NumOfStrategies() == 1) {
				if (ProcessController::debug_)
					std::cout << "EvolveDE" << std::endl;
				evolve_.EvolveDE();
			} else if (ProcessController::lv_.ev_.GetDE_NumOfStrategies() >= 2) {
				switch (ProcessController::lv_.ev_.GetDE_StrategiesSelectionPattern()) {
				case corematerial::StrategiesSelection::kSaDE_ss:
					evolve_.EvolveDE();
					break;
				default:
					std::cout << "Unavailable de_strategies_selection_pattern_ setting. Please check." << std::endl;
					exit(0);
				}
			} else {
				std::cout << "num_of_strategies_ is less than 1, please check." << std::endl;
				exit(0);
			}
		}

		void ProcessController::AfterEvolution() {

		}

		void ProcessController::BeforeSelection() {
			if (ProcessController::lv_.ev_.GetDE_NumOfStrategies() >= 2) {
				switch (ProcessController::lv_.ev_.GetDE_StrategiesSelectionPattern()) {
				case corematerial::StrategiesSelection::kSaDE_ss:
					if (ProcessController::debug_)
						std::cout << "BeforeSelectSaDE_StrategiesSelection" << std::endl;
					ProcessController::select_.BeforeSelectSaDE_StrategiesSelection();
					break;
				}
			}
		}

		void ProcessController::Selection() {
			const corematerial::Selection s = ProcessController::lv_.ev_.GetDE_SelectionPattern();
			//
			// No metter which selection method is using here, individuals must record who is its parent.
			// Not allow any free or delete during selecton, always deallocates in AfterSelection().
			//
			if (s == corematerial::Selection::kCompetition) {
				if (ProcessController::debug_)
					std::cout << "SelectDE" << std::endl;
				select_.SelectDE();
			}
		}

		void ProcessController::AfterSelection() {
			// strategies selection
			if (ProcessController::lv_.ev_.GetDE_NumOfStrategies() >= 2) {
				switch (ProcessController::lv_.ev_.GetDE_StrategiesSelectionPattern()) {
				case corematerial::StrategiesSelection::kSaDE_ss:
					if (ProcessController::debug_)
						std::cout << "AfterSelectSaDE_SuccessStrategiesSelection" << std::endl;
					if (ProcessController::debug_)
						std::cout << "AfterSelectSaDE_FailStrategiesSelection" << std::endl;
					ProcessController::select_.AfterSelectSaDE_SuccessStrategiesSelection();
					ProcessController::select_.AfterSelectSaDE_FailStrategiesSelection();
					break;
				}
			}

			// parameter control CR
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kCR) == corematerial::ParametersControl::kCR) {
				// memory CR
				if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kMemoryCR) == corematerial::ParametersControlMethod::kMemoryCR) {
					switch (ProcessController::lv_.ev_.GetDE_MemoryCR_Pattern()) {
					case corematerial::MemoryCR::kSaDE_CR:
						if (ProcessController::debug_)
							std::cout << "AfterSelectSaDE_SuccessMemoryCR" << std::endl;
						ProcessController::select_.AfterSelectSaDE_SuccessMemoryCR();
						break;
					case corematerial::MemoryCR::kSHADE_CR:
						ProcessController::select_.AfterSelectSHADE_SuccessMemoryCR();
						break;
					default:
						printf("Unknown memory CR pattern.");
						exit(0);
					}
				}
			}

			// parameter control F
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kF) == corematerial::ParametersControl::kF) {
				if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kMemoryF) == corematerial::ParametersControlMethod::kMemoryF) {
					switch (ProcessController::lv_.ev_.GetDE_MemoryF_Pattern()) {
					case corematerial::MemoryF::kSHADE_F:
						ProcessController::select_.AfterSelectSHADE_SuccessMemoryF();
						break;
					default:
						printf("Unknown memory F pattern.");
						exit(0);
					}
				}
			}

			// archive
			if ((ProcessController::lv_.ev_.GetDE_Memory_Pattern() & corematerial::Memory::kArchive) == corematerial::Memory::kArchive) {
				switch (ProcessController::lv_.ev_.GetDE_ArchivePattern()) {
				case(corematerial::Archive::kSHADE_Archive):
					ProcessController::select_.AfterSelectSHADE_SuccessArchive();
					break;
				default:
					printf("Unknown archive pattern.");
					exit(0);
				}
			}

			// np_rank
			if ((ProcessController::lv_.ev_.GetDE_Memory_Pattern() & corematerial::Memory::kNPRank) == corematerial::Memory::kNPRank) {
				memory_.SortNP_Rank();
			}

			corematerial::Selection s = ProcessController::lv_.ev_.GetDE_SelectionPattern();
			if (s == corematerial::Selection::kCompetition) {
				if (ProcessController::debug_)
					std::cout << "AfterSelectDE" << std::endl;
				select_.AfterSelectDE(); // Clear all the individual in next_generation_.
			}
		}

		void ProcessController::NextGen() {
			ProcessController::de_.NextGen();
			ProcessController::sade_.NextGen();
			ProcessController::shade_.NextGen();
		}

		bool ProcessController::ReachStopCriterion() {
			const corematerial::StopCriterion sc = ProcessController::lv_.ev_.GetStopCriterionPattern();
			if ((sc & corematerial::StopCriterion::kMaxFE) == corematerial::StopCriterion::kMaxFE) {
				if (ProcessController::lv_.now_ffe_ >= ProcessController::lv_.ev_.GetDE_MaxFE()) {
					return true;
				}
			}
			if ((sc & corematerial::StopCriterion::kMaxGeneration) == corematerial::StopCriterion::kMaxGeneration) {
				if (ProcessController::lv_.now_gen_ >= ProcessController::lv_.ev_.GetDE_MaxGen()) {
					return true;
				}
			}
			if ((sc & corematerial::StopCriterion::kReachOptimal) == corematerial::StopCriterion::kReachOptimal) {
				if (ProcessController::lv_.now_best_ <= ProcessController::lv_.ev_.GetDE_Optimal_()) {
					return true;
				}
			}
			if (sc  == corematerial::StopCriterion::UNSET) {
				std::cout << "Unset Stop criterion." << std::endl;
				exit(0);
			}
			return false;
		}

		void ProcessController::RecycleMemory() {
			// initial
			switch (ProcessController::lv_.ev_.GetDE_InitialPopulationPattern()) {
			case corematerial::InitialPopulation::kRandom:
				ProcessController::memory_.RecycleDE_Fitness();
				break;
			case corematerial::InitialPopulation::kLHD:
				break;
			}
			// NP Rank
			if ((ProcessController::lv_.ev_.GetDE_Memory_Pattern() & corematerial::Memory::kNPRank) == corematerial::Memory::kNPRank) {
				ProcessController::memory_.RecycleNP_Rank();
			}
			// strategies selection
			if (ProcessController::lv_.ev_.GetDE_NumOfStrategies() >= 2) {
				switch (ProcessController::lv_.ev_.GetDE_StrategiesSelectionPattern()) {
				case corematerial::StrategiesSelection::kSaDE_ss:
					ProcessController::memory_.RecycleSaDE_StrategiesSelection();
					break;
				}
			}
			// parameter control CR
			if ((ProcessController::lv_.ev_.GetParametersControlPattern() & corematerial::ParametersControl::kCR) == corematerial::ParametersControl::kCR) {
				if ((ProcessController::lv_.ev_.GetParametersControlMethodPattern() & corematerial::ParametersControlMethod::kMemoryCR) == corematerial::ParametersControlMethod::kMemoryCR) {
					// Memory CR
					switch (ProcessController::lv_.ev_.GetDE_MemoryCR_Pattern()) {
					case corematerial::MemoryCR::kSaDE_CR:
						if ((ProcessController::lv_.ev_.GetDE_MemoryCR_SettingPattern() & corematerial::MemoryCR_Setting::kMemoryByEachStrategy) == corematerial::MemoryCR_Setting::kMemoryByEachStrategy) {
							ProcessController::parameter_control_.DemallocSaDE_MemoryCR(ProcessController::lv_.ev_.GetDE_NumOfStrategies());
						} else {
							ProcessController::parameter_control_.DemallocSaDE_MemoryCR(1);
						}
						break;
					case corematerial::MemoryCR::kSHADE_CR:

						break;
					}
				}
			}

			// shade
			ProcessController::shade_.RecycleMemory();
		}
	}
}