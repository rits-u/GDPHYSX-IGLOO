#include "ModelManager.h"
using namespace model;

void ModelManager::AddModel(Model3D* toAdd) {
	Models.push_back(toAdd);
}

void ModelManager::checkModels() {
	int num = 0;
	for (std::list<Model3D*>::iterator p = Models.begin();

		p != Models.end();

		p++
		)
	{
		//(*p)->Update(time);

		if (num >= 6) {
			num = 1;

		}
		else {
			num++;
		}
		//if (p == )
			//std::cout << "NULL " << std::endl;
		
	//	std::cout << num << " model: " << (*p)->getPosition() << std::endl;
	}


}