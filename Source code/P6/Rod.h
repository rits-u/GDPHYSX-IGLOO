#pragma once

#include "ParticleContact.h"
#include "ParticleLink.h"

namespace P6
{
    class Rod : public ParticleLink
    {
        public:
        //length of rod in mteres
        float length = 1;

        //always ser restitution to 0 since a rod has no bounciness
        float restitution = 0;

        //overrride the links getcontact
        ParticleContact* GetContact() override;

    };
}