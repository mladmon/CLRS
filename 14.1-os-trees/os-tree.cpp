#include <iostream>

#include "os-tree.h"

void OS_Tree::leftRotate(Node *x) {
	RB_Tree::leftRotate(x);
	Node *y = x->p;
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}

void OS_Tree::rightRotate(Node *y) {
	RB_Tree::rightRotate(y);
	Node *x = y->p;
	x->size = y->size;
	y->size = y->left->size + y->right->size + 1;
}

void OS_Tree::rbInsert(Node *z) {
	Node *y = nil;
	Node *x = root;
	while (x != nil) {
		x->size++;
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
	z->size = 1;
	rbInsertFixup(z);
}

void OS_Tree::decrementSizesToRoot(Node *x) {
	while (x != nil) {
		x->size--;
		x = x->p;
	}
}

void OS_Tree::rbDelete(Node *z) {
	std::cout << "Executing OS_Tree::rbDelete()!" << std::endl << std::endl;
	Node *y = z, *x;
	color y_original = y->c;
	if (z->left == nil) {
		decrementSizesToRoot(z->p);
		x = z->right;
		rbTransplant(z, z->right);
	} else if (z->right == nil) {
		decrementSizesToRoot(z->p);
		x = z->left;
		rbTransplant(z, z->left);
	} else {
		y = rbTreeMinimum(z->right);
		y_original = y->c;
		x = y->right;
		if (y->p == z) {
			decrementSizesToRoot(z);
			x->p = y;
		} else {
			decrementSizesToRoot(y->p);
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		rbTransplant(z, y);
		y->left = z->left;
		y->left->p = y;
		y->c = z->c;
		y->size = z->size;
	}
	if (y_original == BLACK) {
		rbDeleteFixup(x);
	}
	delete z;
}

Node *OS_Tree::osSelect(Node *x, int i) {
	int rank = x->left->size + 1;
	if (i == rank) {
		return x;
	} else if (i < rank) {
		return osSelect(x->left, i);
	} else {
		return osSelect(x->right, i-rank);
	}
}

int OS_Tree::osRank(Node *x) {
	int rank = x->left->size + 1;
	Node *y = x->p;
	while (y != nil) {
		if (x == y->right) {
			rank += y->left->size + 1;
		}
		x = y;
		y = y->p;
	}

	return rank;
}
