#include "../headers/readconfig.h"
namespace evolutionalgorithm {
	template <typename T>
	std::vector<std::string> SplitString(std::string&, T&);

	const std::map<std::string, ReadConfig::ParseTerms> ReadConfig::kParseTermsMap = {
		{"[algorithm]", ParseTerms::algorithm},
		{"[debug]", ParseTerms::debug},
		{"[population]", ParseTerms::population},
		{"[mutant and crossover]", ParseTerms::mutant_and_crossover},
		{"[memory]", ParseTerms::memory},
		{"[selection]", ParseTerms::selection},
		{"[out bound handler]", ParseTerms::out_bound_handler},
		{"[stop criterion]", ParseTerms::stop_criterion},
		{"[parameters]", ParseTerms::parameters},
		{"[memory CR]", ParseTerms::memory_CR},
		{"[memory F]", ParseTerms::memory_F},
		{"[strategies selection]", ParseTerms::strategies_selection},
		{"[parameters control method]", ParseTerms::parameters_control_method},
		{"[selection]", ParseTerms::selection},
		{"[memory CR setting]", ParseTerms::memory_CR_setting},
		{"[archive]", ParseTerms::archive},
		{"[parameters control]", ParseTerms::parameters_control}
	};

	const std::map<std::string, ReadConfig::ParametersName> ReadConfig::kParametersNameMap = {
		{"de_CR_", ParametersName::de_CR_},
		{"de_F_", ParametersName::de_F_},
		{"de_K_", ParametersName::de_K_},
		{"de_np_", ParametersName::de_np_},
		{"de_next_gen_np_", ParametersName::de_next_gen_np_},
		{"de_dim_", ParametersName::de_dim_},
		{"bound_min_", ParametersName::bound_min_},
		{"bound_max_", ParametersName::bound_max_},
		{"shade_H_", ParametersName::shade_H_},
		{"de_P_", ParametersName::de_P_},
		{"sade_LP_", ParametersName::sade_LP_},
		{"max_fe_", ParametersName::max_fe_},
		{"max_gen_", ParametersName::max_gen_},
		{"optimal_", ParametersName::optimal_},
		{"sade_epsilion_", ParametersName::sade_epsilion_},
		{"normal_F_mean_", ParametersName::normal_F_mean_},
		{"normal_F_stddev_", ParametersName::normal_F_stddev_},
		{"random_P_max_scale_", ParametersName::random_P_max_scale_},
		{"random_P_min_", ParametersName::random_P_min_},
		{"archive_size_", ParametersName::archive_size_},
		{"problem_amount_", ParametersName::problem_amount_},
		{"problem_set_", ParametersName::problem_set_}
	};

	ReadConfig::ReadConfig() {
		storage_point_ = nullptr;
		config_file_ = kDefaultConfigFile;
	}

	ReadConfig::~ReadConfig() {

	}

	void ReadConfig::SetConfigFile(std::string file_path) {
		struct stat buf;
		if (stat(file_path.c_str(), &buf) != -1) {
			config_file_ = file_path;
		} else {
			std::cout << "Assigned file doesn't exist. Using default file: " << kDefaultConfigFile << std::endl;
			config_file_ = kDefaultConfigFile;
		}
	}

	void ReadConfig::SetConfigFile(std::istream& stream) {
		std::string file_path;
		stream >> file_path;
		struct stat buf;
		if (stat(file_path.c_str(), &buf) != -1) {
			config_file_ = file_path;
		} else {
			std::cout << "Assigned file doesn't exist. Using default file: " << kDefaultConfigFile << std::endl;
			config_file_ = kDefaultConfigFile;
		}
	}

	void ReadConfig::SetVariablesStoragePoint(Variables& storage_point) {
		storage_point_ = &storage_point;
	}

	void ReadConfig::NextRun(Variables& storage_point) {
		storage_point_ = &storage_point;
		SettingConfig();
		ImplicitHandler();
		DefaultCheck();
	}

	void ReadConfig::NextRun(Variables& storage_point, std::string file_path) {
		SetConfigFile(file_path);
		storage_point_ = &storage_point;
		SettingConfig();
		ImplicitHandler();
		DefaultCheck();
	}

	void ReadConfig::SettingConfig() {
		config_.open(config_file_, std::ios::in);
		while (!config_) {
			std::cout << "loss config file" << std::endl << "Please enter new config file:";
			SetConfigFile(std::cin);
			config_.open(config_file_, std::ios::in);
		}
		if (storage_point_ == nullptr) {
			std::cout << "Before parsing, storage_point_ must be passed by reference." << std::endl;
			exit(0);
		}
		storage_point_->ReInitialGlobalVariable();

		ParseTerms parse_mode = ParseTerms::undefine_parse;
		while (!config_.eof() && config_.is_open()) {
			std::getline(config_, one_line_);
			++line_counter_;
			Debug(one_line_, line_counter_);
			//
			// For one file only one place can get line before it being closed
			// then assign to appropriate function to handle it
			//
			if (one_line_[0] == '/' && one_line_[1] == '/') continue;
			if (one_line_[0] == '[') {
				std::map<std::string, ParseTerms>::const_iterator it = kParseTermsMap.find(one_line_);
				if (it != kParseTermsMap.end()) {
					parse_mode = it->second;
				} else {
					std::cout << "can't parse term:" << one_line_ << ". Please check "<< config_file_ <<" file." << std::endl;
					exit(0);
				}
				continue; // if first character is '[' means that this line is just section changing which doesn't need to parse.
			}
			RemoveSpace(one_line_);
			if (one_line_.compare("\0") == 0) {
				continue; // Ignore the line doesn't has any chatacter.
			}
			//
			// Assign to appropricate function to handle it.
			//
			switch (parse_mode) {
			case ParseTerms::algorithm:
				ParseAlgorithm();
				break;
			case ParseTerms::debug:
				ParseDebug();
				break;
			case ParseTerms::population:
				ParsePopulation();
				break;
			case ParseTerms::mutant_and_crossover:
				ParseMutantAndCrossover();
				break;
			case ParseTerms::memory:
				ParseMemory();
				break;
			case ParseTerms::selection:
				ParseSelection();
				break;
			case ParseTerms::out_bound_handler:
				ParseOutBoundHandler();
				break;
			case ParseTerms::stop_criterion:
				ParseStopCriterion();
				break;
			case ParseTerms::parameters:
				ParseParameters();
				break;
			case ParseTerms::memory_CR:
				ParseMemoryCR();
				break;
			case ParseTerms::memory_F:
				ParseMemoryF();
				break;
			case ParseTerms::strategies_selection:
				ParseStrategiesSelection();
				break;
			case ParseTerms::parameters_control_method:
				ParseParametersMethodControl();
				break;
			case ParseTerms::memory_CR_setting:
				ParseMemoryCR_Setting();
				break;
			case ParseTerms::archive:
				ParseArchive();
				break;
			case ParseTerms::parameters_control:
				ParseParametersControl();
				break;
			default:
				std::cout << "Can't understand " << one_line_ << " on line: " << line_counter_ << ". Please check setup.config file." << std::endl;
				exit(0);
			}
		}
	}

	void ReadConfig::ParseAlgorithm() {
		ParseOnlyOne(one_line_, line_counter_, corematerial::kAlgorithmMap, storage_point_->de_algorithm_pattern_);
	}

	void ReadConfig::ParseDebug() {
		ParseMultiStat(one_line_, line_counter_, corematerial::kDebugMap, storage_point_->debug_pattern_);
	}

	void ReadConfig::ParsePopulation() {
		ParseOnlyOne(one_line_, line_counter_, corematerial::kInitialPopulationMap, storage_point_->de_initial_pattern_);
	}

	void ReadConfig::ParseMutantAndCrossover() {
		ParseMultiStat(one_line_, line_counter_, corematerial::kMutantAndCrossoverMap, storage_point_->de_mutant_and_crossover_pattern_);
	}

	void ReadConfig::ParseStrategiesSelection() {
		ParseOnlyOne(one_line_, line_counter_, corematerial::kStrategiesSelectionMap, storage_point_->de_strategies_selection_pattern_);
	}

	void ReadConfig::ParseMemory() {
		ParseMultiStat(one_line_, line_counter_, corematerial::kMemoryMap, storage_point_->de_memory_pattern_);
	}

	void ReadConfig::ParseArchive() {
		ParseOnlyOne(one_line_, line_counter_, corematerial::kArchiveMap, storage_point_->de_archive_pattern_);
	}

	void ReadConfig::ParseMemoryCR() {
		ParseOnlyOne(one_line_, line_counter_, corematerial::kMemoryCRMap, storage_point_->de_memory_CR_pattern_);
	}

	void ReadConfig::ParseMemoryCR_Setting() {
		ParseMultiStat(one_line_, line_counter_, corematerial::kMemoryCR_SettingMap, storage_point_->de_memory_CR_setting_pattern_);
	}

	void ReadConfig::ParseMemoryF() {
		ParseOnlyOne(one_line_, line_counter_, corematerial::kMemoryFMap, storage_point_->de_memory_F_pattern_);
	}

	void ReadConfig::ParseParametersMethodControl() {
		ParseMultiStat(one_line_, line_counter_, corematerial::kParametersControlMethodMap, storage_point_->parameters_control_method_pattern_);
	}

	void ReadConfig::ParseSelection() {
		ParseOnlyOne(one_line_, line_counter_, corematerial::kSelectionMap, storage_point_->de_selection_pattern_);
	}

	void ReadConfig::ParseOutBoundHandler() {
		ParseOnlyOne<corematerial::OutBoundHandler>(one_line_, line_counter_, corematerial::kOutBoundHandlerMap, storage_point_->de_out_bound_handler_pattern_);
	}

	void ReadConfig::ParseStopCriterion() {
		ParseMultiStat(one_line_, line_counter_, corematerial::kStopCriterionMap, storage_point_->de_stop_criterion_pattern_);
	}

	void ReadConfig::ParseParametersControl() {
		ParseMultiStat(one_line_, line_counter_, corematerial::kParametersControlMap, storage_point_->parameters_control_pattern_);
	}

	void ReadConfig::ParseParameters() {
		std::string setting_term = GetTerm(one_line_, line_counter_);
		std::map<std::string, ParametersName>::const_iterator it = kParametersNameMap.find(setting_term);
		if (it != kParametersNameMap.end()) {
			std::string setting_stat = GetStat(one_line_, line_counter_);
			switch (it->second) {
			case ParametersName::de_CR_:
				storage_point_->de_CR_ = LargerThanOrEqualToZero<double>(setting_stat, line_counter_);
				std::cout << "CR:" << storage_point_->de_CR_ << std::endl;
				break;
			case ParametersName::de_F_:
				storage_point_->de_F_ = LargerThanOrEqualToZero<double>(setting_stat, line_counter_);
				std::cout << storage_point_->de_F_ << std::endl;
				break;
			case ParametersName::de_K_:
				storage_point_->de_K_ = LargerThanOrEqualToZero<double>(setting_stat, line_counter_);
				std::cout << storage_point_->de_K_ << std::endl;
				break;
			case ParametersName::de_np_:
				storage_point_->de_NP_ = LargerThanZero<size_t>(setting_stat, line_counter_);
				std::cout << storage_point_->de_NP_ << std::endl;
				break;
			case ParametersName::de_next_gen_np_:
				storage_point_->de_next_gen_NP_ = LargerThanZero<size_t>(setting_stat, line_counter_);
				std::cout << "next_gen_np_:" << storage_point_->de_next_gen_NP_ << std::endl;
				break;
			case ParametersName::de_dim_:
				storage_point_->de_dim_ = LargerThanZero<size_t>(setting_stat, line_counter_);
				std::cout << storage_point_->de_dim_ << std::endl;
				break;
			case ParametersName::bound_min_:
				std::cout << "MIN::...";
				ParseArray(setting_stat, ArrayChooser::bound_min);
				std::cout << "DONE" << std::endl;
				break;
			case ParametersName::bound_max_:
				std::cout << "MAX::...";
				ParseArray(setting_stat, ArrayChooser::bound_max);
				std::cout << "DONE" << std::endl;
				break;
			case ParametersName::shade_H_:
				storage_point_->shade_H_ = LargerThanOrEqualToZero<int>(setting_stat, line_counter_);
				std::cout << storage_point_->shade_H_ << std::endl;
				break;
			case ParametersName::de_P_:
				storage_point_->de_P_ = LargerThanOrEqualToZero<double>(setting_stat, line_counter_);
				std::cout << storage_point_->de_P_ << std::endl;
				break;
			case ParametersName::sade_LP_:
				storage_point_->sade_LP_ = LargerThanZero<int>(setting_stat, line_counter_);
				std::cout << storage_point_->sade_LP_ << std::endl;
				break;
			case ParametersName::max_fe_:
				storage_point_->max_fe_ = LargerThanOrEqualToZero<int>(setting_stat, line_counter_);
				std::cout << storage_point_->max_fe_ << std::endl;
				break;
			case ParametersName::max_gen_:
				storage_point_->max_gen_ = LargerThanOrEqualToZero<int>(setting_stat, line_counter_);
				std::cout << storage_point_->max_gen_ << std::endl;
				break;
			case ParametersName::optimal_:
				storage_point_->optimal_ = stod(setting_stat);
				std::cout << storage_point_->optimal_ << std::endl;
				break;
			case ParametersName::sade_epsilion_:
				storage_point_->sade_epsilion_ = LargerThanZero<double>(setting_stat, line_counter_);
				std::cout << "epsilion :" << storage_point_->sade_epsilion_ << std::endl;
				break;
			case ParametersName::normal_F_mean_:
				storage_point_->normal_F_mean_ = stod(setting_stat);
				std::cout << "normal_F_mean_:" << storage_point_->normal_F_mean_ << std::endl;
				break;
			case ParametersName::normal_F_stddev_:
				storage_point_->normal_F_stddev_ = stod(setting_stat);
				std::cout << "normal_F_stddev_:" << storage_point_->normal_F_stddev_ << std::endl;
				break;
			case ParametersName::random_P_max_scale_:
				storage_point_->random_P_max_scale_ = LargerThanZero<double>(setting_stat, line_counter_);
				std::cout << "random_P_max_scale_:" << storage_point_->random_P_max_scale_ << std::endl;
				break;
			case ParametersName::random_P_min_:
				storage_point_->random_P_min_ = LargerThanZero<int>(setting_stat, line_counter_);
				std::cout << "random_P_min_:" << storage_point_->random_P_min_ << std::endl;
				break;
			case ParametersName::archive_size_:
				storage_point_->archive_size_ = LargerThanOrEqualToZero<int>(setting_stat, line_counter_);
				std::cout << "archive_size_:" << storage_point_->archive_size_ << std::endl;
				break;
			case ParametersName::problem_amount_:
				storage_point_->problem_amount_ = LargerThanZero<int>(setting_stat, line_counter_);
				std::cout << "problem_amount_:" << storage_point_->problem_amount_ << std::endl;
				break;
			case ParametersName::problem_set_:
				ParseArray(setting_stat, ArrayChooser::problem);
				break;
			}
		} else WarningMessage(one_line_, line_counter_);
	}

	void ReadConfig::ParseArray(std::string& stat, int chooser) {
		bool* checker = NULL;
		if (chooser == ArrayChooser::bound_min) {
			ReadConfig::MallocAndInitialBound(&storage_point_->bound_min_, &checker, storage_point_->de_dim_);
		} else if (chooser == ArrayChooser::bound_max) {
			ReadConfig::MallocAndInitialBound(&storage_point_->bound_max_, &checker, storage_point_->de_dim_);
		} else if (chooser == ArrayChooser::problem) {
			if (storage_point_->problem_amount_ > 0) {
				storage_point_->problem_set_ = (bool*)malloc(sizeof(bool) * storage_point_->problem_amount_);
				if (storage_point_->problem_set_ == NULL) {
					std::cout << "problem_set_ occured some unknown error when malloc, this may cause by problem_amount_ haven't been set or it should be larger than ZERO. On line: " << line_counter_ << std::endl;
					exit(0);
				}
				std::fill(storage_point_->problem_set_, storage_point_->problem_set_ + storage_point_->problem_amount_, false);
			} else {
			}
		} else {
			std::cout << "Unknown array to parse. On line: " << line_counter_ << "." << std::endl;
			exit(0);
		}

		std::string dlim = ",";
		std::vector<std::string> v = SplitString(stat, dlim);
		std::vector<std::string>::iterator it = v.begin();
		std::vector<std::string> dim_and_value;
		std::vector<std::string> lower_and_upper_dim;
		unsigned lower_dim, upper_dim;
		while (it != v.end()) {
			dim_and_value = SplitString(*it, dlim = "=");
			std::string dims = GetStat(dim_and_value[0], line_counter_);
			lower_and_upper_dim = SplitString(dims, dlim = ":");
			lower_dim = std::stoi(lower_and_upper_dim[0]);
			upper_dim = std::stoi(lower_and_upper_dim[1]);
			if (chooser == ArrayChooser::bound_min || chooser == ArrayChooser::bound_max) {
				if (lower_dim >= storage_point_->de_dim_ || upper_dim >= storage_point_->de_dim_) {
					std::cout << "[X:Y]=Z, X and Y must less than de_dim_. On line:" << line_counter_ << std::endl;
					exit(0);
				}
			}
			if (lower_dim > upper_dim) {
				std::cout << "[X:Y]=Z, X must less than or equal to Y. On line: " << line_counter_ << std::endl;
				exit(0);
			}
			for (unsigned dim_counter = lower_dim; dim_counter <= upper_dim; ++dim_counter) {
				if (chooser == ArrayChooser::bound_min) {
					storage_point_->bound_min_[dim_counter] = std::stod(dim_and_value[1]);
					checker[dim_counter] = true;
				} else if (chooser == ArrayChooser::bound_max) {
					storage_point_->bound_max_[dim_counter] = std::stod(dim_and_value[1]);
					checker[dim_counter] = true;
				} else if (chooser == ArrayChooser::problem) {
					storage_point_->problem_set_[dim_counter] = std::stoi(dim_and_value[1]) == 1 ? true : false;
				}
			}
			++it;
		}
		if (chooser == ArrayChooser::bound_min || chooser == ArrayChooser::bound_max) {
			bool die = false;
			for (unsigned dim_counter = 0; dim_counter < storage_point_->de_dim_; ++dim_counter) {
				if (!checker[dim_counter]) {
					if (chooser == ArrayChooser::bound_min) {
						std::cout << "Unable to find bound_min_[" << dim_counter << "] in file:" << config_file_ << "." << std::endl;
					} else if (chooser == ArrayChooser::bound_max) {
						std::cout << "Unable to find bound_max_[" << dim_counter << "] in file:" << config_file_ << "." << std::endl;
					}
					die = true;
				}
			}
			if (die) exit(0);
		}
	}

	void ReadConfig::ImplicitHandler() {
		//calculate using how much strategies
		corematerial::MutantAndCrossover now_strategy = static_cast<corematerial::MutantAndCrossover>(0);
		corematerial::MutantAndCrossover compare_strategies = static_cast<corematerial::MutantAndCrossover>(0);
		//initial now_strategy = 0x00, compare_strategies = 0x00;
		while ((compare_strategies & storage_point_->de_mutant_and_crossover_pattern_) != storage_point_->de_mutant_and_crossover_pattern_) {
			++storage_point_->de_num_of_strategies_;
			do {
				if (now_strategy != corematerial::MutantAndCrossover::UNSET) {
					now_strategy <<= 1;
				} else {
					now_strategy = static_cast<corematerial::MutantAndCrossover>(0x01);
					//
					// Make sure that now_strategy be assigned as variables of which value is 0x01.
					// Or this will cause counting error.
					//
				}
			} while ((now_strategy & storage_point_->de_mutant_and_crossover_pattern_) == corematerial::MutantAndCrossover::UNSET);
			storage_point_->strategy_index_.insert(std::pair<corematerial::MutantAndCrossover, size_t>(now_strategy, (storage_point_->de_num_of_strategies_ - 1)));
			std::cout << "strategy index: "<< (storage_point_->de_num_of_strategies_ - 1) << "\tstrategy code: " << static_cast<size_t>(now_strategy) << std::endl;
			compare_strategies += now_strategy;
		}

		if ((storage_point_->de_mutant_and_crossover_pattern_ & corematerial::MutantAndCrossover::kCurToPBest) == corematerial::MutantAndCrossover::kCurToPBest) {
			// Cur-to_PBest must using NP Rank
			if ((storage_point_->de_memory_pattern_ & corematerial::Memory::kNPRank) != corematerial::Memory::kNPRank) {
				storage_point_->de_memory_pattern_ += corematerial::Memory::kNPRank;
			}
		}
		if ((storage_point_->parameters_control_method_pattern_ & corematerial::ParametersControlMethod::kArchiveSizeEqualNP) == corematerial::ParametersControlMethod::kArchiveSizeEqualNP) {
			storage_point_->archive_size_ = storage_point_->de_NP_;
		}
	}

	void ReadConfig::DefaultCheck() {
		// default using kRand
		if (storage_point_->de_mutant_and_crossover_pattern_ == corematerial::MutantAndCrossover::UNSET) {
			storage_point_->de_mutant_and_crossover_pattern_ = corematerial::MutantAndCrossover::kRand;
		}
	}

	template <typename T>
	std::vector<std::string> SplitString(std::string& t, T& dlim) {
		size_t pos, last = 0;
		std::vector<std::string> v;
		while ((pos = t.find(dlim, last)) != std::string::npos) {
			v.push_back(t.substr(last, pos - last));
			last = pos + 1;
		}
		v.push_back(t.substr(last));
		return v;
	}
}