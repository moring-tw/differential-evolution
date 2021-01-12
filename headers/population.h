#pragma once
#ifndef EA_HEADERS_POPULATION_H_
#define EA_HEADERS_POPULATION_H_

#include <stdlib.h>

#include "individual.h"
#include "corematerial.h"

namespace evolutionalgorithm {
	//extern unsigned int ExecutiveVariables::de_initial_pattern_;
	class Population
	{
	public:
		Population();
		virtual ~Population();
		Individual& operator[](unsigned i_index) {
			return (*population_[i_index]);
		}

		friend bool operator!=(const Population& p, const Individual **ptr) {
			return !(p.population_ == ptr);
		}

		friend bool operator==(const Population& p, const Individual** ptr) {
			return (p.population_ == ptr);
		}

		void Initial(size_t);
		void Initial(size_t, size_t);
	protected:
		Individual** population_ = nullptr;
	private:
		bool is_initialed_ = false;
		unsigned np_ = 0;
	};
}
#endif // !EA_HEADERS_POPULATION_H_
