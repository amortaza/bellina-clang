#pragma once

namespace bl {
	class BasePluginCtx {
	public:

		virtual void onNode(char* signature) = 0;
		virtual ~BasePluginCtx() {}
	};
}