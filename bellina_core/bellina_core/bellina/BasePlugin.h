#pragma once

namespace bl {
	class BasePlugin {
	public:
		BasePlugin() {
			printf("BasePlugin\n");
		}

		// if this is not virtual, then it will not get called
		virtual ~BasePlugin() {
			printf("~BasePlugin\n");
		}
	};
}