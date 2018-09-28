#ifndef OS_TREE_H
#define OS_TREE_H

#include "rb-tree.h"

// change base class private members to protected so they're inherited
// change appropriate Tree methods to virtual
// decalre OS-Tree as a friend of Node as well since friendship isn't inherited
// or actually, make OS-Tree a friend of derived OS_Node :)
// call Node(int k); need to redefine OS_Tree() because default constructor
// creates a Node and we want nil to be an OS_Node! (and need to set its size)

/* turns out you can't create a derived Node, OS_Node, because OS_Tree inherits
   members of RB_Tree which work with Node *s, and Node *s do not know that the
   field 'size' exists, even if it's pointing to an OS_Node. OS_Node *s would
	know the field exists, but then you'd have to change all of OS_Tree's methods
	to work with OS_Node *s, not Node *s, and so you're not redefining virtual
	functions but rather creating new ones and hence inheriting from RB_Tree is
	useless, especially because the inherited functions also use Node *s :P

	Solution: add 'int size' field to Node, and simply accept that it's not used
	by RB_Trees at all, but will be used by OS_Trees... hence the inheritance here
	is not perfect (because you wouldn't implement RB_Trees w/ Nodes that have a
   useless 'int size' field... but the best we can do to inehrit a lot of stuff)
class OS_Node : public Node {
	private:
		int size;
	public:
		OS_Node(int k) : Node(k), size(1) {}
	friend class OS_Tree;
}; */

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
