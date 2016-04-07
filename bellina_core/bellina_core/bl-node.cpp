#include "stdafx.h"

#include"g2/g2.h"
#include"bl-node.h"

using namespace g2;
using namespace g2::flags;

using namespace bl;

Node::Node() {
	canvas = 0;
	texture_ = 0;
	mask_ = 0;

	w = h = -1;
	font_name = 0;
	font_size = 24;
	label_ = 0;

	opacity1(1.f);
	opacity2(1.f);
	fontOpacity(1.f);

	pos(0, 0);
	padding(0, 0, 0, 0);

	color1(255, 0, 0);
	color2(255, 0, 0);
	fontColor(255, 255, 255);
	borderColor(255, 0, 255);

	borderThickness(1);

	flags_ = G2_COLOR_SOLID | G2_ALPHA_NONE;
}

void Node::color1(unsigned char _r, unsigned char _g, unsigned char _b) {
	r1 = _r; g1 = _g; b1 = _b;
}

void Node::color2(unsigned char _r, unsigned char _g, unsigned char _b) {
	r2 = _r; g2 = _g; b2 = _b;
}

void Node::borderColor(unsigned char _r, unsigned char _g, unsigned char _b) {
	border_red = _r; border_green = _g; border_blue = _b;
}

void Node::borderThickness(int thickness) {
	border_thickness = thickness;
}

void resetCanvasRef(Node *node, int w, int h) {
	if (node->canvas) delete node->canvas;

	printf("creating canvas %i %i\n", w, h);
	node->canvas = g2::createCanvas(w,h);
}

void Node::dim(int _w, int _h) {
	if (_w != w || _h != h) {
		w = _w; h = _h;
		resetCanvasRef(this, _w, _h);		
	}
	else {
		w = _w; h = _h;
	}
}

void Node::pos(int _x, int _y) {
	x = _x; y = _y;
}

void Node::addKid(Node* kid) {
	kids.push_back(kid);
}

void Node::font(char *name, int size) {
	font_name = _strdup(name);
	font_size = size;

	g2::font(font_name, size);
	fontHeight = g2::font_height();
}

void Node::fontColor(unsigned char r, unsigned char g, unsigned char b) {
	font_red = r; font_green = g; font_blue = b;
}

void Node::fontOpacity(float alpha) {
	font_alpha = alpha;
}

void Node::padding(int l, int t, int r, int b) {
	padding_left = l; padding_top = t; padding_right = r; padding_bottom = b;
}

void Node::label(char *_text) {
	label_ = _strdup(_text);

	if (!font_name) font("arial", font_size);
}

void Node::opacity1(float opacity) {
	alpha1 = opacity;
}

void Node::opacity2(float opacity) {
	alpha2 = opacity;
}

void Node::texture(TextureRef* ref) {
	texture_ = ref;
}

void Node::mask(TextureRef* ref) {
	mask_ = ref;
}

void Node::flags(int _flags) {
	flags_ = _flags;
}

void Node::addFlag(int flag) {
	flags_ ^= flag;
}

void Node::removeFlag(int flag) {
	flags_ &= ~flag;
}

Node::~Node() {
	// font
	if (font_name) delete[] font_name;

	// label
	if (label_) delete[] label_;

	// texture ref
	if (texture_) delete texture_;

	// do not delete mask_

	// canvas ref
	if (canvas) delete canvas;

	// kids
	std::list<Node*>::const_iterator iterator;

	for (iterator = kids.begin(); iterator != kids.end(); ++iterator) {
		Node *kid = *iterator;

		delete kid;
	}
}