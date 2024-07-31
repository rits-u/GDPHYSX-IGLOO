#pragma once
#include <list>
#include <vector>

#include "P6Particle.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"
#include "ParticleContact.h"
#include "ContactResolver.h"
#include "Links/ParticleLink.h"

#include "iostream"

namespace P6 {
	class PhysicsWorld 
	{
		//FIELDS
		private:
			GravityForceGenerator Gravity = GravityForceGenerator(MyVector(0, -9.8, 0));

		protected:
			ContactResolver contactResolver = ContactResolver(20);


		public:
			ForceRegistry forceRegistry;
			std::list<P6Particle*> Particles;
			std::vector<ParticleContact*> Contacts;
			std::list<ParticleLink*> Links;

		//METHODS
		public:
			void AddParticle(P6Particle* toAdd);
			void Update(float time);
			void CheckLifespan(float time);
			void AddContact(P6Particle* p1, P6Particle* p2, float restitution, MyVector contactNormal, float depth);

		private:
			void UpdateParticleList();

		protected:
			void GenerateContacts();
			void GetOverlaps(); //get the contacts that overlap
	};
}
