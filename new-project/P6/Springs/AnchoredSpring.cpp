#include "AnchoredSpring.h"
using namespace P6;

void AnchoredSpring::UpdateForce(P6Particle* particle, float time) {
	MyVector pos = particle->Position;

	MyVector force = pos - anchorPoint; //vector Pos->AnchorPoint

	float mag = force.getMagnitude(); //distance of V above or lcurr

	//			f		=		-k		*		|lcurr - lrest|
	float springForce = -springConstant * abs(mag - restLength);

	force = force.normalize();
	force = force * springForce;

	particle->AddForce(force);
}