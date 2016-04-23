#include "stdafx.h"

#include "bellina/bellina.h"

void Draw();

void Init_OnGL();
void UnInit();

void Render_My_Bellina();

void OnTick() {
	try
	{
		Render_My_Bellina();		
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

	Xel::Window::SetCallbacks(bl::input::onResize, Init_OnGL, UnInit);

	Xel::Mouse::SetCallbacks(
		bl::input::onMouseMove,
		bl::input::onMouseButton,
		bl::input::onMouseScroll);

	Xel::Keyboard::SetCallbacks(
		bl::input::onKeyDown,
		bl::input::onKeyUp);

	Xel::Window::SetTitle("Bellina v0.3.0");
	Xel::Window::SetPosition(720, 100);
	Xel::Window::SetSize(1000, 743);

	Xel::Loop(OnTick);

//	int i; std::cin >> i;
	printf("good bye.\n");	return 0;
}

