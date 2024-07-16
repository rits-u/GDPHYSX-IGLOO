#pragma once

#include "../ForceGenerator.h"

namespace P6
{
    class AnchoredSpring : public ForceGenerator
    {
        public:
        AnchoredSpring(MyVector pos, float _springConst, float _restLen);

        //override update force of the generator
        void UpdateForce(P6Particle* particle, float time) override;
        
        private:

        /*Point in world hwere the other end of the spring is*/
        //where spring is attached
        MyVector anchorPoint;

        //how hard ur sring is
        /*Spring constant// how stiff the spring is*/
        float springConstant;

        //rest length of spring
        float restLength;
    };
}