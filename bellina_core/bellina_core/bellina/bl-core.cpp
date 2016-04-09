#include "stdafx.h"

#include "g2/g2.h"

#include "bl-core.h"
#include "bl-extern.h"

using namespace bl;
using namespace bl::Internal;
using namespace bl::flags;

void bl::onMouseMove(std::function<void(int mx, int my)> cb) {
	current_node->callback_onMouseMove = cb;
	current_node->callback_onMouseMove_enabled = true;
}

void bl::enable(int callbackFlag) {
	if (callbackFlag & BL_MOUSE_MOVE) current_node->callback_onMouseMove_enabled = true;
}

void bl::disable(int callbackFlag) {
	if (callbackFlag & BL_MOUSE_MOVE) 
		current_node->callback_onMouseMove_enabled = false;
}

void bl::init() {
	g2::init();

	// window not available yet
	root = 0;
}

void bl::uninit() {
	if (root) {
		printf("deleting root at uninit\n"); 
		delete root; 
		root = 0;
	}

	g2::uninit();
}

Node* bl::nd() {
	Node* parent = current_node;

	current_node = new Node(parent);

	if (parent) parent->addKid(current_node);

	return current_node;
}

void bl::end() {
	if (nodeStack.size() > 0) {
		current_node = nodeStack.top();
		nodeStack.pop();
	}
	else
		current_node = 0;
}

void bl::id(char* nid) {
	current_node->id(nid);
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

