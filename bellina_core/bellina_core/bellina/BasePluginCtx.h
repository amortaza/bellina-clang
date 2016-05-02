#pragma once

namespace bl {
	class BasePluginCtx {
	public:
		char* _signature = 0;

		BasePluginCtx(char* signature) {
			_signature = _strdup(signature);
			//rintf("set signature of BasePluginCtx %s\n", _signature);
		}

		virtual void pluginOnNode() = 0;

		virtual ~BasePluginCtx() {			
			if (_signature) {
				delete[] _signature; 
				printf("cleared signature of BasePluginCtx\n");
			}
		}
	};
}