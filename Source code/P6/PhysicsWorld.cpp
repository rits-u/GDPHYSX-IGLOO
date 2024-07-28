#include "PhysicsWorld.h"
using namespace P6;

//this method adds the parameter particle to the field list of particles
void PhysicsWorld::AddParticle(P6Particle* toAdd) {
	Particles.push_back(toAdd);
	forceRegistry.Add(toAdd, &Gravity);
}

//this function handles the overall update on every particle added in the list 
void PhysicsWorld::Update(float time) {
	UpdateParticleList();
	forceRegistry.UpdateForces(time);

	int num = 0;

	for (std::list<P6Particle*>::iterator p = Particles.begin();
		p != Particles.end();
		p++
		)
	{
		(*p)->Update(time);
	}

	//GenerateContacts();

	if (Contacts.size() > 0) {
		contactResolver.ResolveContacts(Contacts, time);
	}
}

//this function checks if the particle has exceeded their lifespan, if so, call Destroy() function
void PhysicsWorld::CheckLifespan(float time) {
	for (std::list<P6Particle*>::iterator p = Particles.begin();
		p != Particles.end();
		p++)
	{
		if ((*p)->lifespan <= (int)time - (int)(*p)->spawnTime)
			(*p)->Destroy();
	}
}

void PhysicsWorld::AddContact(P6Particle* p1, P6Particle* p2, float restitution, MyVector contactNormal, float depth) {
	ParticleContact* toAdd = new ParticleContact();

	toAdd->particles[0] = p1;
	toAdd->particles[1] = p2;
	toAdd->restitution = restitution;
	toAdd->contactNormal = contactNormal;
	toAdd->depth = depth;

	Contacts.push_back(toAdd);
}

void PhysicsWorld::GenerateContacts() {
	Contacts.clear();

	//check for overlaps here
	GetOverlaps();

	for (std::list<ParticleLink*>::iterator i = Links.begin();
		i != Links.end();
		i++) {

		ParticleContact* contact = (*i)->GetContact();
		if (contact != nullptr) {
			Contacts.push_back(contact);
		}

	}
}

void PhysicsWorld::GetOverlaps() {

	//iterate through the list upto the 2nd to the last element
	//ex {A, B, C, D} -> iterate from A->C
	for (int i = 0; i < Particles.size() - 1; i++) {
		//you can access the element at index i like this-> Particles[i]
		std::list<P6Particle*>::iterator a = std::next(Particles.begin(), i);

		//start with the next element from above
		//ex {A, B, C, D} -> iterate from B->D
		for (int h = i + 1; h < Particles.size(); h++) {
			//you can access the element at index h like this-> Partciles[h]
			std::list<P6Particle*>::iterator b = std::next(Particles.begin(), h);

			//get the vector from A -> B
			MyVector mag2Vector = (*a)->Position - (*b)->Position;

			//get the square magnitude
			float mag2 = mag2Vector.SquareMagnitude();

			//get the sum of the radius of A and B
			float rad = (*a)->radius + (*b)->radius;

			//square it
			float rad2 = rad * rad;

			//if sq. mag is == to sq. sum | they are touching
			//if sq. mag is < to sq. sum | they are overlapping
			if (mag2 <= rad2) {
				MyVector dir = mag2Vector.normalize();

				//get the depth of the collision
				float r = rad2 - mag2;
				float depth = sqrt(r);
				//fmin gets the lower value between the parameters
				float restitution = fmin((*a)->restitution, (*b)->restitution);

				//add contact
				AddContact(*a, *b, restitution, dir, depth);

			}
		}
	}
}


//this function removes destroyed particles from the list
void PhysicsWorld::UpdateParticleList() {
	Particles.remove_if(
		[](P6Particle* p) {
			return p->IsDestroyed();
		}
	);
}