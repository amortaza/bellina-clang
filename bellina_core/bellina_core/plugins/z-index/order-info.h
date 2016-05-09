#pragma once

namespace z_index {
	struct Order {
		string nodeId;
		int order;
	};

	typedef list<Order*> Orders;

	class OrderInfo {
	public:

		int maxOrder;

		Orders* orders = new Orders();
		map<string, Order*> orderByNode;

		~OrderInfo() {
			orderByNode.clear();

			Orders::const_iterator iterator;
			for (iterator = orders->begin(); iterator != orders->end(); ++iterator) {
				Order* order = *iterator;

				delete order;
				//test new Order();
			}

			orders->clear();

			delete orders;
		}

		OrderInfo(Node* parent) {
			orders->clear();

			int index = 1;
			int maxIndex = -1;

			list<Node*>::const_iterator i2;
			for (i2 = parent->kids.begin(); i2 != parent->kids.end(); ++i2) {
				Node* kid = *i2;
				string key(kid->nid);

				Order* order = new Order();
				order->nodeId = key;
				order->order = index;

				++index;

				orderByNode[key] = order;

				orders->push_back(order);
			}

			maxOrder = index;
		}

		Order* getOrderById(char* nid) {
			string key(nid);

			auto e2 = orderByNode.find(key);
			if (e2 == orderByNode.end()) throw "not possible";
			Order* order = e2->second;
			return order;
		}
	};
}