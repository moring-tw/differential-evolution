#pragma once
#ifndef EA_HEADERS_INDIVIDUAL_H_
#define EA_HEADERS_INDIVIDUAL_H_

#include <vector>
#include <iostream>

#include "corematerial.h"

namespace evolutionalgorithm {
	class Individual {
	public:
		Individual();
		Individual(size_t);
		virtual ~Individual();
		double& operator[](int d_index) {
			return dimensions_[d_index];
		}

		void operator=(double* dimensions) {
			dimensions_ = dimensions;
		}

		double* GetDimensions();
		void InitialComparisonResult();
		void SetCR(const double);
		void SetF(const double);
		void SetK(const double);
		void SetP(const double);
		void SetComparedParent(const size_t);
		double GetCR();
		double GetF();
		double GetK();
		double GetP();
		size_t GetComparedParent();
		void ShowPath();
		corematerial::MutantAndCrossover use_strategy_ = corematerial::MutantAndCrossover::UNSET;
		size_t use_strategy_index_ = 0;
		int number_of_unimproved_times_ = 0;
		std::vector<std::vector<unsigned>> record_path_;
		bool is_out_ = false;
		bool is_equal_ = false;
		bool is_less_ = false;
		bool is_larger_ = false;
	private:
		unsigned dim_ = 0;
		double* dimensions_ = 0;
		double use_CR_ = 0, use_F_ = 0, use_K_ = 0, use_P_ = 0;
		size_t compared_parent_ = 0; // Records which one parent is compared to this individual.
	};
}

#endif // !EA_HEADERS_INDIVIDUAL_H_
