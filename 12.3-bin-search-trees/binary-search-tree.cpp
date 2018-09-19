#include <iostream>
#include <vector>
#include <new>

using namespace std;

class Tree;

class Node {
	friend class Tree;
	private:
		int key;
		Node *p, *left, *right;
	public:
		Node(int k) : key(k), p(NULL), left(NULL), right(NULL) {}
};

class Tree {
	private:
		Node *root;
		vector<Node *> t;
		void transplant(Node *, Node *);
	public:
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
	for (Node *n: t) {
		delete n;
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
		treeSearch(x->left, k);
	} else {
		treeSearch(x->right, k);
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

	return 0;
}
