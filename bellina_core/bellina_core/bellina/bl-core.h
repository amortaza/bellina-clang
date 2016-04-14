#pragma once

#include <functional>

#include "Xel/Xel.h"

#include "bl-plugin.h" // too complicated to comment out

namespace g2 { extern class TextureRef; }

namespace bl { extern class FluentBorder; }
namespace bl { extern class FluentFont; }
namespace bl { extern class Node; }

using namespace bl;
using namespace bl::plug;

namespace bl {
	typedef std::function<void(void*)> EventCallback;

	void listen(char* event_name, EventCallback event_callback);
	void fire(char* event_name, void* event_data);

	void init();
	void uninit();	

	void plugin(char* name, PluginInit plugin_init, PluginTick plugin_tick, PluginUninit plugin_uninit );
	void use(char* name);

	Node* div();
	void end();

	void paint();

	// node control
	void id(char*);

	void pos(int _x, int _y);
	void dim(int _w, int _h);

	void color(unsigned char r, unsigned char g, unsigned char b);
	void color2(unsigned char r, unsigned char g, unsigned char b);

	void canvasOpacity(float);
	void canvasOpacity2(float);	

	void texture(g2::TextureRef*);
	void mask(g2::TextureRef*);

	void padding(int l, int t, int r, int b);

	FluentBorder* border(unsigned int borderFlag);
	
	void borderColor(unsigned char r, unsigned char g, unsigned char b);
	void borderThickness(int t);
	void borderTops(bool b);
	void borderOpacity(float a);

	FluentFont* font(char *name, int size);
	FluentFont* fontColor(unsigned char r, unsigned char g, unsigned char b);
	FluentFont* text(char *);
	FluentFont* fontOpacity(float);

	void resetFlags(int);
	void addFlag(int);
	void removeFlag(int);

	void labelTops(bool);

	void setColorSolidFlag();
	void setColorHorizGradientFlag();
	void setColorVertGradientFlag();

	void setTextureFlag();

	// input
	void enable(int callbackFlag);
	void disable(int callbackFlag);	

	void onMouseMove(std::function<void(int mx, int my, Node* bubbledFrom)>);
	void onMouseDown(std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)>);
	void onMouseUp(std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)>);
	void onMouseScroll(std::function<void(int amount, int mx, int my, Node* bubbledFrom)>);

	void onKeyDown(std::function<void(unsigned long long xcode, Node* bubbledFrom)>);
	void onKeyUp(std::function<void(unsigned long long xcode, Node* bubbledFrom)>);
}
