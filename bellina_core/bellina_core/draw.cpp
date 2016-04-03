#include "stdafx.h"
#include "g2.h"

void Draw() {
	int winW = Xel::Window::width;
	int winH = Xel::Window::height;

	g2::viewport(winW, winH);
	g2::ortho(winW, winH);

	g2::clear();

}