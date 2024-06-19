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

void RenderParticle::debugDraw(int num) {
	if (!this->physicsParticle->IsDestroyed()) {
		this->renderObject->setPosition(this->physicsParticle->Position);
		this->renderObject->drawModel();

		/*if (num >= 6) {
			num = 1;

		}
		else {
			num++;
		}
		std::cout << num << " particle: " << (*p)->getPosition() << std::endl;*/

		//std::cout << "draw" << std::endl;
		//std::cout << num << " particle: " << this->physicsParticle->getPosition() << std::endl;
	}
	
}

void RenderParticle::instantiateParticle() {

}