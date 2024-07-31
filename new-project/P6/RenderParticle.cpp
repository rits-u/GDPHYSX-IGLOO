#include "RenderParticle.h"
using namespace P6;

//constructor
RenderParticle::RenderParticle(P6Particle* p, Model3D* model) {
	this->physicsParticle = p;
	this->renderObject = model;
}

// this function is used for updating the position of the model based on the position 
// of the particle, also used for calling the renderer of the object
void RenderParticle::draw(std::string type) {
	if (!this->physicsParticle->IsDestroyed()) {
		this->renderObject->position = this->physicsParticle->Position;
		float r = this->physicsParticle->radius;
		MyVector radius = MyVector(r, r, r);
		this->renderObject->setScale(radius);
		this->renderObject->drawModel();
	}
}