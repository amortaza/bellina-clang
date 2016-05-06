#pragma once

#include "Xel/Xel.h"
#include "pango/pango.h"
#include "bl-types.h"

namespace g2 { extern class TextureRef; }

namespace bl { extern class FluentBorder; }
namespace bl { extern class FluentFont; }

namespace bl { extern class Node; }
namespace bl { extern class ShadowNode; }

using namespace bl;
using namespace pango;

namespace bl {	

	void root();	

	ShadowNode* get_shadow();
	void shadow(ShadowCallback);

	void listenShortTerm(char* eventName, ListenerCallback eventCallback);
	void listenLongTerm(char* eventName, ListenerCallback eventCallback);

	void fire(char* eventName, void* eventData);

	void init();
	void uninit();	

	// default signature
	void use(char* pluginName);
	void on(char* pluginName, PluginCallback cb);

	void onLifeCycle(char* pluginName, char* signature, char* lifeCycle, PluginCallback cb);
	void onLifeCycle(char* pluginName,                  char* lifeCycle, PluginCallback cb);

	void use(char* pluginName, char* signature, PluginCtxFactory factory);
	void on( char* pluginName, char* signature, PluginCtxFactory factory, PluginCallback cb);		

	void pluginCtxOnNode(char* pluginName, char* signature, PluginCtxFactory);

	void pluginCall(char* pluginName, char* signature, char* lifeCycle, Node* node, void* eventData);

	Node* div();
	void end();

	void paint();

	Node* current();

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
	void onMouseMove(NodeMouseMoveCallback);
	void onMouseDown(NodeMouseDownCallback);
	void onMouseUp(NodeMouseUpCallback);
	void onMouseScroll(NodeMouseScrollCallback);

	void onMouseMoveOnNode(Node*,NodeMouseMoveCallback);
	void onMouseDownOnNode(Node*, NodeMouseDownCallback);
	void onMouseUpOnNode(Node*, NodeMouseUpCallback);
	void onMouseScrollOnNode(Node*, NodeMouseScrollCallback);
}
