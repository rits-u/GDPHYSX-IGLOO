#pragma once

#include "../ForceGenerator.h"
#include "../MyVector.h"

namespace P6 {
	class AnchoredSpring : public ForceGenerator
	{
	public:
		AnchoredSpring(MyVector pos, float _springConst, float _restLen) :
			anchorPoint(pos), springConstant(_springConst), restLength(_restLen) {}

		void UpdateForce(P6Particle* particle, float time) override;

	private:
		//this is where the spring is attached
		MyVector anchorPoint;

		float springConstant; //how hard your spring is

		float restLength; //length of the spring at rest
	};

}

