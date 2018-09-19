#include <iostream>
#include <string>
#include <new>

using namespace std;

class List;

class Node {
	friend class List;
	private:
		int key;
		Node *prev, *next;
	public:
		Node(int k) : key(k), prev(NULL), next(NULL) {}
};

class List {
	private:
		Node *head;
		//vector<Node *> list;
	public:
		List() : head(NULL) {}
		~List();
		Node * listSearch(int);
		void listInsert(Node *);
		void listDelete(Node *);
		void listDelete(int k);
		void print(string);
};

List::~List() {
	/*for (Node *n : list) {
		delete n;
	}*/
	Node *n = head;
	while (n != NULL) {
		Node *temp = n->next;
		cout << "Deleting node: " << n << endl;
		delete n;
		n = temp;
	}
}

Node * List::listSearch(int k) {
	/*for (const Node *n : list) {
		if (k == n->key) {
			return n;
		}
	}
	return NULL;*/
	Node *n = head;
	while (n != NULL && n->key != k) {
		n = n->next;
	}
	return n;
}

void List::listInsert(Node *x) {
	x->next = head;
	if (head != NULL) {
		head->prev = x;
	}
	x->prev = NULL;
	head = x;
}

void List::listDelete(Node *x) {
	if (x->next != NULL) {
		x->next->prev = x->prev;
	}
	if (x->prev != NULL) {
		x->prev->next = x->next;
	} else {
		head = x->next;
	}
	cout << "Deleting node: " << x << endl;
	delete x;
}

void List::listDelete(int k) {
	Node *n = listSearch(k);
	if (n != NULL) {
		listDelete(n);
	} else {
		cout << "Node not in list!" << endl;
	}
}

void List::print(string name) {
	cout << name << ".head --> ";
	Node *n = head;
	if (n != NULL) {
		while (n->next != NULL) {
			cout << "[" << n->key << "] <--> ";
			n = n->next;
		}
		cout << "[" << n->key << "] --> NULL";
	}
	cout << endl;
}

int main() {
	List foo;

	Node *n1 = new Node(5);
	foo.listInsert(n1);

	for (int i=3; i < 8; i++) {
		foo.listInsert(new Node(i));
	}

	foo.print("foo");

	foo.listDelete(4);
	foo.listDelete(4);
	foo.listDelete(7);
	foo.listDelete(n1);

	foo.print("foo");

	return 0;
}
