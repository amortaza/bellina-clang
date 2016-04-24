#include "stdafx.h"

#include "bellina/bellina.h"

#include "z-index.h"

using namespace std;
using namespace bl;
using namespace bl::listener;

using namespace z_index;

namespace z_index {
	char* plugin_name = "z-index";
	
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

	map<string, OrderInfo*> orderInfoByParent;

	void init() {}
	void onNode();

	void uninit();

	OrderInfo* getKidsOrderInfo(Node* parent) {
		string parentKey(parent->nid);

		auto e2 = orderInfoByParent.find(parentKey);
		if (e2 == orderInfoByParent.end()) {

			OrderInfo* info = new OrderInfo(parent);
			orderInfoByParent[parentKey] = info;

			return info;
		}
		else {
			return e2->second;
		}
	}

	void reorderDom(	Node* p, 
						map<string, Node*>* nodeById) {
		
		OrderInfo* info = getKidsOrderInfo(p);

		p->kids.clear(); // only do this AFTER getKidsOrderInfo		

		int index = 1;
		
		Orders::const_iterator i2;
		for (i2 = info->orders->begin(); i2 != info->orders->end(); ++i2) {
			Order* order = *i2;
			
			order->order = index;
			++index;

			Node* kid = (*nodeById)[order->nodeId];

			//rintf(">>>>>>>>>> kid stack %s\n", kid->nid );
			p->kids.push_back(kid);
		}
		
		info->maxOrder = index;
	}

	bool haha(Order* a, Order* b) {
		return a->order < b->order;
	}

	void bringToTop(Node* parent, char* childId) {
		OrderInfo* info = getKidsOrderInfo(parent);
		
		Order* order = info->getOrderById(childId);
		order->order = info->maxOrder;

		info->orders->sort(haha);		
	}
}

void z_index::uninit() {
	typedef map<string, OrderInfo*>::iterator it1;
	for (it1 it = orderInfoByParent.begin(); it != orderInfoByParent.end(); it++) {
		OrderInfo* info = it->second;

		delete info;
	}
}

void z_index::onNode() {

	Node* c = _::current_node;

	map<string, Node*>* nodeById;
	nodeById = bl::util::buildNodeLookup(&c->kids);

	reorderDom(c, nodeById);

	nodeById->clear();
	delete nodeById;

	list<Node*>::const_iterator it;
	for (it = c->kids.begin(); it != c->kids.end(); ++it) {
		Node *node = *it;

		_::current_node = node;

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (button == Xel::Mouse::Button::Left) {
				Node* parent = bl::node->parent;

				bringToTop(parent, bl::node->nid);
			}

			return true;
		});
	}

	_::current_node = c;
}

void z_index::load() {
	bl::pluginRegister(	z_index::plugin_name, 
						z_index::init, 
						z_index::onNode, 
						nullptr, 
						z_index::uninit);
}