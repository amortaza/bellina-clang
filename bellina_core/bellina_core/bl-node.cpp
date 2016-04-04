#include "stdafx.h"
#include <list>

#include"g2.h"
#include"bl-node.h"

using namespace bl;

Node::Node() {
	canvasRef = 0;
	w = h = -1;
	font_name = 0;
	font_size = 24;
	text = 0;
	alpha1 = alpha2 = 1.f;
	opacityDir = 0;

	pos(0, 0);
	color(255, 0, 0);
}

void Node::color(unsigned char _r, unsigned char _g, unsigned char _b) {
	r = _r; g = _g; b = _b;
}

void resetCanvasRef(Node *node, int w, int h) {
	if (node->canvasRef) delete node->canvasRef;

	printf("creating canvas %i %i\n", w, h);
	node->canvasRef = g2::createCanvas(w,h);
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
	textY = g2::font_height();
}

void Node::label(char *_text) {
	text = _strdup(_text);

	if (!font_name) font("arial", font_size);
}

void Node::opacity(float opacity) {
	alpha1 = opacity;
}

void Node::opacityDir(int dir, float opacity2) {
	alphaDir = dir;
	alpha2 = opacity2;
}

Node::~Node() {
	// font
	if (font_name) delete[] font_name;
	if (text) delete[] text;

	// canvas ref
	if (canvasRef) delete canvasRef;

	// kids
	std::list<Node*>::const_iterator iterator;

	for (iterator = kids.begin(); iterator != kids.end(); ++iterator) {
		Node *kid = *iterator;

		delete kid;
	}
}