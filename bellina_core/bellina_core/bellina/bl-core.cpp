#include "stdafx.h"

#include "eos/eos.h"

#include "bl-core.h"
#include "bl-extern.h"
#include "bl-sys.h"
#include "bl-plugin.h"

using namespace g2::flags;

using namespace bl;
using namespace bl::_;
using namespace bl::flags;
using namespace bl::sys;

void bl::onMouseScroll(std::function<void(int amount, int mx, int my, Node* bubbledFrom)> cb) {
	current_node->callback_onMouseScroll = cb;
}

void bl::onMouseUp(std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> cb) {
	current_node->callback_onMouseUp = cb;
}

void bl::onMouseDown(std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> cb) {
	current_node->callback_onMouseDown = cb;
}

void bl::onClick(std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> cb) {
	current_node->callback_onClick = cb;
}

void bl::onMouseMove(std::function<void(int mx, int my, Node* bubbledFrom)> cb) {
	current_node->callback_onMouseMove = cb;
}

void bl::onKeyDown(std::function<void(unsigned long long xcode, Node* bubbledFrom)> cb) {
	current_node->callback_onKeyDown = cb;
	key_down_registry.push_back(current_node);
}

void bl::onKeyUp(std::function<void(unsigned long long xcode, Node* bubbledFrom)> cb) {
	current_node->callback_onKeyUp = cb;
	key_up_registry.push_back(current_node);
}

void bl::enable(int callbackFlag) {
	if (callbackFlag & BL_MOUSE_MOVE_BUBBLE) current_node->callback_onMouseMove_enabled_bubble = true;
	if (callbackFlag & BL_MOUSE_DOWN_BUBBLE) current_node->callback_onMouseDown_enabled_bubble = true;
	if (callbackFlag & BL_MOUSE_UP_BUBBLE) current_node->callback_onMouseUp_enabled_bubble = true;
	if (callbackFlag & BL_MOUSE_SCROLL_BUBBLE) current_node->callback_onMouseScroll_enabled_bubble = true;
	if (callbackFlag & BL_KEY_DOWN_BUBBLE) current_node->callback_onKeyDown_enabled_bubble = true;
	if (callbackFlag & BL_KEY_UP_BUBBLE) current_node->callback_onKeyUp_enabled_bubble = true;
}

void bl::disable(int callbackFlag) {
	if (callbackFlag & BL_MOUSE_MOVE_BUBBLE) current_node->callback_onMouseMove_enabled_bubble = false;
	if (callbackFlag & BL_MOUSE_DOWN_BUBBLE) current_node->callback_onMouseDown_enabled_bubble = false;
	if (callbackFlag & BL_MOUSE_UP_BUBBLE) current_node->callback_onMouseUp_enabled_bubble = false;
	if (callbackFlag & BL_MOUSE_SCROLL_BUBBLE) current_node->callback_onMouseScroll_enabled_bubble = false;
	if (callbackFlag & BL_KEY_DOWN_BUBBLE) current_node->callback_onKeyDown_enabled_bubble = false;
	if (callbackFlag & BL_KEY_UP_BUBBLE) current_node->callback_onKeyUp_enabled_bubble = false;
}

Node* bl::nd() {
	Node* parent = current_node;

	current_node = new Node(parent);

	if (parent) {
		parent->addKid(current_node);
		nodeStack.push(parent);
	}

	return current_node;
}

void bl::end() {
	// validate that if mouse_click event is being captured that there is ID required
	if (current_node && current_node->callback_onClick != nullptr) {
		if (current_node->nid == 0) {
			char* msg = "a node which has onClick event handler does NOT have ID...ID is required.\n";
			printf(msg);
			throw msg;
		}
	}
	if (nodeStack.size() > 0) {
		//printf("size %i\n", nodeStack.size());
		current_node = nodeStack.top();
		nodeStack.pop();
	}
	else
		current_node = 0;
}

void bl::id(char* nid) {
	current_node->id(nid);
}

void bl::focus() {
	//bl::focus_node_id = _strdup(current_node->nid);
}

void bl::pos(int x, int y) {
	current_node->pos(x, y);
}

void bl::dim(int w, int h) {
	current_node->dim(w,h);
}

void bl::color(unsigned char r, unsigned char g, unsigned char b) {
	current_node->color1(r, g, b);
}

void bl::color2(unsigned char r, unsigned char g, unsigned char b) {
	current_node->color2(r, g, b);
}

void bl::canvasOpacity(float alpha) {
	current_node->canvasOpacity1(alpha);
}

void bl::canvasOpacity2(float a) {
	current_node->canvasOpacity2(a);
}

void bl::texture(g2::TextureRef* t) {
	current_node->texture(t);
}

void bl::mask(g2::TextureRef*t) {
	current_node->mask(t);
}

void bl::padding(int l, int t, int r, int b) {
	current_node->padding(l, t, r, b);
}

FluentBorder* bl::border(unsigned int border_flag_) {
	border_flag = border_flag_;
	addFlag(border_flag_);

	return &fluent_border;
}

void bl::borderColor(unsigned char r, unsigned char g, unsigned char b) {
	current_node->borderColor(border_flag, r, g, b);
}

void bl::borderThickness(int t) {
	current_node->borderThickness(border_flag, t);
}

void bl::borderTops(bool b) {
	current_node->borderTops(border_flag, b);
}

void bl::borderOpacity(float a) {
	current_node->borderOpacity(border_flag,a);
}

FluentFont* bl::fontOpacity(float a) {
	current_node->fontOpacity(a);

	return &fluent_font;
}

FluentFont* bl::font(char *name, int size) {
	current_node->font(name, size);

	return &fluent_font;
}

FluentFont* bl::fontColor(unsigned char r, unsigned char g, unsigned char b) {
	current_node->fontColor(r, g, b);

	return &fluent_font;
}

FluentFont* bl::text(char *label) {
	current_node->label(label);

	return &fluent_font;
}


void bl::resetFlags(int f) {
	current_node->resetFlags(f);
}

void bl::addFlag(int f) {
	current_node->addFlag(f);
}

void bl::removeFlag(int f) {
	current_node->removeFlag(f);
}


void bl::labelTops(bool b) {
	current_node->labelTops(b);
}

void bl::setColorSolidFlag() {
	current_node->setColorSolidFlag();
}

void bl::setColorHorizGradientFlag() {
	current_node->setColorHorizGradientFlag();
}

void bl::setColorVertGradientFlag() {
	current_node->setColorVertGradientFlag();
}


void bl::setTextureFlag() {
	current_node->setTextureFlag();
}

void bl::init() {
	g2::init();

	// window not available yet
	root = 0;
}

using namespace bl::plug;

void bl::uninit() {
	if (root) delete root;
	if (last_mouse_down_node_id) delete[] last_mouse_down_node_id;
	if (focus_node_id) delete[] focus_node_id;

	typedef std::map<std::string, Plugin*>::iterator it1;
	for (it1 it = pluginMap.begin(); it != pluginMap.end(); it++) {
		Plugin* plugin = it->second;

		if (plugin->uninit != nullptr) plugin->uninit();

		delete plugin;
	}

	bl::event::uninit();

	g2::uninit();
}

