#include "stdafx.h"

#include "bellina/bellina.h"

#include "button.h"

using namespace button;

void button::begin() {

	 bl::div(); {
		 //bl::shadowId("green");

		 // set properties

		 

		 bl::color(0, 150, 50);
		 bl::pos(200, 200);
		 bl::dim(160, 120);

		 bl::text("Ok, bellina!");

		 //bl::on("node-drag", [](void* e) { printf("green\n"); return true; });

		 //bl::on("resize", [](void* e) {printf("resize green\n");return true; });
	 }
	 bl::end();
}

void button::end() {

}

Button* button::construct(char* id) {
	Button* b = new Button();

	b->id = _strdup(id);

	return b;
}

void button::destruct(Button* b) {
	delete[] b->id;

	delete b;
}