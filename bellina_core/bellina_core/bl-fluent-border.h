#pragma once

namespace bl {
	class FluentBorder {

	private:
		unsigned int border_flag;

	public:
		FluentBorder* border(unsigned int borderFlag);

		FluentBorder* color(unsigned char r, unsigned char g, unsigned char b);

		FluentBorder* thickness(int t);

		FluentBorder* tops(bool b);

		FluentBorder* opacity(float a);
	};
}