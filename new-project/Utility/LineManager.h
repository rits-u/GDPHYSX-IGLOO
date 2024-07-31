#pragma once

#include "RenderLine.h"
#include "list"

namespace utility {
	class LineManager
	{
		public:
			std::list<RenderLine*> Lines;

		public:
			void AddLine(RenderLine* line);
			void DrawLines();

	};

}

