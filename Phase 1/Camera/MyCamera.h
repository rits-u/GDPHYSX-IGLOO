#pragma once

namespace camera {
	class MyCamera
	{
		protected:
			float z_far;
			float z_near;

		public:
			MyCamera();

		public:
			void set_zFar(float z_far);
			void set_zNear(float z_near);
		};

}