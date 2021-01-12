#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_BEHAVIOR_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_BEHAVIOR_H_

#include "variants/de.h"
#include "variants/sade.h"
#include "variants/shade.h"
#include "variants/random.h"
#include "localvariables.h"

namespace evolutionalgorithm {
	namespace differentialevolution {
		class Behavior {
		public:
			Behavior();
			virtual ~Behavior();
			void SetDE(DE*);
			void SetSaDE(SaDE*);
			void SetSHADE(SHADE*);
			void SetRandom(Random*);
			void SetLocalVariables(LocalVariables*);
			void CheckLV();
		protected:
			DE* de_ = nullptr;
			SaDE* sade_ = nullptr;
			SHADE* shade_ = nullptr;
			Random* random_ = nullptr;
			LocalVariables* lv_ = nullptr;
		};
	}
}
#endif // !EA_HEADERS_DIFFERENTIAL_EVOLUTION_BEHAVIOR_H_
