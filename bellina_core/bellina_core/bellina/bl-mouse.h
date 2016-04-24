#pragma

namespace bl {
	namespace mouse {
		void updateSysMouse(int mx, int my);

		void bl_onMouseMove(int mx, int my);
		void bl_onMouseScroll(int amount);
		void bl_onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int mx, int my);
	}
}