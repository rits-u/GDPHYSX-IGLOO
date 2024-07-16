#pragma once
#include "P6Particle.h"
#include "ParticleContact.h"

namespace P6
{
    //Base class for all links
    class ParticleLink
    {
        public:
        //particles that are linked
        P6Particle* particles[2];

        //Returns a contact if particles violate the condition of the link
        virtual ParticleContact* GetContact() {return nullptr;};

        protected:
        //Distance between 2 particles used mainly for interpenetration
        float CurrentLength();
        

    };
}