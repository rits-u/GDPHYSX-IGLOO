#pragma once

#include "MyVector.h"
#include "chrono"

namespace P6 {

	class P6Particle
	{
		//FIELDS
		public:
			float mass = 1;
			MyVector Position = MyVector(0, 0, 0);
			MyVector Velocity = MyVector(0, 0, 0);
			MyVector Acceleration = MyVector(0, 0, 0);
			float damping = 0.9f;
			float lifespan = 10.0f;
			float spawnTime = 10.f;
			float radius = 1.0f; //a radius of 1 meter or size of the particle
			float restitution = 0.9f;
			float gravityStr = 1.f;

		protected:
			MyVector accumulatedForce = MyVector(0, 0, 0);
			bool isDestroyed = false;
		
		//CONSTRUCTOR
		public:
			P6Particle();
			P6Particle(MyVector Position, float damping, float mass, float radius);
			P6Particle(float gravityStr, MyVector Position, float mass, float radius);

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
			void AddForceAtPoint(MyVector force, MyVector p);
	};
}

