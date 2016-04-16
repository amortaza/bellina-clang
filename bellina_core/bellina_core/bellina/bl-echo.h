#pragma once

#include <map>
#include <list>
#include <functional>

#include "bl-types.h"

namespace bl { extern class Node; }

namespace bl {
	namespace echo {

		class Echo {

		public:
			~Echo();

			void fire(char* eventName, void*eventData);
			void listen(char* eventName, ListenerCallback callback);

		private:
			std::map<std::string, std::list<ListenerCallback>*> listenerRegistry;
		};
	}
}