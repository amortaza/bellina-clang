#include "stdafx.h"

#include "bellina/bellina.h"
#include "plugins/mouse-in/mouse-in.h"
#include "plugins/click/click.h"

#include "button.h"

namespace button {
	Button* This;

	int State_Default = 0;
	int State_Mouse_Down = 1;	

	void renderText() {

		if (This->state == State_Mouse_Down)
			bl::fontColor(255, 255, 100);
		else
			bl::fontColor(100, 100, 100);
		
		bl::padding(5, 5, 0, 0);
		bl::text(This->title);
	}

	void setupHover() {
		/*bl::on("mouse-in", [](void* data) {
			mouse_in::MouseInOutEvent* e = (mouse_in::MouseInOutEvent*)data;

			if (e->isInEvent)
				This->state = State_In;
			else
				This->state = State_Out;
			
			return true;
		});*/
	}

	void setupClick() {

		bl::onLifeCycle("click", click::lifecycle::mouse_down, [](void* data) {
			//rintf("button mouse down\n");
			This->state = State_Mouse_Down;
			return false;
		});

		bl::onLifeCycle("click", click::lifecycle::mouse_up_and_no_click, [](void* data) {
			//rintf("button mouse up no click\n");
			This->state = State_Default;
			return false;
		});

		/*bl::onLifeCycle("click", click::lifecycle::mouse_drag, [](void* data) {
			printf("button mouse drag\n");
			return false;
		});*/

		if (This->click_cb != nullptr) {
			ClickCallback cb = This->click_cb;

			bl::on("click", [cb](void* data) {
				This->state = State_Default;
				cb();
				return false;
			});
		}
	}
}

using namespace button;

void button::begin(char* bid) {

	bl::div(); 
	bl::id(bid);

	This = (Button*) bl::shadows(bid, construct, destruct);

	// set widget properties
	title("ok");
}

void button::end() {
	// overwrite user properties

	// render before plugin
	render();

	// setup plugins
	setupClick();
	setupHover();

	bl::end();
}

void button::render() {
	bl::color(0, 150, 50);
	bl::pos(200, 200);
	bl::dim(This->w, This->h);

	if (This->title) renderText();

	bl::borderColor(100, 200, 255);
	bl::borderThickness(2);
	bl::border(bl::flags::BL_BORDER_ALL);
}

void* button::construct(char* id) {
	Button* b = new Button();

	b->id = _strdup(id);
	b->title = 0;

	b->click_cb = nullptr;

	b->w = 128;
	b->h = 64;

	b->state = State_Default;

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

void button::dim(int w, int h) {
	This->w = w;
	This->h = h;
}