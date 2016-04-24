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
							
		p->kids.clear();
		
		OrderInfo* info = getKidsOrderInfo(p);

		int index = 1;
		
		Orders::const_iterator i2;
		for (i2 = info->orders->begin(); i2 != info->orders->end(); ++i2) {
			Order* order = *i2;
			
			order->order = index;
			++index;

			Node* kid = (*nodeById)[order->nodeId];

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
	Node* parent = _::current_node;	

	map<string, Node*>* nodeById;
	nodeById = bl::util::buildNodeLookup(&parent->kids);

	//bringToTop(parent,"blue");
	bringToTop(parent, "green");
	//bringToTop(parent, "red");

	reorderDom(parent, nodeById);
	
	nodeById->clear();
	delete nodeById;
}
