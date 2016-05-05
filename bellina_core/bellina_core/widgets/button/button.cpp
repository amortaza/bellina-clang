#include "stdafx.h"

#include "bellina/bellina.h"

#include "button.h"

namespace button {
	Button* This;
}

using namespace button;

void button::begin(char* bid) {

	bl::div(); 
	bl::id("ace");

	This = (Button*) bl::shadows(bid, construct, destruct);

	// set properties
	title("ok");

	//bl::on("node-drag", [](void* e) { printf("green\n"); return true; });

	//bl::on("resize", [](void* e) {printf("resize green\n");return true; });

}

void button::end() {
	// overwrite user properties

	// setup plugins
	if (This->click_cb != nullptr) {
		ClickCallback cb = This->click_cb;

		bl::on("click", [cb](void* data) {
			cb();
			return true;
		});
	}

	render();

	bl::end();
}

void button::render() {
	bl::color(0, 150, 50);
	bl::pos(200, 200);
	bl::dim(160, 120);

	if (This->title) bl::text(This->title);
}

void* button::construct(char* id) {
	Button* b = new Button();

	b->id = _strdup(id);
	b->title = 0;
	b->click_cb = nullptr;

	return b;
}

void button::destruct(void* btn) {
	Button* b = (Button*)btn;

	delete[] b->id;

	if (b->title) delete[] b->title;

	delete b;
}

void button::title(char* t) {
	This->title = t;
}

void button::click(ClickCallback cb) {
	This->click_cb = cb;
}