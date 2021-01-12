#pragma once
#ifndef EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_RANDOM_H_
#define EA_HEADERS_DIFFERENTIAL_EVOLUTION_VARIANTS_RANDOM_H_
#include "basic.h"

//
// This class is not any variants of differential evolutions,
// whereas it's for some parameters which is not adaptive controlled but random generated.
//
namespace evolutionalgorithm {
	namespace differentialevolution {
		class Random : public Basic {
		public:
			Random();
			virtual ~Random();
			void RandomP();
		protected:
		private:

		};
	} // namespace differentialevolution
} // namespace evolutionalgorithm


#endif // EA_HEADERS_DIFFERENTIAL_EVOLITION_VARIANTS_RANDOM_H_