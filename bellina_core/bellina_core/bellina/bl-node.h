#pragma once

#include <map>

#include "bl-types.h"

namespace g2 { extern class CanvasRef; }
namespace g2 { extern class TextureRef; }

namespace bl { extern class BasePluginCtx; };

using namespace std;

namespace bl {

	class Node {

	public:
		BasePluginCtx* getPluginCtxFromShadow(char* pluginName, char* signature, PluginCtxFactory factory);

	public:
		Point global_pos;

		list<NodeMouseScrollCallback> onMouseScroll_callbacks;
		list<NodeMouseMoveCallback> onMouseMove_callbacks;
		list<NodeMouseDownCallback> onMouseDown_callbacks;
		list<NodeMouseUpCallback> onMouseUp_callbacks;

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
		list<Node*> kids;

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
