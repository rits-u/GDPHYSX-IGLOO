#pragma once

#include <vector>
#include "ParticleContact.h"

namespace P6 {
	class ContactResolver
	{
		//FIELDS
		protected:
			unsigned current_iterations = 0;

		//METHODS
		public:
			unsigned max_iterations;
			ContactResolver(unsigned _maxIterations) : max_iterations(_maxIterations) {}
			void ResolveContacts(std::vector<ParticleContact*> contacts, float time);


	};

}

