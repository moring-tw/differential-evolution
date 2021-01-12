#pragma once
#ifndef EA_HEADERS_READCONFIG_H_
#define EA_HEADERS_READCONFIG_H_

#include <string.h>
#include <sys/stat.h>

#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

#include "corematerial.h"
#include "publicfunction.h"
#include "variables.h"



namespace evolutionalgorithm {
	class ReadConfig {
	public:
		ReadConfig();
		virtual ~ReadConfig();
		void SetConfigFile(std::string);
		void SetConfigFile(std::istream&);
		void SetVariablesStoragePoint(Variables&);
		void NextRun(Variables&);
		void NextRun(Variables& ,std::string);
	protected:
		void SettingConfig();
	private:
		std::ifstream config_;
		std::string config_file_;
		Variables* storage_point_;
		const std::string kDefaultConfigFile = "setup.cfg";
		std::string one_line_;
		unsigned line_counter_ = 0;
		enum class ParseTerms : int{
			undefine_parse,algorithm, debug, population, mutant_and_crossover, memory, selection, out_bound_handler, stop_criterion, parameters, memory_CR, memory_F,
			strategies_selection, parameters_control_method, memory_CR_setting, archive, parameters_control
		};
		static const std::map<std::string, ParseTerms> kParseTermsMap;

		inline void Debug(std::string& t, unsigned line_counter) {
			if ((storage_point_->debug_pattern_ & corematerial::Debug::kReadConfig) == corematerial::Debug::kReadConfig) {
				std::cout << "[" << line_counter << "]:" << t << std::endl;
			}
		}

		static inline void RemoveSpace(std::string& t) {
			t.erase(std::remove_if(t.begin(), t.end(), isspace), t.end());
		}

		static inline std::string GetTerm(std::string& t, unsigned line_counter) {
			unsigned pos = t.find('=');
			if (pos != std::string::npos) {
				return t.substr(0, pos);
			} else {
				std::cout << "error: can't find symbol \'=\' when parse config on line:" << line_counter << std::endl;
				std::cout << "line " << line_counter << ": " << t << std::endl;
				exit(2);
			}
		}

		static inline std::string GetStat(std::string& t, unsigned line_counter) {
			size_t start = t.find('['), endding = t.find_last_of(']');
			if (start != std::string::npos && endding != std::string::npos) {
				return t.substr(start + 1, endding - start - 1);
			} else {
				std::cout << "error: can't get stat on line:" << line_counter << std::endl;
				std::cout << "line " << line_counter << t << std::endl;
				exit(3);
			}
		}

		template <typename T>
		static inline T LargerThanZero(std::string& t, unsigned line_counter) {
			double d = std::stod(t);
			T temp;
			if ((temp = static_cast<T>(d)) <= 0) {
				std::cout << "de_dim_ must larger than ZERO on line:" << line_counter << "." << std::endl;
				exit(0);
			}
			return temp;
		}

		template <typename T>
		static inline T LargerThanOrEqualToZero(std::string& t, unsigned line_counter) {
			double d = std::stod(t);
			T temp;
			if ((temp = static_cast<T>(d)) < 0) {
				std::cout << "de_dim_ must larger than oe equal to ZERO on line:" << line_counter << "." << std::endl;
				exit(0);
			}
			return temp;
		}

		template <typename T>
		static inline void WarningMessage(T& t, unsigned line_counter) {
			std::cout << std::endl << "--------------------Runtime Warning!!!--------------------" << std::endl;
			std::cout << "Can't parse \"" << t << "\" on line [" << line_counter << "]. Please check the word's spelling." << std::endl << std::endl;
		}

		template <typename T>
		static inline void ParseOnlyOne(std::string& t, unsigned line_counter, const std::map<std::string, T>& m, T& global_variable) {
			std::string setting_stat = GetStat(t, line_counter);
			if (setting_stat.compare("true") == 0) {
				std::string setting_term = GetTerm(t, line_counter);
				auto it = m.find(setting_term);
				if (it != m.end()) {
					//*global_variable = PublicFunction::to_underlying(it->second);
					global_variable = it->second;
				} else {
					WarningMessage(setting_term, line_counter);
				}
			}
		}

		template <typename T>
		static inline void ParseMultiStat(std::string& t, unsigned line_counter, const std::map<std::string, T>& m, T& global_variable) {
			std::string setting_term = GetTerm(t, line_counter);
			auto it = m.find(setting_term);
			if (it != m.end()) {
				std::string setting_stat = GetStat(t, line_counter);
				if (setting_stat.compare("true") == 0) {
					if ((global_variable & it->second) != it->second) {
						global_variable += it->second;
					}
				} else {
					if ((global_variable & it->second) == it->second) {
						global_variable -= it->second;
					}
				}
			} else {
				WarningMessage(setting_term, line_counter);
			}
		}

		static inline void MallocAndInitialBound(double** bound, bool** check, unsigned dim) {
			if (dim == 0) {
				std::cout << "Before set bound, de_dim_ must be set already." << std::endl;
				exit(0);
			}
			(*bound) = (double*)malloc(sizeof(double) * dim);
			(*check) = (bool*)malloc(sizeof(bool) * dim);
			std::fill((*check), (*check) + dim, false);
		}
		void ParseAlgorithm();
		void ParseDebug();
		void ParsePopulation();
		void ParseMutantAndCrossover();
		void ParseStrategiesSelection();
		void ParseMemory();
		void ParseArchive();
		void ParseMemoryCR();
		void ParseMemoryCR_Setting();
		void ParseMemoryF();
		void ParseParametersMethodControl();
		void ParseSelection();
		void ParseOutBoundHandler();
		void ParseStopCriterion();
		void ParseParametersControl();
		enum class ParametersName {
			de_CR_, de_F_, de_K_, de_np_, de_dim_, bound_min_, bound_max_, shade_H_, de_P_, sade_LP_, max_fe_, max_gen_, optimal_, sade_epsilion_, normal_F_mean_, normal_F_stddev_,
			random_P_max_scale_, random_P_min_, archive_size_, problem_amount_, problem_set_, de_next_gen_np_
		};
		static const std::map<std::string, ParametersName> kParametersNameMap;
		void ParseParameters();
		void ParseArray(std::string&, int);
		enum ArrayChooser{bound_min,bound_max,problem};
		void ImplicitHandler();
		void DefaultCheck();
	};
} // namespace evolutionalgorithm
#endif // ! EA_HEADERS_READCONFIG_H_