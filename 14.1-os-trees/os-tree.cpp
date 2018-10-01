#include "os-tree.h"

void OS_Tree::leftRotate(Node *x) {
	// To-Do: Implement this method
}

void OS_Tree::rightRotate(Node *y) {
	// To-Do: Implement this method
}

void OS_Tree::rbInsert(Node *z) {
	// To-Do: Implement this method
}

void OS_Tree::rbDelete(Node *z) {
	// To-Do: Implement this method
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
