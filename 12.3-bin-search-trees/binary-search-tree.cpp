#include <iostream>
#include <string>
#include <exception>
#include <chrono>
#include <random>
#include <unordered_set>
#include <new>

using namespace std;

class Tree;

class Node {
	friend class Tree;
	private:
		Node *p, *left, *right;
	public:
		int key;
		Node(int k) : p(NULL), left(NULL), right(NULL), key(k) {}
};

class Tree {
	private:
		void transplant(Node *, Node *);
	public:
		Node *root;
		Tree() : root(NULL) {}
		~Tree();
		void inorderTreeWalk(Node *);
		Node *treeSearch(Node *, int);
		Node *iterativeTreeSearch(Node *, int);
		Node *treeMinimum(Node *);
		Node *treeMaximum(Node *);
		Node *treeSuccessor(Node *);
		Node *treePredecessor(Node *);
		void treeInsert(Node *);
		void treeDelete(Node *);
};

Tree::~Tree() {
	Node *n = treeMinimum(root);
	while (n != NULL) {
		Node *next = treeSuccessor(n);
		//delete n;
		treeDelete(n);
		n = next;
	}
}

void Tree::inorderTreeWalk(Node *x) {
	if (x != NULL) {
		inorderTreeWalk(x->left);
		cout << x->key << " ";
		inorderTreeWalk(x->right);
	}
}

Node *Tree::treeSearch(Node *x, int k) {
	if (x == NULL || k == x->key) {
		return x;
	} else if (k < x->key) {
		return treeSearch(x->left, k);
	} else {
		return treeSearch(x->right, k);
	}
}

Node *Tree::iterativeTreeSearch(Node *x, int k) {
	while (x != NULL && k != x->key) {
		if (k < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	return x;
}

Node *Tree::treeMinimum(Node *x) {
	while (x->left != NULL) {
		x = x->left;
	}
	return x;
}

Node *Tree::treeMaximum(Node *x) {
	while (x->right != NULL) {
		x = x->right;
	}
	return x;
}

Node *Tree::treeSuccessor(Node *x) {
	if (x->right != NULL) {
		return treeMinimum(x->right);
	}
	Node *y = x->p;
	while (y != NULL && x == y->right) {
		x = y;
		y = y->p;
	}
	return y;
}

Node *Tree::treePredecessor(Node *x) {
	if (x->left != NULL) {
		return treeMaximum(x->left);
	}
	Node *y = x->p;
	while (y != NULL && x == y->left) {
		x = y;
		y = y->p;
	}
	return y;
}

void Tree::treeInsert(Node *n) {
	Node *x = root;
	Node *y = NULL;
	while (x != NULL) {
		y = x;
		if (n->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	n->p = y;
	if (y == NULL) {
		root = n;
	} else if (n->key < y->key) {
		y->left = n;
	} else {
		y->right = n;
	}
}

void Tree::transplant(Node *u, Node *v) {
	if (u->p == NULL) {
		root = v;
	} else if (u->p->left == u) {
		u->p->left = v;
	} else {
		u->p->right = v;
	}
	if (v != NULL) {
		v->p = u->p;
	}
}

void Tree::treeDelete(Node *n) {
	if (n->left == NULL) {
		transplant(n, n->right);
	} else if (n->right == NULL) {
		transplant(n, n->left);
	} else {
		Node *y = treeMinimum(n->right);
		if (y->p != n) {
			transplant(y, y->right);
			y->right = n->right;
			y->right->p = y;
		}
		transplant(n, y);
		y->left = n->left;
		y->left->p = y;
	}
	delete n;
}

int main() {
	unsigned long n = 20;
	string str;
	cout << "Enter desired number of elements in the tree, n: ";
	getline (cin, str);
	try {
		n = stoul(str);
	} catch (exception &e) {
		cerr << "Error: " << e.what() << ": ";
		cerr << "Using default value n = " << n << endl;
	}

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	/* By choosing the universe of keys to be U = {1, 2, ..., 3n}, we prevent the
	   possibility of an infinite loop because n can no longer exceed |U|, the
	   size of the universe (i.e., we avoid the pigeonhole principle) */
	uniform_int_distribution<int> distribution(1, 3*n);

	unordered_set<int> keys;
	int count = 0;
	while (keys.size() < n) {
		keys.insert(distribution(generator));
		count++;
	}
	//cout << "keys.size(): " << keys.size() << endl;
	//cout << "count: " << count << endl;

	Tree t;
	for (const auto &key : keys) {
		t.treeInsert(new Node(key));
	}

	cout << "t.root->key: " << t.root->key << endl;
	t.inorderTreeWalk(t.root); cout << endl;
	cout << "Minimum: " << t.treeMinimum(t.root)->key << endl;
	cout << "Maximum: " << t.treeMaximum(t.root)->key << endl;

	int foo = distribution(generator);
	while (keys.insert(foo).second == false) {
		foo = distribution(generator);
	}
	Node *bar = new Node(foo);
	t.treeInsert(bar);
	cout << "Inserting foo: " << foo << endl;

	t.inorderTreeWalk(t.root); cout << endl;
	cout << "Minimum: " << t.treeMinimum(t.root)->key << endl;
	cout << "Maximum: " << t.treeMaximum(t.root)->key << endl;

	cout << "bar:\t\t\t" << bar << endl;
	cout << "Node with key " << foo << ":\t" << t.treeSearch(t.root, foo) << endl;
	cout << "Node with key " << foo << ":\t" << t.iterativeTreeSearch(t.root, foo) << endl;

	Node *baz = t.treeSuccessor(bar);
	if (baz != NULL) {
		cout << "successor of " << foo << " is: " << baz->key << endl;
	} else {
		cout << "successor of " << foo << " is: NULL" << endl;
	}

	baz = t.treePredecessor(bar);
	if (baz != NULL) {
		cout << "predecessor of " << foo << " is: " << baz->key << endl;
	} else {
		cout << "predecessor of " << foo << " is: NULL" << endl;
	}

	cout << "Deleting root " << t.root->key << endl;
	t.treeDelete(t.root);
	cout << "t.root->key: " << t.root->key << endl;

	t.inorderTreeWalk(t.root); cout << endl;
	cout << "Minimum: " << t.treeMinimum(t.root)->key << endl;
	cout << "Maximum: " << t.treeMaximum(t.root)->key << endl;

	return 0;
}
