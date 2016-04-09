#include "stdafx.h"

#include "bellina/bellina.h"

#include "main.h"

void Render_My_Bellina();

void OnTick() {
	try
	{
		Render_My_Bellina();

		bl::paint();
	}
	catch (char* msg) {
		printf(msg);
		printf("\n");
	}

	Xel::Swap();
}

int main(int argc, char** argv) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Xel::Init();

	Xel::Window::SetCallbacks(bl::ui::onResize, Init_OnGL, UnInit);

	Xel::Mouse::SetCallbacks(
		bl::ui::onMouseMove,
		bl::ui::onMouseButton,
		bl::ui::onMouseScroll);

	Xel::Keyboard::SetCallbacks(
		bl::ui::onKeyDown,
		bl::ui::onKeyUp);

	Xel::Window::SetTitle("Bellina v0.2.0");
	Xel::Window::SetPosition(200, 100);
	Xel::Window::SetSize(1300, 843);

	Xel::Loop(OnTick);

	//int i; std::cin >> i;
	printf("good bye.\n");	return 0;
}

