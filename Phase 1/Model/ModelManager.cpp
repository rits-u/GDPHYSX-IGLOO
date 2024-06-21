#include "ModelManager.h"
using namespace model;

//this method adds the model from the parameter to the field list of models
void ModelManager::AddModel(Model3D* toAdd) {
	Models.push_back(toAdd);
}

//this method gets the y-position of the model, this was used for debugging
void ModelManager::checkModels() {
	int num = 0;
	for (std::list<Model3D*>::iterator p = Models.begin();

		p != Models.end();

		p++
		)
	{

		if (num >= 6) {
			num = 1;

		}
		else {
			num++;
		}
		
		std::cout << num << " model: " << (*p)->getPosition() << std::endl;
	}


}