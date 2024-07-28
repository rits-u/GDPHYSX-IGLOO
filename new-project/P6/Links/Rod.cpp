#include "Rod.h"
using namespace P6;

ParticleContact* Rod::GetContact() {
	float currLen = CurrentLength();

	if (currLen == length)
		return nullptr;

	ParticleContact* ret = new ParticleContact();
	ret->particles[0] = particles[0];
	ret->particles[1] = particles[1];

	MyVector dir = particles[1]->Position - particles[0]->Position;
	dir = dir.normalize();

	//Rod is longer than expected
	if (currLen > length) {
		ret->contactNormal = dir;
		ret->depth = currLen - length; //depth should always be POSITIVE
	}

	//Rod is shorter than expected
	else {
		ret->contactNormal = dir * -1;
		ret->depth = length - currLen;
	}

	//ideally this should be 0
	ret->restitution = restitution;

	return ret;
}