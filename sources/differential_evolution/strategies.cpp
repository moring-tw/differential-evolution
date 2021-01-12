#include "../../headers/differential_evolution/strategies.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		Strategies::Strategies() {

		}

		Strategies::~Strategies() {
			Strategies::archive_ = nullptr;
		}

		void Strategies::SetArchive(Population* archive) {
			Strategies::archive_ = archive;
			Strategies::archive_is_set_ = true;
		}

		void Strategies::SetExecutiveVariables(ExecutiveVariables& ev) {
			Strategies::ev_ = &ev;
		}

		void Strategies::SetLocalVariables(LocalVariables& lv) {
			Strategies::lv_ = &lv;
		}

		void Strategies::ExecutiveVariablesCheck() {
			if (Strategies::ev_ == nullptr) {
				std::cout << "Before using any strategy, ev_(ExecutiveVariables) must be set already." << std::endl;
				exit(0);
			}
		}

		double* Strategies::DE_Rand(Population& population, size_t base_individual, unsigned number_of_vector_differences) {
			ExecutiveVariablesCheck();
			unsigned* individuals = PublicFunction::ShufflePopulation(Strategies::ev_->GetDE_NP(), base_individual, number_of_vector_differences * 2 + 1);
			const size_t dim = Strategies::ev_->GetDE_Dim();
			double* trail_individual = CreateTrailIndividual(dim);
			unsigned rnbr = PublicFunction::RandomInt(0, dim - 1);
			//const double CR = population[base_individual].GetCR();
			const double CR = Strategies::lv_->next_generation_[base_individual].GetCR();
			//const double F = population[base_individual].GetF();
			const double F = Strategies::lv_->next_generation_[base_individual].GetF();

			for (size_t dim_counter = 0; dim_counter < dim; ++dim_counter) {
				if (PublicFunction::RandomDouble(0, 1) < CR || dim_counter == rnbr) {
					trail_individual[dim_counter] = population[individuals[0]][dim_counter];
					for (unsigned vector_diff_counter = 0; vector_diff_counter < number_of_vector_differences; ++vector_diff_counter) {
						trail_individual[dim_counter] += F * (population[individuals[vector_diff_counter * 2 + 1]][dim_counter] - population[individuals[vector_diff_counter * 2 + 2]][dim_counter]);
					}
					if (IsOutBound(trail_individual[dim_counter], dim_counter)) {
						OutBoundHandler(population, base_individual, trail_individual, dim_counter);
					}
				} else {
					trail_individual[dim_counter] = population[base_individual][dim_counter];
				}
			}
			free(individuals);

			return trail_individual;
		}

		double* Strategies::DE_Best(Population& population, unsigned base_individual, unsigned best_individual, unsigned number_of_vector_differences) {
			ExecutiveVariablesCheck();
			unsigned* individuals = PublicFunction::ShufflePopulation(Strategies::ev_->GetDE_NP(), base_individual, number_of_vector_differences * 2);
			const size_t dim = Strategies::ev_->GetDE_Dim();
			double* trail_individual = CreateTrailIndividual(dim);
			unsigned rnbr = PublicFunction::RandomInt(0, dim - 1);
			//const double CR = population[base_individual].GetCR();
			const double CR = Strategies::lv_->next_generation_[base_individual].GetCR();
			//const double F = population[base_individual].GetF();
			const double F = Strategies::lv_->next_generation_[base_individual].GetF();

			for (size_t dim_counter = 0; dim_counter < dim; ++dim_counter) {
				if (PublicFunction::RandomDouble(0, 1) < CR || dim_counter == rnbr) {
					trail_individual[dim_counter] = population[best_individual][dim_counter];
					for (unsigned vector_diff_counter = 0; vector_diff_counter < number_of_vector_differences; ++vector_diff_counter) {
						trail_individual[dim_counter] += F * (population[individuals[vector_diff_counter * 2]][dim_counter] - population[individuals[vector_diff_counter * 2 + 1]][dim_counter]);
					}
					if (IsOutBound(trail_individual[dim_counter], dim_counter)) {
						OutBoundHandler(population, base_individual, trail_individual, dim_counter);
					}
				} else {
					trail_individual[dim_counter] = population[base_individual][dim_counter];
				}
			}
			free(individuals);
			return trail_individual;
		}

		double* Strategies::DE_Cur_To_Rand(Population& population, unsigned base_individual, unsigned number_of_vector_differences) {
			ExecutiveVariablesCheck();
			unsigned* individuals = PublicFunction::ShufflePopulation(Strategies::ev_->GetDE_NP(), base_individual, number_of_vector_differences * 2 + 1);
			const size_t dim = Strategies::ev_->GetDE_Dim();
			double* trail_individual = CreateTrailIndividual(dim);
			unsigned rnbr = PublicFunction::RandomInt(0, dim - 1);
			//const double CR = population[base_individual].GetCR();
			const double CR = Strategies::lv_->next_generation_[base_individual].GetCR();
			//const double F = population[base_individual].GetF();
			const double F = Strategies::lv_->next_generation_[base_individual].GetF();
			//const double K = population[base_individual].GetK();
			const double K = Strategies::lv_->next_generation_[base_individual].GetK();

			for (size_t dim_counter = 0; dim_counter < dim; ++dim_counter) {
				trail_individual[dim_counter] = population[base_individual][dim_counter] + K * (population[individuals[0]][dim_counter] - population[base_individual][dim_counter]);
				for (unsigned vector_diff_counter = 0; vector_diff_counter < number_of_vector_differences; ++vector_diff_counter) {
					trail_individual[dim_counter] += F * (population[individuals[vector_diff_counter * 2 + 1]][dim_counter] - population[individuals[vector_diff_counter * 2 + 2]][dim_counter]);
				}
				if (IsOutBound(trail_individual[dim_counter], dim_counter)) {
					OutBoundHandler(population, base_individual, trail_individual, dim_counter);
				}
			}
			free(individuals);
			return trail_individual;
		}

		double* Strategies::DE_Cur_To_Best(Population& population, unsigned base_individual, unsigned best_individual, unsigned number_of_vector_differences) {
			ExecutiveVariablesCheck();
			unsigned* individuals = PublicFunction::ShufflePopulation(Strategies::ev_->GetDE_NP(), base_individual, number_of_vector_differences * 2);
			const size_t dim = Strategies::ev_->GetDE_Dim();
			double* trail_individual = CreateTrailIndividual(dim);
			unsigned rnbr = PublicFunction::RandomInt(0, dim - 1);
			//const double CR = population[base_individual].GetCR();
			const double CR = Strategies::lv_->next_generation_[base_individual].GetCR();
			//const double F = population[base_individual].GetF();
			const double F = Strategies::lv_->next_generation_[base_individual].GetF();

			for (unsigned dim_counter = 0; dim_counter < dim; ++dim_counter) {
				if (PublicFunction::RandomDouble(0, 1) < CR || dim_counter == rnbr) {
					trail_individual[dim_counter] = population[base_individual][dim_counter] + F * (population[best_individual][dim_counter] - population[base_individual][dim_counter]);
					for (unsigned vector_diff_counter = 0; vector_diff_counter < number_of_vector_differences; ++vector_diff_counter) {
						trail_individual[dim_counter] += F * (population[individuals[vector_diff_counter * 2]][dim_counter] - population[individuals[vector_diff_counter * 2 + 1]][dim_counter]);
					}
					if (IsOutBound(trail_individual[dim_counter], dim_counter)) {
						OutBoundHandler(population, base_individual, trail_individual, dim_counter);
					}
				} else {
					trail_individual[dim_counter] = population[base_individual][dim_counter];
				}
			}
			free(individuals);
			return trail_individual;
		}

		double* Strategies::DE_Cur_To_PBest(Population& population, unsigned base_individual, unsigned* sorted_individuals, unsigned number_of_vector_differences) {
			ExecutiveVariablesCheck();
			//
			// If trail individual is successfully selected but it had been regenerated because of out-of-bound. Should this success of CR and F be added into success-history?
			// This Strategy implementation(DE/Current-to-pBest) is follow SHADE paper, but this "ADDITIONAL" consideration of out-of-bound is not in general SHADE.
			// BTW, it is using kHalfBoundDistance when any dimension is outside the boundaries in original SHADE.
			//
			Strategies::ev_->UpdateOut_B(false);
			//CheckArchiveIsSet(ev_->GetArchiveNowSize(), Strategies::archive_is_set_);

			CheckArchiveIsSet(lv_->shade_archive_now_size_, Strategies::archive_is_set_);
			unsigned total_size = Strategies::ev_->GetDE_NP() + lv_->shade_archive_now_size_;
			unsigned* individuals = PublicFunction::ShufflePopulation(total_size, base_individual, total_size - 1);
			std::vector<std::pair<unsigned, unsigned>> difference_individual_pairs = VectorDifferencesPair(individuals, number_of_vector_differences);
			const size_t dim = Strategies::ev_->GetDE_Dim();
			double* trail_individual = CreateTrailIndividual(dim);
			unsigned rnbr = PublicFunction::RandomInt(0, dim - 1);
			const double P = population[base_individual].GetP();
			unsigned pbest_individual = sorted_individuals[PublicFunction::RandomInt(0, static_cast<int>(std::round(Strategies::ev_->GetDE_NP() * P)))];
			double difference = 0;
			//const double CR = population[base_individual].GetCR();
			const double CR = Strategies::lv_->next_generation_[base_individual].GetCR();
			//const double F = population[base_individual].GetF();
			const double F = Strategies::lv_->next_generation_[base_individual].GetF();
			const double NP = Strategies::ev_->GetDE_NP();

			for (size_t dim_counter = 0; dim_counter < dim; ++dim_counter) {
				if (PublicFunction::RandomDouble(0, 1) < CR || dim_counter == rnbr) {
					trail_individual[dim_counter] = population[base_individual][dim_counter] + F * (population[pbest_individual][dim_counter] - population[base_individual][dim_counter]);
					for (unsigned vector_differences_counter = 0; vector_differences_counter < number_of_vector_differences; ++vector_differences_counter) {
						difference = population[difference_individual_pairs[vector_differences_counter].first][dim_counter];
						// The function VectorDifferenecesPair() guarantees that the first value of the pair in the vector is selected from population.
						if (difference_individual_pairs[vector_differences_counter].second >= NP) {
							// It means that the individual should be taken from archive if the second value is larger than or equal to NP
							difference -= (*Strategies::archive_)[difference_individual_pairs[vector_differences_counter].second % ev_->GetDE_NP()][dim_counter];
						} else {
							// or from population.
							difference -= population[difference_individual_pairs[vector_differences_counter].second][dim_counter];
						}
						trail_individual[dim_counter] += F * difference;
					}
					if (IsOutBound(trail_individual[dim_counter], dim_counter)) {
						ev_->UpdateOut_B(true);
						OutBoundHandler(population, base_individual, trail_individual, dim_counter);
					}
				} else {
					trail_individual[dim_counter] = population[base_individual][dim_counter];
				}
			}
			free(individuals);
			return trail_individual;
		}

		bool Strategies::IsOutBound(double value, unsigned base_dim) {
			if (value < Strategies::ev_->GetBoundMin(base_dim) || value > Strategies::ev_->GetBoundMax(base_dim))
				return true;
			return false;
		}

		void Strategies::OutBoundHandler(Population& population, unsigned base_individual, double* trail_individual, unsigned base_dim) {
			corematerial::OutBoundHandler obh_pattern = Strategies::ev_->GetDE_OutBoundHandlerPattern();
			const double bound_min = Strategies::ev_->GetBoundMin(base_dim), bound_max = Strategies::ev_->GetBoundMax(base_dim);
			if (obh_pattern == corematerial::OutBoundHandler::kBackToBound) {
				if (trail_individual[base_dim] < bound_min) trail_individual[base_dim] = bound_min;
				else if (trail_individual[base_dim] > bound_max) trail_individual[base_dim] = bound_max;
			} else if (obh_pattern == corematerial::OutBoundHandler::kHalfBoundDistance) {
				if (trail_individual[base_dim] < bound_min)
					// Middle point of the "BASE" individual's dimension to the lower bound.
					trail_individual[base_dim] = (population[base_individual][base_dim] + bound_min) / 2;
				else if (trail_individual[base_dim] > bound_max)
					// Middle point of the upper bound to the "BASE" individual's dimension.
					trail_individual[base_dim] = (bound_max + population[base_individual][base_dim]) / 2;
			} else if (obh_pattern == corematerial::OutBoundHandler::kRerandomDimension) {
				trail_individual[base_dim] = PublicFunction::RandomDouble(bound_min, bound_max);
			} else if (obh_pattern == corematerial::OutBoundHandler::kRerandomIndividual) {
				for (size_t dim_counter = 0; dim_counter < Strategies::ev_->GetDE_Dim(); ++dim_counter) {
					trail_individual[dim_counter] = PublicFunction::RandomDouble(Strategies::ev_->GetBoundMin(dim_counter), Strategies::ev_->GetBoundMax(dim_counter));
				}
			}
		}


		std::vector<std::pair<unsigned, unsigned>> Strategies::VectorDifferencesPair(unsigned* individuals, unsigned number_of_vector_differences) {
			//
			// Only the second value of the pair in the vector is randomly select from the union of the population and the archive.
			// Otherwise is merely selected from population.
			//
			const size_t NP = Strategies::ev_->GetDE_NP();
			const size_t archive_size = lv_->shade_archive_now_size_;
			std::vector<std::pair<unsigned, unsigned>> difference_individual_pairs;
			for (unsigned vector_differences_counter = 0; vector_differences_counter < number_of_vector_differences; ++vector_differences_counter) {
				unsigned individual_first;
				unsigned index = 0;
				while (index < NP + archive_size) {
					if (individuals[index] < NP && individuals[index] != UINT_MAX) {
						// Only choose from population.
						individual_first = individuals[index];
						individuals[index] = UINT_MAX;
						break;
					}
					if (index == NP + archive_size - 1) {
						std::cout << "Can't find any individuals[index] falling within the interval [0:" << Strategies::ev_->GetDE_NP() << "]." << std::endl;
						std::cout << "In strategies.cpp, function Strategies::VectorDifferencesPair(unsigned*,unsigned)." << std::endl;
						exit(0);
					}
					++index;
				}
				index = 0;
				while (index < NP + archive_size) {
					// choose from the union of the population and the archive.
					if (individuals[index] != UINT_MAX) {
						difference_individual_pairs.push_back(std::make_pair(individual_first, individuals[index]));
						individuals[index] = UINT_MAX;
						break;
					}
					++index;
				}
			}
			return difference_individual_pairs;
		}
	} // differentialevolution
} // evolutionalgorithm