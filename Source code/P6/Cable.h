#pragma once

#include <iostream>
#include "ForceGenerator.h"

#include "Springs/AnchoredSpring.h"
#include "Rod.h"
#include "P6Particle.h"
#include "ParticleLink.h"

namespace P6
{
    /*Cables anchor a point in space, but should never exceed the length you set like a rod*/
    class Cable  : public ForceGenerator, ParticleLink//: public AnchoredSpring, Rod
    {
        private:
        MyVector handlePoint;
        float cableLength, lineConstant;
        P6Particle* particle;
        Rod* rod;

        public:

        bool bEnd = false;

        Cable(float cableLength);

        void UpdateForce(P6Particle* particle, float time) override;

        float getCableLength();

        /*RODS CLASSES*/
        // float length = 1;
        // float restitution = 0.9;
        // ParticleContact* GetContact() override;


    };
}