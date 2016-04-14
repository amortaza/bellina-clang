#pragma once

#include <functional>

#include "g2/g2.h"
//#include "bl-core.h" // including this causing error

namespace bl {
	struct BorderSide {
		unsigned char red, green, blue;
		int thickness;
		float alpha;
		bool topsCanvas;
	};

	struct Point {
		int x, y;
	};

	class Node {

	public:
		Point global_pos;

		bool callback_onKeyUp_enabled_bubble;
		std::function<void(unsigned long long xcode, Node* bubbledFrom)> callback_onKeyUp;

		bool callback_onKeyDown_enabled_bubble;
		std::function<void(unsigned long long xcode, Node* bubbledFrom)> callback_onKeyDown;

		bool callback_onMouseScroll_enabled_bubble;
		std::function<void(int amount, int mx, int my, Node* bubbledFrom)> callback_onMouseScroll;

		bool callback_onMouseMove_enabled_bubble;
		std::function<void(int mx, int my, Node* bubbledFrom)> callback_onMouseMove;

		bool callback_onMouseDown_enabled_bubble;
		std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> callback_onMouseDown;

		bool callback_onMouseUp_enabled_bubble;
		std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> callback_onMouseUp;

		char* nid;

		int x, y;
		int w, h;
		
		unsigned char r1, g1, b1;
		unsigned char r2, g2, b2;
		unsigned char font_red, font_green, font_blue;

		float alpha1_canvas, alpha2_canvas;
		float font_alpha;

		g2::TextureRef* texture_;
		g2::TextureRef* mask_;

		// affects texture
		//         label
		int padding_left, padding_top, padding_right, padding_bottom;

		BorderSide border_left, border_top, border_right, border_bottom;

		int flags;

		char* label_;
		char* font_name;
		int font_size;

		bool label_tops_canvas;

		Node* parent;
		std::list<Node*> kids;

	public:
		g2::CanvasRef* canvas;
		int fontHeight;

		Node(Node *parent_);
		~Node();

		void id(char*);

		void pos(int _x, int _y);
		void dim(int _w, int _h);

		void color1(unsigned char r, unsigned char g, unsigned char b);
		void color2(unsigned char r, unsigned char g, unsigned char b);

		void canvasOpacity1(float);
		void canvasOpacity2(float);
		void fontOpacity(float);		

		void texture(g2::TextureRef*);
		void mask(g2::TextureRef*);

		void padding(int l, int t, int r, int b);

		void borderColor(unsigned int border_flag, unsigned char r, unsigned char g, unsigned char b);
		void borderThickness(unsigned int border_flag, int);
		void borderTops(unsigned int border_flag, bool);
		void borderOpacity(unsigned int border_flag, float);

		void font(char *name, int size);
		void fontColor(unsigned char r, unsigned char g, unsigned char b);
		void label(char *);

		void addKid(Node *);

		void resetFlags(int);
		void addFlag(int);
		void removeFlag(int);

		void labelTops(bool);		

		void setColorSolidFlag();
		void setColorHorizGradientFlag();
		void setColorVertGradientFlag();

		void setTextureFlag();
	};
}
