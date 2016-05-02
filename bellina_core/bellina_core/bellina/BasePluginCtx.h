#pragma once

namespace bl {
	class BasePluginCtx {
	public:
		char* _signature = 0;

		BasePluginCtx(char* signature) {
			_signature = _strdup(signature);
			printf("set signature of BasePluginCtx\n");
		}

		virtual void pluginOnNode() = 0;

		virtual ~BasePluginCtx() {			
			if (_signature) {
				delete[] _signature; printf("cleared signature of BasePluginCtx\n");
			}
		}
	};
}