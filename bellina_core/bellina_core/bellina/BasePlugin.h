#pragma once

namespace bl {
	class BasePlugin {
	public:
		BasePlugin() {
		}

		// if this is not virtual, then it will not get called
		virtual ~BasePlugin() {
		}
	};
}