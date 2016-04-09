#pragma once

namespace bl {
	class FluentFont {

	private:

	public:
		FluentFont* font(char *name, int size);

		FluentFont* color(unsigned char r, unsigned char g, unsigned char b);

		FluentFont* text(char *);

		FluentFont* opacity(float a);
	};
}