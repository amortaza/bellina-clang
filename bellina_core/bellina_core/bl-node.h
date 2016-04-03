#pragma once

namespace bl {
	class Node {
	private:
	public:
		int w, h;
		unsigned char r, g, b;

		Node();

		void dim(int _w, int _h);
		void color(unsigned char r, unsigned char g, unsigned char b);
	};
}
