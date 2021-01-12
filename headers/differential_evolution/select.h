#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_SELECT_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_SELECT_H_

#include "behavior.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		class Select : public Behavior
		{
		public:
			Select();
			~Select();
			void SelectDE();
			void AfterSelectDE();
			void BeforeSelectSaDE_StrategiesSelection();
			void AfterSelectSaDE_SuccessStrategiesSelection();
			void AfterSelectSaDE_FailStrategiesSelection();
			void AfterSelectSaDE_SuccessMemoryCR();
			
			void AfterSelectSHADE_SuccessMemoryCR();
			void AfterSelectSHADE_SuccessMemoryF();
			void AfterSelectSHADE_SuccessArchive();
		private:
			static inline void SelectionError(std::string func_name, std::string error_variable) {
				std::cout << "Cannnot execute\"" << func_name << "\". Please check: " << error_variable << std::endl;
				exit(0);
			}
		};
	}
}
#endif // !EA_HEADERS_DIFFERENTIAL_EVOLUTION_SELECT_H_
