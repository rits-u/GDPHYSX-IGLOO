#include "ModelManager.h"
using namespace model;

//this method adds the model from the parameter to the field list of models
void ModelManager::AddModel(Model3D* toAdd) {
	Models.push_back(toAdd);
}