#include "stdafx.h"

#include <chrono>

#include "bellina/bellina.h"

#include "../click/click.h"
#include "double-click.h"

using namespace bl;
using namespace bl::listener;
using namespace click;
using namespace std::chrono;

namespace double_click {
	
	char* plugin_name = "double-click";

	char* lastClickNodeId = 0;
	Xel::Mouse::Button lastClickButton;
	milliseconds lastClickMs;
	int maxDurationMs = 750;

	void freeId() {
		if (lastClickNodeId) {
			delete[] lastClickNodeId;
			lastClickNodeId = 0;
		}
	}

	void init() {
		if (bl::pluginHasInt(plugin_name, "duration")) {
			maxDurationMs = bl::pluginGetInt(plugin_name, "duration");
		}
	}

	void uninit() {
		freeId();
	}

	void onNode() {

		bl::on("click", [](void* e) {

			click::MouseClickEvent* event = (click::MouseClickEvent*) e;
			
			if (lastClickNodeId && bl::util::isNode(bl::node, lastClickNodeId) && event->button == lastClickButton) {
				milliseconds diff = duration_cast<milliseconds>(system_clock::now().time_since_epoch()) - lastClickMs;

				if (diff.count() < maxDurationMs) {
					bl::pluginCall(plugin_name, bl::node, event);
					fire(plugin_name, event);
				}

				freeId();
			}
			else {
				freeId();

				lastClickNodeId = _strdup(bl::node->nid);
				lastClickButton = event->button;
				lastClickMs = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			}
			
			return true;
		});
	}
}

void double_click::load() {
	bl::pluginLoad(click::load);

	bl::pluginRegister(
		double_click::plugin_name,
		double_click::init,
		double_click::onNode,
		double_click::uninit);
}