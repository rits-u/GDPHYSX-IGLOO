#pragma once

#include "Model3D.h"
#include "list"

namespace model {
	class ModelManager
	{
		public:
			std::list<Model3D*> Models;
			void AddModel(Model3D* toAdd);
			void checkModels(); //DEBUGGING ONLY
	};

}