#pragma once
#include <vector>
#include "ParticleContact.h"

namespace P6
{
    class ContactResolver
    {
        public:
        //Max number of reoslve calls
        unsigned max_iterations;

        //Constructor to assign the max iterations on init
        ContactResolver(unsigned _maxIterations);

        //reolve all assigned contacts
        void ResolveContacts(std::vector<ParticleContact*> contacts, float time);

        protected:
            //Current number of Resolve calls
            unsigned current_iterations = 0;

    };

}
