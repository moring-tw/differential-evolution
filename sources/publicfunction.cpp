#include "../headers/publicfunction.h"

namespace evolutionalgorithm {
	std::mt19937 PublicFunction::generator_(static_cast<int>(time(0)));
	PublicFunction::PublicFunction() {

	}

	PublicFunction::~PublicFunction() {

	}

	double PublicFunction::RandomDouble(double bound_min, double bound_max) {
		std::uniform_real_distribution<double> distribution(bound_min, bound_max);
		return distribution(PublicFunction::generator_);
	}

	int PublicFunction::RandomInt(int bound_min, int bound_max) {
		std::uniform_int_distribution<int> distribution(bound_min, bound_max);
		return distribution(PublicFunction::generator_);
	}

	unsigned* PublicFunction::ShufflePopulation(size_t np) {
		if (np <= 0) {
			std::cout << "Can't shuffle population which size is less than or equal to 0." << std::endl;
			exit(0);
		}
		unsigned* pool = (unsigned*)malloc(sizeof(unsigned) * np);
		if (pool == nullptr) {
			std::cout << "Can't malloc pool, this may cause by np equal to ZERO." << std::endl;
			exit(0);
		}
		for (size_t ini = 0; ini < np; ++ini) {
			pool[ini] = ini;
		}
		for (size_t index = 0; index < np; ++index) {
			std::swap(pool[index], pool[index + PublicFunction::RandomInt(0, np - index - 1)]);
		}
		return pool;
	}

	unsigned* PublicFunction::ShufflePopulation(size_t np, size_t base_individual, unsigned how_much) {
		if (how_much > np - 1) {
			std::cout << "Can't shuffle more than np-1" << std::endl;
			exit(0);
		}
		if (base_individual >= np) {
			std::cout << "base_individual out of population range." << std::endl;
			exit(0);
		}
		if (np <= 1) {
			std::cout << "Can't shuffle population when there np is less than 2." << std::endl;
			exit(0);
		}
		unsigned* pool = (unsigned*)malloc(sizeof(unsigned) * np - 1);
		if (pool == nullptr) {
			std::cout << "Can't malloc pool, this may cause by np less than TWO." << std::endl;
			exit(0);
		}
		bool skiped = false;
		for (size_t ini = 0; ini < (np - 1) ; ++ini) {
			if (ini == base_individual) skiped = true;
			if (skiped)
				pool[ini] = ini + 1;
			else
				pool[ini] = ini;
			if (np == 2) break;
		}
		if (np > 2) {
			for (unsigned index = 0; index < how_much; ++index) {
				std::swap(pool[index], pool[index + PublicFunction::RandomInt(0, np - index - 2)]);
			}
		}
		return pool;
	}

	//
	// Quick Sort
	//
	void PublicFunction::SortPopulation(double* fitness, unsigned* np_rank, size_t np, size_t left) {
		if (left < np) {
			int i = left, j = np;
			while (true) {
				while (i + 1 < np && fitness[np_rank[++i]] < fitness[np_rank[left]]);
				while (j - 1 > -1 && fitness[np_rank[--j]] > fitness[np_rank[left]]);
				if (i >= j) break;
				std::swap(np_rank[i], np_rank[j]);
			}
			std::swap(np_rank[left], np_rank[j]);
			SortPopulation(fitness, np_rank, j, left);
			SortPopulation(fitness, np_rank, np, j + 1);
		}
	}

	void PublicFunction::SortIndividual(double* fitness, unsigned* np_rank, size_t np, size_t base_individual) {
		unsigned rank_position = 0;
		for (size_t np_counter = 0; np_counter < np; ++np_counter) {
			if (np_rank[np_counter] == base_individual) {
				rank_position = np_counter;
				break;
			}
		}
		// If fitness of individual is getting better, move its rank to upper place.
		while (rank_position > 0) {
			if (fitness[np_rank[rank_position - 1]] > fitness[np_rank[rank_position]]) {//ASC
				std::swap(np_rank[rank_position - 1], np_rank[rank_position]);
				--rank_position;
			} else {
				break;
			}
		}
		// If fitness of individual is getting worse, move its rank to lower place.
		while (rank_position < np - 1) {
			if (fitness[np_rank[rank_position + 1]] < fitness[np_rank[rank_position]]) {
				std::swap(np_rank[rank_position + 1], np_rank[rank_position]);
				++rank_position;
			} else {
				break;
			}
		}
	}

	double PublicFunction::NormalDistributionRandom(double mean, double stddev) {
		std::normal_distribution<double> distribution(mean, stddev);
		return distribution(generator_);
	}

	double PublicFunction::CauchyDistributionRandom(double mean, double stddev) {
		std::cauchy_distribution<double> distribution(mean, stddev);
		return distribution(generator_);
	}

	double PublicFunction::WeightedArithmeticMean(std::vector<double>& delta_fitness, std::vector<double>& success) {
		double amount_delta = 0, result = 0;
		for (unsigned delta_fitness_counter = 0; delta_fitness_counter < delta_fitness.size(); ++delta_fitness_counter) {
			amount_delta += delta_fitness[delta_fitness_counter];
		}
		for (unsigned success_counter = 0; success_counter < success.size(); ++success_counter) {
			result += (delta_fitness[success_counter] / amount_delta) * success[success_counter];
		}
		return result;
	}

	double PublicFunction::WeightedLenmerMean(std::vector<double>& delta_fitness, std::vector<double>& success) {
		double amount_delta = 0, result = 0, temp = 0;
		for (unsigned delta_fitness_counter = 0; delta_fitness_counter < delta_fitness.size(); ++delta_fitness_counter) {
			amount_delta += delta_fitness[delta_fitness_counter];
		}
		for (unsigned success_counter = 0; success_counter < success.size(); ++success_counter) {
			result += (delta_fitness[success_counter] / amount_delta) * pow(success[success_counter], 2);
			temp += (delta_fitness[success_counter] / amount_delta) * success[success_counter];
		}
		result /= temp;
		return result;
	}

	double PublicFunction::CalculateStandardDeviation(double* values, double mean, unsigned values_size) {
		double stddev = 0;
		for (unsigned size_counter = 0; size_counter < values_size; ++size_counter) {
			stddev += pow(values[size_counter] - mean, 2);
		}
		stddev /= values_size;
		stddev = pow(stddev, 0.5);
		return stddev;
	}

	double PublicFunction::RoundToDecimalPlace(double value, unsigned decimal_place) {
		value = floor(value * pow(10, decimal_place) + 0.5) / pow(10, decimal_place);
		return value;
	}

} // namespace evolutionalgorithm