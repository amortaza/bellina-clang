#include "stdafx.h"

#include "bl-core.h"
#include "bl-listener.h"

using namespace bl;
using namespace bl::listener;

namespace bl {
	namespace listener {
		std::map<std::string, std::list<ListenerCallback>*> listenerRegistry;

		namespace _ {
			std::list<Node*> key_down_registry;
			std::list<Node*> key_up_registry;
		}
	}
}

void bl::listen(char* event_name, bl::ListenerCallback event_callback) {
	std::string key = std::string(event_name);

	std::list<ListenerCallback>* callbacks;

	auto e2 = listenerRegistry.find(key);

	if (e2 == listenerRegistry.end()) {
		callbacks = new std::list<ListenerCallback>();
		listenerRegistry[key] = callbacks;

	}
	else {
		callbacks = e2->second;
	}

	callbacks->push_back(event_callback);
}

void bl::fire(char* event_name, void* event_data) {
	std::string key = std::string(event_name);

	std::list<ListenerCallback>* callbacks;

	auto e2 = listenerRegistry.find(key);

	if (e2 != listenerRegistry.end()) {
		callbacks = e2->second;

		std::list<ListenerCallback>::const_iterator iterator;

		for (iterator = callbacks->begin(); iterator != callbacks->end(); ++iterator) {
			ListenerCallback cb = *iterator;

			cb(event_data);
		}
	}
}

void bl::listener::uninit() {
	typedef std::map<std::string, std::list<ListenerCallback>*>::iterator it1;
	for (it1 it = listenerRegistry.begin(); it != listenerRegistry.end(); it++) {
		std::list<ListenerCallback>* callbacks = it->second;

		delete callbacks;
	}
}
