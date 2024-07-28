#include "ParticleContact.h"

using namespace P6;

float ParticleContact::GetSeparatingSpeed()
{
    //Av
    MyVector velocity = particles[0]->Velocity;

    if (particles[1]) {
        velocity -= particles[1]->Velocity;
    }

    //idk if correct
   // return velocity.getDotProduct(velocity,contactNormal);
    return velocity.scalarProduct(contactNormal);
}

void ParticleContact::ResolveVelocity(float time)
{
    //sS
    float separatingSpeed = GetSeparatingSpeed();

    //if obj is already moving away from each other- skip
   if(separatingSpeed > 0) 
   {
    return;
   } 

   float newSS = -restitution * separatingSpeed;
   //mag of our delta velocity
   float deltaSpeed = newSS - separatingSpeed;

    //get total inverse mass of collsing particles
    //apply impulse based on this later
   float totalMass = (float)1/ particles[0]->mass;
   if (particles[1]) 
       totalMass += (float)1 / particles[1]->mass;

   //Invalid collision if total mass is 0 or less
   if(totalMass <= 0) 
      return;

   //mag of impuls eneeded to apply in collison
   float impulse_mag = deltaSpeed / totalMass;

   //get impulse vector using contact normal
   MyVector Impulse = contactNormal * impulse_mag;

   //chang in V for Particle A
   MyVector V_a = Impulse * ((float)1/ particles[0]->mass);
   particles[0]->Velocity = particles[0]->Velocity + V_a;

   if (particles[1])
   {
        //Apply impulse in the opposite direction for B
        MyVector V_b = Impulse * ((float)-1 / particles[1]->mass);
        particles[1]->Velocity = particles[1]->Velocity + V_b;
   }
}

void ParticleContact::Resolve(float time){
    
    //v after coll
    ResolveVelocity(time);

    //pos after coll
    //Resolve interpenetration here order that matter much
    ResolveInterpenertration(time);

}


//add here first
void ParticleContact::ResolveInterpenertration(float time)
{
    //do nothing if depth is 0 or lower == barely touch
    if (depth <= 0) 
        return;

    //total mass of collisions
    float totalMass = (float) 1 / particles[0]->mass;
    if(particles[1]) 
       totalMass += (float)1 / particles[1]->mass;

//invalid collison if total mass is 0 or less
    if (totalMass <= 0 ) 
       return;

    //higher mass == less likely for the particle to move
        //how much to move / how many units to move per total mass
    float totalMoveByMass = depth / totalMass;

    //directionf of the mmovement
    //how much to move and where // get vector of total movement involved
    MyVector moveByMass = contactNormal * totalMoveByMass;

    //get the change in position for A
    MyVector P_a = moveByMass * ((float) 1 / particles[0]->mass);
   
   //translate A
    particles[0]->Position += P_a;

    if (particles[1])
    {
        //get the change in pos for B in the opp dir
        MyVector P_b = moveByMass * (-(float) 1 / particles[1]->mass);
       //Translete for B
        particles[1]->Position += P_b;
    }

    //restart, after solving - assume depth is now 0
    depth = 0;

}