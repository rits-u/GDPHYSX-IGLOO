#include "RenderParticle.h"
using namespace P6; 

RenderParticle::RenderParticle(P6Particle* p, Model3D* model) {
	this->physicsParticle = p;
	this->renderObject = model;
}

void RenderParticle::draw() {
	if (!this->physicsParticle->IsDestroyed()) {
		this->renderObject->setPosition(this->physicsParticle->Position);
		this->renderObject->drawModel();
	}
}