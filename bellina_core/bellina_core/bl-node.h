#pragma once

namespace bl {
	class Node {
	private:
	public:
		int x, y;
		int w, h;
		unsigned char r, g, b;

		g2::CanvasRef* canvasRef;

		std::list<Node*> kids;

		Node();
		~Node();

		void pos(int _x, int _y);
		void dim(int _w, int _h);
		void color(unsigned char r, unsigned char g, unsigned char b);

		void addKid(Node *);
	};
}
