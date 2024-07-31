#pragma once

#include "ParticleLink.h"

namespace P6 {
	class Rod : public ParticleLink
	{
		public:
			float length = 1; //particles should always be at this length
			float restitution = 0; //ideally should be 0

			ParticleContact* GetContact() override;
	};

}

