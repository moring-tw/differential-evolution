#include "../../headers/differential_evolution/evolve.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		Evolve::Evolve()
		{
		}

		Evolve::~Evolve()
		{
		}

		void Evolve::BeforeEvolveDE_RandomP() {
			if (Behavior::lv_->ev_.GetDE_NextGenNP() > 0) {
				if (Behavior::lv_->ev_.GetDE_NP() > 0) {
					if (Behavior::lv_->ev_.GetDE_PMin() > 0) {
						if (Behavior::lv_->ev_.GetDE_PMaxScale() > 0) {
							Evolve::random_->RandomP();
						} else Evolve::EvolvingError("P min");
					} else Evolve::EvolvingError("P max scale");
				} else Evolve::EvolvingError("NP");
			} else Evolve::EvolvingError("next gen NP");
		}

		void Evolve::EvolveDE() {
			if (Evolve::lv_->ev_.GetDE_StrategiesPattern() != corematerial::MutantAndCrossover::UNSET) {
				Evolve::de_->Evolution();
			} else Evolve::EvolvingError("GetDE_StrategiesPattern");
		}

		void Evolve::BeforeEvolveSaDE_StrategiesSelection() {
			Evolve::sade_->CalculateSaDE_StrategiesProbability();
			if (Evolve::lv_->ev_.GetDE_NP() != 0) {
				Evolve::sade_->SelectSaDE_Strategies();
			} else Evolve::EvolvingError("NP");
		}

		void Evolve::BeforeEvolveSaDE_CR_Selection(const size_t num_of_memory) {
			if (num_of_memory == 1 || num_of_memory == Behavior::lv_->ev_.GetDE_NumOfStrategies()) {
				if (Behavior::lv_->ev_.GetDE_NP() == Behavior::lv_->ev_.GetDE_NextGenNP()) {
					//
					// In SaDE, NP must be equal to next gen NP.
					//
					if (Behavior::lv_->ev_.GetDE_StrategiesPattern() > 0) {
						Behavior::sade_->CalculateSaDE_CRm(num_of_memory);
						Behavior::sade_->SelectSaDE_CR();
					} else Evolve::EvolvingError("StrategiesPattern");
				} else Evolve::EvolvingError("NP");
			} else Evolve::EvolvingError("num_of_memory");
		}

		void Evolve::BeforeEvolveSHADE_CR_Selection() {
			if (Behavior::lv_->ev_.GetDE_NextGenNP() > 0) {
				Behavior::shade_->SelectSHADE_CR();
			} else Evolve::EvolvingError("de_next_gen_NP_");
		}

		void Evolve::BeforeEvolveSHADE_F_Selection() {
			if (Behavior::lv_->ev_.GetDE_NextGenNP() > 0) {
				Behavior::shade_->SelectSHADE_F();
			} else Evolve::EvolvingError("de_next_gen_NP_");
		}
	} // namespace evolutionalgorithm
} // namespace differentialevolution