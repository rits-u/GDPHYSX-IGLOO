#include "Cable.h"
using namespace P6;

Cable::Cable(P6Particle* p, float maxLength) {
	this->restitution = 0;
	this->maxLength = maxLength;
	this->length = 50.0f;
	this->anchorParticle = p;
	this->particles[0] = this->anchorParticle;
}

/*  this function handles the connection between the anchor particle and the actual particle,
    this limits the length of the lionk */
ParticleContact* Cable::GetContact() {
	float currLen = CurrentLength();

	if (currLen == this->length)
		return nullptr;

	ParticleContact* ret = new ParticleContact();
	ret->particles[0] = this->anchorParticle;
	ret->particles[1] = this->particles[1];

	MyVector dir = this->particles[1]->Position - this->anchorParticle->Position;
	dir = dir.normalize();

	if (this->length < this->maxLength)
		this->length += 10.f;


	//Rod is longer than expected
	if (currLen > this->length) {
		ret->contactNormal = dir;
		ret->depth = currLen - this->length; //depth should always be POSITIVE
	}

	//Rod is shorter than expected
	else {
		ret->contactNormal = dir * -1;
		ret->depth = this->length - currLen;
	}

	//ideally this should be 0
	ret->restitution = restitution;

	return ret;

}