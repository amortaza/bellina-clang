#pragma once

namespace bl {
	class Widget {
	public:
		char* id;

	public:
		Widget(char* id_);

		virtual ~Widget();
	};
}
