#ifndef OS_TREE_H
#define OS_TREE_H

#include "rb-tree.h"

class OS_Tree : public RB_Tree {
	private:
		void leftRotate(Node *);
		void rightRotate(Node *);
	public:
		OS_Tree() {	nil->size = 0; }
		void rbInsert(Node *);
		void rbDelete(Node *);
		Node *osSelect(Node *, int);
		int osRank(Node *);
};

#endif // OS_TREE_H
