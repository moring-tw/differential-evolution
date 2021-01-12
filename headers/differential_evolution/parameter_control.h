#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_PARAMETER_CONTROL_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_PARAMETER_CONTROL_H_

#include "behavior.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		class ParameterControl :public Behavior{
		public:
			ParameterControl();
			virtual ~ParameterControl();
			void InitialDE_CR();
			void InitialDE_F();
			void InitialDE_K();
			void InitialDE_P();
			void MallocSaDE_MemoryCR(const size_t);
			void DemallocSaDE_MemoryCR(const size_t);
			void InitialSaDE_MemoryCR(const size_t);

			void MallocSHADE_MemoryCR();
			void InitialSHADE_MemoryCR();
			void MallocSHADE_MemoryF();
			void InitialSHADE_MemoryF();
		private:
			static inline void ParameterControlNotInitialedError(std::string failed_var, std::string var_name) {
				std::cout << "Failed to initial/malloc " << failed_var << ", due to " << var_name << " haven't been initialed." << std::endl;
				exit(0);
			};
			static inline void ParameterControlDemallocError(std::string failed_var, std::string var_name) {
				std::cout << "Failed to demalloc " << failed_var << "due to " << var_name << " has illegal value." << std::endl;
				exit(0);
			}
		};
	}
}
#endif