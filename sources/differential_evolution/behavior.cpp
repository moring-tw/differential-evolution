#include "../../headers/differential_evolution/behavior.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		Behavior::Behavior() {

		}
		Behavior::~Behavior() {

		}

		void Behavior::SetDE(DE* de) {
			Behavior::de_ = de;
		}

		void Behavior::SetSaDE(SaDE* sade) {
			Behavior::sade_ = sade;
		}

		void Behavior::SetSHADE(SHADE* shade) {
			Behavior::shade_ = shade;
		}

		void Behavior::SetRandom(Random* random) {
			Behavior::random_ = random;
		}

		void Behavior::SetLocalVariables(LocalVariables* lv) {
			if (lv == nullptr) {
				std::cout << "Memorize doesn't accept nullptr of LocalVariables object pointer." << std::endl;
				exit(0);
			}
			Behavior::lv_ = lv;
		}

		void Behavior::CheckLV() {
			if (Behavior::lv_ == nullptr) {
				std::cout << "Before using Memorize object, lv_ must be assigned by Memorize::SetLocalVariables()." << std::endl;
				exit(0);
			}
		}
	}
}