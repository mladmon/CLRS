#ifndef OS_TREE_H
#define OS_TREE_H

#include "rb-tree.h"

// change base class private members to protected so they're inherited
// change appropriate Tree methods to virtual
// decalre OS-Tree as a friend of Node as well since friendship isn't inherited
// or actually, make OS-Tree a friend of derived OS_Node :)
// call Node(int k); need to redefine OS_Tree() because default constructor
// creates a Node and we want nil to be an OS_Node! (and need to set its size)

class OS_Node : public Node {
	private:
		int size;
	public:
		OS_Node(int k) : Node(k), size(1) {}
	friend class OS_Tree;
};

class OS_Tree : public RB_Tree {
	private:
		void leftRotate(Node *);
		void rightRotate(Node *);
	public:
		OS_Tree() : nil(new OS_Node(0)), root(nil) { nil->c = BLACK; size = 0; }
		void rbInsert(Node *);
		void rbDelete(Node *);
};

#endif // OS_TREE_H
