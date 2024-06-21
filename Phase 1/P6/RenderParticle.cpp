#include "RenderParticle.h"
using namespace P6; 

//constructor
RenderParticle::RenderParticle(P6Particle* p, Model3D* model) {
	this->physicsParticle = p;
	this->renderObject = model;
}

// this function is used updating the position of the model based on the position 
// of the particle, also used for calling the renderer of the object
void RenderParticle::draw() {
	if (!this->physicsParticle->IsDestroyed()) {
		this->renderObject->setPosition(this->physicsParticle->Position);
		this->renderObject->drawModel();
	}
}