#pragma once

namespace pango {
	class BasePluginCtx {
	public:
		char* _signature = 0;

		BasePluginCtx(char* signature) {
			_signature = _strdup(signature);
		}

		virtual ~BasePluginCtx() {
			if (_signature) delete[] _signature;
		}

		virtual void pluginOnNode() = 0;		
	};
}