#pragma once

#include "MyVector.h"
#include "chrono"

namespace P6 {

	class P6Particle
	{
		//FIELDS
	public:
		float mass = 1;
		MyVector Position;
		MyVector Velocity;
		MyVector Acceleration;
		float damping = 0.9f;
		float lifespan = 10.0f;
		float spawnTime;
		float radius = 1.0f; //a radius of 1 meter or size of the particle
		float restitution = 1.0f;

	protected:
		MyVector accumulatedForce = MyVector(0, 0, 0);
		bool isDestroyed = false;

		//CONSTRUCTOR
	public:
		P6Particle();
		P6Particle(MyVector Position, MyVector Velocity, MyVector Acceleration, float lifespan);
		P6Particle(MyVector Position, MyVector Velocity, MyVector Acceleration, float lifespan, float spawnTime);

		//METHODS
	protected:
		void UpdatePosition(float time);
		void UpdateVelocity(float time);

	public:
		void Update(float time);
		void Destroy();
		bool IsDestroyed();
		void AddForce(MyVector force);
		void ResetForce();
	};
}

