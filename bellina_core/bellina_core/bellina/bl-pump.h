#pragma once

namespace bl {
	namespace pump {
		void send();

		void onMouseMove(int mx, int my);
		void onMouseScroll(int amount);
		void onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int mx, int my);
	}
}