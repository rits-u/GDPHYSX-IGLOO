#pragma once
#include "P6Particle.h"


namespace P6
{
    class ParticleContact
    {
        public:
        
        //interpenetration depth
        float depth;

        //The particles in contact
        P6Particle* particles[2];

        //Holds the coefficient of restitution
        float restitution;

        //Contact normal of this collision
        MyVector contactNormal;

        //Resolve this contact
        void Resolve(float time);

        //Get the separating speed
        float GetSeparatingSpeed();

        protected:
        //Calculates the new velocities of the objects
        void ResolveVelocity(float time);

        //Calculates the interpenetration resolution
        void ResolveInterpenertration(float time);

    };
}