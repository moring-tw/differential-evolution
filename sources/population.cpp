#include"../headers/population.h"

namespace evolutionalgorithm {
	Population::Population() {

	}

	Population::~Population() {
		//
		//for each allocation, there has to be a deallocation 
		//what was allocated using new should be freed using delete, using new[] should be deallocated using delete[] and using malloc should be deallocated using free
		//
		for (unsigned i = 0; i < Population::np_; ++i) {
			delete& (*population_[i]);
			population_[i] = nullptr;
		}
		delete population_;
		population_ = nullptr;
	}

	void Population::Initial(size_t np, size_t dim) {
		if (Population::is_initialed_) {
			for (size_t i = 0; i < Population::np_; ++i) {
				//
				// this loop should be executed before new np being assigned to Population::np_
				// because the new np may different from old np. this will cause memory leak.
				//
				delete population_[i];
				population_[i] = nullptr;
			}
			delete[] population_;
			population_ = nullptr;
		}
		Population::np_ = np;
		Population::population_ = new Individual * [np];
		for (size_t np_counter = 0; np_counter < np; ++np_counter) {
			population_[np_counter] = new Individual(dim);
		}
		if (!Population::is_initialed_)
			Population::is_initialed_ = true;
	}

	//
	//this function won't malloc individual's dimension
	//using this function should assign "double*" to each individual as dimension
	//or will appear undefined behavior cause program crash.
	//
	void Population::Initial(size_t np) {
		if (Population::is_initialed_) {
			for (size_t i = 0; i < Population::np_; ++i) {
				delete population_[i];
				population_[i] = nullptr;
			}
			delete[] population_;
			population_ = nullptr;
		}
		Population::np_ = np;
		Population::population_ = new Individual * [np];
		for (size_t np_counter = 0; np_counter < np; ++np_counter) {
			population_[np_counter] = new Individual();
		}
		if (!Population::is_initialed_)
			Population::is_initialed_ = true;
	}
}