#pragma once
#include "../ForceGenerator.h"

namespace P6
{
    class ParticleSpring : public ForceGenerator
    {

        private:
        //the other particle this spring is attached to
        P6Particle* otherParticle;

        //spring contstant "stiffness of spring"
        float springConstant;

        //rest length for this spring
        float restLength;

        public:
        //Constrcutor
        ParticleSpring(P6Particle* particle, float _springConst, float _restLen);

        //Override the Update Force of th eGenerator
        void UpdateForce(P6Particle* particle, float time) override;
    };
}