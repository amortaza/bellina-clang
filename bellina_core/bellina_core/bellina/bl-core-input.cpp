#include "stdafx.h"

#include "bl-listener.h"
#include "bl-globals.h"
#include "bl-core.h"
#include "bl-globals.h"
#include "bl-sys.h"
#include "bl-plugin.h"
#include "bl-flags.h"
#include "bl-node.h"

using namespace bl;
using namespace bl::_;
using namespace bl::flags;
using namespace bl::sys;

using namespace bl::listener::_;

void bl::onMouseScroll(MouseScrollCallback cb) {
	current_node->callback_onMouseScroll = cb;
}

void bl::onMouseUp(MouseUpCallback cb) {
	current_node->callback_onMouseUp = cb;
}

void bl::onMouseDown(MouseDownCallback cb) {
	current_node->callback_onMouseDown = cb;
}

void bl::onMouseMove(MouseMoveCallback cb) {
	current_node->callback_onMouseMove = cb;
}

void bl::onKeyDown(KeyDownCallback cb) {
	current_node->callback_onKeyDown = cb;
	key_down_registry.push_back(current_node);
}

void bl::onKeyUp(KeyUpCallback cb) {
	current_node->callback_onKeyUp = cb;
	key_up_registry.push_back(current_node);
}

void bl::enable(int callbackFlag) {
	if (callbackFlag & BL_MOUSE_MOVE_BUBBLE) current_node->callback_onMouseMove_enabled_bubble = true;
	if (callbackFlag & BL_MOUSE_DOWN_BUBBLE) current_node->callback_onMouseDown_enabled_bubble = true;
	if (callbackFlag & BL_MOUSE_UP_BUBBLE) current_node->callback_onMouseUp_enabled_bubble = true;
	if (callbackFlag & BL_MOUSE_SCROLL_BUBBLE) current_node->callback_onMouseScroll_enabled_bubble = true;
	if (callbackFlag & BL_KEY_DOWN_BUBBLE) current_node->callback_onKeyDown_enabled_bubble = true;
	if (callbackFlag & BL_KEY_UP_BUBBLE) current_node->callback_onKeyUp_enabled_bubble = true;
}

void bl::disable(int callbackFlag) {
	if (callbackFlag & BL_MOUSE_MOVE_BUBBLE) current_node->callback_onMouseMove_enabled_bubble = false;
	if (callbackFlag & BL_MOUSE_DOWN_BUBBLE) current_node->callback_onMouseDown_enabled_bubble = false;
	if (callbackFlag & BL_MOUSE_UP_BUBBLE) current_node->callback_onMouseUp_enabled_bubble = false;
	if (callbackFlag & BL_MOUSE_SCROLL_BUBBLE) current_node->callback_onMouseScroll_enabled_bubble = false;
	if (callbackFlag & BL_KEY_DOWN_BUBBLE) current_node->callback_onKeyDown_enabled_bubble = false;
	if (callbackFlag & BL_KEY_UP_BUBBLE) current_node->callback_onKeyUp_enabled_bubble = false;
}
