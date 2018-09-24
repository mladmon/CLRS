#include <iostream>
#include <new>

using namespace std;

enum color { RED, BLACK };

class Tree;

class Node {
	friend class Tree;
	private:
		color c;
		int key;
		Node *left, *right, *p;
	public:
		Node(int k) : c(RED), key(k), left(NULL), right(NULL), p(NULL) {}
};

class Tree {
	private:
		Node *nil, *root;
		void leftRotate(Node *);
		void rightRotate(Node *);
		void rbInsertFixup(Node *);
	public:
		Tree() : nil(new Node(0)), root(nil) { nil->c = BLACK; }
		~Tree();
		void rbInsert(Node *);
};

Tree::~Tree() {
	// To-Do: delete all nodes allocated with new
	delete nil;
}

void Tree::leftRotate(Node *x) {
	Node *y = x->right;				// set y
	x->right = y->left;				// turn y's left subtree into x's right subtree
	if (y->left != nil) {
		y->left->p = x;
	}
	y->p = x->p;						// link x's parent to y
	if (x->p == nil) {
		root = y;
	} else if (x == x->p->left) {
		x->p->left = y;
	} else {
		x->p->right = y;
	}
	y->left = x;						// put x on y's left
	x->p = y;
}

void Tree::rightRotate(Node *y) {
	Node *x = y->left;				// set x
	y->left = x->right;				// turn x's right subtree into y's left subtree
	if (x->right != nil) {
		x->right->p = y;
	}
	x->p = y->p;						// link y's parent to x
	if (y->p == nil) {
		root = x;
	} else if (y == y->p->left) {
		y->p->left = x;
	} else {
		y->p->right = x;
	}
	x->right = y;						// put y on x's right
	y->p = x;
}

void Tree::rbInsertFixup(Node *z) {
	while (z->p->c == RED) {
		if (z->p == z->p->p->left) {
			Node *y = z->p->p->right;
			if (y->c == RED) {				// case 1
				y->c = BLACK;
				z->p->c = BLACK;
				z->p->p->c = RED;
				z = z->p->p;
			} else {
				if (z == z->p->right) {		// case 2
					z = z->p;
					leftRotate(z);
				}
				z->p->c = BLACK;				// case 3
				z->p->p->c = RED;
				rightRotate(z->p->p);
			}
		} else {
			Node *y = z->p->p->left;
			if (y->c == RED) {				// case 1
				y->c = BLACK;
				z->p->c = BLACK;
				z->p->p->c = RED;
				z = z->p->p;
			} else {
				if (z == z->p->left) {		// case 2
					z = z->p;
					rightRotate(z);
				}
				z->p->c = BLACK;				// case 3
				z->p->p->c = RED;
				leftRotate(z->p->p);
			}
		}
	}
	root->c = BLACK;
}

void Tree::rbInsert(Node *z) {
	Node *y = nil;
	Node *x = root;
	while (x != nil) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	z->p = y;
	if (y == nil) {
		root = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
	z->left = nil;
	z->right = nil;
	z->c = RED;
	rbInsertFixup(z);
}

int main(int argc, char *argv[]) {

	return 0;
}