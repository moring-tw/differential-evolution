#include "../../../headers/differential_evolution/variants/random.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		Random::Random() {

		}

		Random::~Random() {

		}

		void Random::RandomP() {
			const size_t next_gen_np = Basic::lv_->ev_.GetDE_NextGenNP();
			const size_t np = Basic::lv_->ev_.GetDE_NP();
			const size_t p_min = Basic::lv_->ev_.GetDE_PMin();
			const double p_max_scale = Basic::lv_->ev_.GetDE_PMaxScale();
			for (size_t next_gen_np_counter = 0; next_gen_np_counter < next_gen_np; ++next_gen_np_counter) {
				Basic::lv_->next_generation_[next_gen_np_counter].SetP(PublicFunction::RandomDouble((double)p_min / np, p_max_scale));
			}
		}
	} // namespace differentialevolution
} // namespace evolutionalgorithm