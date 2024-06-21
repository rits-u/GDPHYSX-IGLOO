#include "P6Particle.h"
using namespace P6;

P6Particle::P6Particle(MyVector Position, MyVector Velocity, MyVector Acceleration, float lifespan) {
	this->Position = Position;
	this->Velocity = Velocity;
	this->Acceleration = Acceleration;
	this->lifespan = lifespan;
	this->spawnTime = 0.0f;
}

P6Particle::P6Particle(MyVector Position, MyVector Velocity, MyVector Acceleration, float lifespan, float spawnTime) {
	this->Position = Position;
	this->Velocity = Velocity;
	this->Acceleration = Acceleration;
	this->lifespan = lifespan;
	this->spawnTime = spawnTime;
}

//this function is used for updating the position of the particle
void P6Particle::UpdatePosition(float time) {
	this->Position = this->Position + (this->Velocity * time) + ((this->Acceleration * time * time) * (1.0f / 2.0f));
}

//this function is used for updating the velocity of the particle
void P6Particle::UpdateVelocity(float time) {
	//A                 =        F         /    m
	this->Acceleration += accumulatedForce * (1/mass);

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

//GETERS AND SETTERS
void P6Particle::Destroy() {
	this->isDestroyed = true;
}

bool P6Particle::IsDestroyed() {
	return isDestroyed;
}

void P6Particle::AddForce(MyVector force) {
	accumulatedForce += force;
}

float P6Particle::getPosition() {
	return this->Position.y;
}