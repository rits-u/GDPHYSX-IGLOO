#include "P6Particle.h"
using namespace P6;

P6Particle::P6Particle() {
	this->Position = MyVector(0, 0, 0);
	this->Velocity = MyVector(0, 0, 0);
	this->Acceleration = MyVector(0, 0, 0);
	this->lifespan = 10.0f;
	this->spawnTime = 0.0f;
	this->gravityStr = 1.0f;
}


P6Particle::P6Particle(MyVector Position, float damping, float mass, float radius) {
	this->Position = Position;
	this->damping = damping;
	this->mass = mass;
	this->radius = radius;
	this->gravityStr = 1.f;
}

P6Particle::P6Particle(float gravityStr, MyVector Position, float mass, float radius) {
	this->Position = Position;
	this->damping = 0.9f;
	this->mass = mass;
	this->radius = radius;
	this->gravityStr = gravityStr;
}

//this function is used for updating the position of the particle
void P6Particle::UpdatePosition(float time) {
	this->Position = this->Position + (this->Velocity * time) + ((this->Acceleration * time * time) * (1.0f / 2.0f));
}

//this function is used for updating the velocity of the particle
void P6Particle::UpdateVelocity(float time) {
	//A                 =        F         /    m
	this->Acceleration += accumulatedForce * (1 / mass);

	//Vf           =        V1      +         A
	this->Velocity = this->Velocity + (this->Acceleration * time);

	//Vfd          =         Vf     *       d ^ t
	this->Velocity = this->Velocity * powf(damping, time);
}

//this function manages the update of the properties of the particle
void P6Particle::Update(float time) {
	this->UpdatePosition(time);
	this->UpdateVelocity(time);

	this->ResetForce();
}


//this function resets the force so that it won't apply force unnecessarily
void P6Particle::ResetForce() {
	this->accumulatedForce = MyVector(0, 0, 0);
	this->Acceleration = MyVector(0, 0, 0);
}

//this function sets the flag of the particle on being destroyed
void P6Particle::Destroy() {
	this->isDestroyed = true;
}

//this function tells whether a particle is destroyed or not
bool P6Particle::IsDestroyed() {
	return isDestroyed;
}

//This function updates the accumulated force
void P6Particle::AddForce(MyVector force) {
	accumulatedForce += force;
}

void P6Particle::AddForceAtPoint(MyVector force, MyVector p) {
	this->AddForce(force);
	this->accumulatedForce = p.getCrossProduct(force);
}