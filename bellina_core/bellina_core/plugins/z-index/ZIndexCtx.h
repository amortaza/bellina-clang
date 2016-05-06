#pragma once

namespace z_index {

	bool haha(Order* a, Order* b) {
		return a->order < b->order;
	}

	class ZIndexCtx : public BasePluginCtx {

	public:
		OrderInfo* orderInfo = 0;

		ZIndexCtx() : BasePluginCtx("default") {
		}

		~ZIndexCtx() {
			if (orderInfo) delete orderInfo;
		}

		// does not need signature or factory cause "this" already exits...
		void pluginOnNode() {

			Node* c = bl::current();

			ShadowNode* shadow = bl::get_shadow();
			
			ZIndexCtx* ctx = (ZIndexCtx*)shadow->getPluginCtx(z_index::plugin_name, "default", nullptr);

			if (!ctx->orderInfo)
				ctx->orderInfo = new OrderInfo(c);

			map<string, Node*>* nodeById;
			nodeById = bl::util::buildNodeLookup(&c->kids);

			reorderDom(c, ctx->orderInfo, nodeById);

			nodeById->clear();
			delete nodeById;
			
			char* signature = _signature;
			
			list<Node*>::const_iterator it;
			for (it = c->kids.begin(); it != c->kids.end(); ++it) {
				Node *kid = *it;

				bl::onMouseDownOnNode(kid, [signature] (Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
					if (button == Xel::Mouse::Button::Left) {
						Node* parent = bl::node->parent;

						ZIndexCtx* This = (ZIndexCtx*) parent->getPluginCtxFromShadow(z_index::plugin_name, signature, nullptr);

						This->bringToTop(This->orderInfo, bl::node->nid);

						ZIndexEvent event;
						event.topNode = bl::node;

						bl::pluginCall(plugin_name, signature, "default", bl::node->parent, &event);
						bl::fire(plugin_name, &event);
					}

					return true;
				});
			}
		}

	private:
		void reorderDom(Node* p, OrderInfo* parentOrderInfo, map<string, Node*>* nodeById) {
			

			p->kids.clear(); // only do this AFTER getKidsOrderInfo		

			int index = 1;

			Orders::const_iterator i2;
			for (i2 = parentOrderInfo->orders->begin(); i2 != parentOrderInfo->orders->end(); ++i2) {
				Order* order = *i2;

				order->order = index;
				++index;

				Node* kid = (*nodeById)[order->nodeId];

				//rintf(">>>>>>>>>> kid stack %s\n", kid->nid );
				p->kids.push_back(kid);
			}

			parentOrderInfo->maxOrder = index;
		}

		void bringToTop(OrderInfo* parentOrderInfo, char* childId) {			

			Order* order = parentOrderInfo->getOrderById(childId);
			order->order = parentOrderInfo->maxOrder;

			parentOrderInfo->orders->sort(haha);
		}
	};
}