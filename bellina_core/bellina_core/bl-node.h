#pragma once

#include <list>
#include "g2.h"

namespace bl {
	class Node {
	private:
	public:
		int x, y;
		int w, h;
		unsigned char r, g, b;

		char* text;
		char* font_name;
		int font_size;

		float alpha1, alpha2;
		int alphaDir; // 0 none, 1: horiz, 2: vert

		std::list<Node*> kids;

	public:
		g2::CanvasRef* canvasRef;
		int textY;

		Node();
		~Node();

		void pos(int _x, int _y);
		void dim(int _w, int _h);
		void color(unsigned char r, unsigned char g, unsigned char b);

		void font(char *name, int size);
		void label(char *);

		void opacity(float);
		void opacityDir(int, float);

		void addKid(Node *);
	};
}
