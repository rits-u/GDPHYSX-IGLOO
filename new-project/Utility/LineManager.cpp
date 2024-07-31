#include "LineManager.h"
using namespace utility;

void LineManager::AddLine(RenderLine* line) {
	this->Lines.push_back(line);
}

void LineManager::DrawLines() {
    for (std::list<RenderLine*>::iterator i = this->Lines.begin();
        i != this->Lines.end();
        i++
        ) {

      //  (*i)->Update();
        (*i)->Draw();
    }
}
