#include <iostream>

#include "rb-tree.h"

RB_Tree::~RB_Tree() {
	Node *n = rbTreeMinimum(root);
	while (n != nil) {
		Node *next = rbTreeSuccessor(n);
		rbDelete(n);
		n = next;
	}
	delete nil;
}

void RB_Tree::leftRotate(Node *x) {
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

void RB_Tree::rightRotate(Node *y) {
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

void RB_Tree::rbInsertFixup(Node *z) {
	while (z->p->c == RED) {
		if (z->p == z->p->p->left) {
			Node *y = z->p->p->right;
			if (y->c == RED) {				// case 1
				z->p->c = BLACK;
				y->c = BLACK;
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
				z->p->c = BLACK;
				y->c = BLACK;
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

void RB_Tree::rbInsert(Node *z) {
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

void RB_Tree::rbTransplant(Node *u, Node *v) {
	if (u->p == nil) {
		root = v;
	} else if (u == u->p->left) {
		u->p->left = v;
	} else {
		u->p->right = v;
	}
	v->p = u->p;
}

void RB_Tree::rbDeleteFixup(Node *x) {
	while (x != root && x->c == BLACK) {
		if (x == x->p->left) {
			Node *w = x->p->right;
			if (w->c == RED) {
				w->c = BLACK;
				x->p->c = RED;
				leftRotate(x->p);
				w = x->p->right;
			}
			if (w->left->c == BLACK && w->right->c == BLACK) {
				w->c = RED;
				x = x->p;
			} else {
				if (w->right->c == BLACK) {
					w->left->c = BLACK;
					w->c = RED;
					rightRotate(w);
					w = x->p->right;
				}
				w->c = x->p->c;
				x->p->c = BLACK;
				w->right->c = BLACK;
				leftRotate(x->p);
				x = root;
			}
		} else {
			Node *w = x->p->left;
			if (w->c == RED) {
				w->c = BLACK;
				x->p->c = RED;
				rightRotate(x->p);
				w = x->p->left;
			}
			if (w->right->c == BLACK && w->left->c == BLACK) {
				w->c = RED;
				x = x->p;
			} else {
				if (w->left->c == BLACK) {
					w->right->c = BLACK;
					w->c = RED;
					leftRotate(w);
					w = x->p->left;
				}
				w->c = x->p->c;
				x->p->c = BLACK;
				w->left->c = BLACK;
				rightRotate(x->p);
				x = root;
			}
		}
	}
	x->c = BLACK;
}

void RB_Tree::rbDelete(Node *z) {
	Node *y = z, *x;
	color y_original = y->c;
	if (z->left == nil) {
		x = z->right;
		rbTransplant(z, z->right);
	} else if (z->right == nil) {
		x = z->left;
		rbTransplant(z, z->left);
	} else {
		y = rbTreeMinimum(z->right);
		y_original = y->c;
		x = y->right;
		if (y->p == z) {
			x->p = y;
		} else {
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		rbTransplant(z, y);
		y->left = z->left;
		y->left->p = y;
		y->c = z->c;
	}
	if (y_original == BLACK) {
		rbDeleteFixup(x);
	}
	delete z;
}

Node *RB_Tree::rbTreeMinimum(Node *x) {
	while (x->left != nil) {
		x = x->left;
	}
	return x;
}

Node *RB_Tree::rbTreeSuccessor(Node *x) {
	if (x->right != nil) {
		return rbTreeMinimum(x->right);
	}
	Node *y = x->p;
	while (y != nil && x == y->right) {
		x = y;
		y = y->p;
	}
	return y;
}

void RB_Tree::inorderTreeWalk(Node *x) {
	if (x != nil) {
		inorderTreeWalk(x->left);
		std::cout << x->key << "(" << x->c << ") ";
		inorderTreeWalk(x->right);
	}
}
