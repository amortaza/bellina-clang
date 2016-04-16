#pragma once

#include "Xel/Xel.h"

#include "bl-plugin.h" // too complicated to comment out
#include "bl-types.h"

namespace g2 { extern class TextureRef; }

namespace bl { extern class FluentBorder; }
namespace bl { extern class FluentFont; }
namespace bl { extern class Node; }

using namespace bl;
using namespace bl::plugin;

namespace bl {	

	void root();

	void listenShortTerm(char* eventName, ListenerCallback eventCallback);
	void listenLongTerm(char* eventName, ListenerCallback eventCallback);

	//? void listen(char* eventName, ListenerCallback eventCallback);

	void fire(char* eventName, void* eventData);
	//? void fireAt(char* eventName, void* eventData);	

	void init();
	void uninit();	

	void use(char* plugin_name);
	void on(char* plugin_name, PluginCallback cb);

	void pluginLoad(char* plugin_name, PluginInit, PluginOnNode, PluginTick, PluginUninit);
	void pluginSetInt(char* plugin_name, char* prop_name, int value);
	int  pluginGetInt(char* plugin_name, char* prop_name);

	Node* div();
	void end();

	void tick();
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

	void onMouseMove(NodeMouseMoveCallback);
	void onMouseDown(NodeMouseDownCallback);
	void onMouseUp(NodeMouseUpCallback);
	void onMouseScroll(NodeMouseScrollCallback);
}
