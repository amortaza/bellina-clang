#pragma once

#include <list>
#include "g2/g2.h"

namespace bl {
	class Node {

	public:
		int x, y;
		int w, h;
		
		unsigned char r1, g1, b1;
		unsigned char r2, g2, b2;
		unsigned char font_red, font_green, font_blue;

		float alpha1, alpha2;
		float font_alpha;

		g2::TextureRef* texture_;
		g2::TextureRef* mask_;

		// affects texture
		//         label
		int padding_left, padding_top, padding_right, padding_bottom;

		unsigned char border_red, border_green, border_blue;
		int border_thickness;

		int flags_;

		char* label_;
		char* font_name;
		int font_size;

		std::list<Node*> kids;

	public:
		g2::CanvasRef* canvas;
		int fontHeight;

		Node();
		~Node();

		void pos(int _x, int _y);
		void dim(int _w, int _h);

		void color1(unsigned char r, unsigned char g, unsigned char b);
		void color2(unsigned char r, unsigned char g, unsigned char b);

		void opacity1(float);
		void opacity2(float);
		void fontOpacity(float);

		void texture(g2::TextureRef*);
		void mask(g2::TextureRef*);

		void padding(int l, int t, int r, int b);

		void borderColor(unsigned char r, unsigned char g, unsigned char b);
		void borderThickness(int);

		void font(char *name, int size);
		void fontColor(unsigned char r, unsigned char g, unsigned char b);
		void label(char *);

		void addKid(Node *);

		void flags(int);
		void addFlag(int);
		void removeFlag(int);
	};
}
