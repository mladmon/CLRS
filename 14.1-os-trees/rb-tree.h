#ifndef RB_TREE_H
#define RB_TREE_H

#include <new>

enum color { RED, BLACK };

class Node {
	private:
		Node *left, *right, *p;
	public:
		int key;
		color c;
		int size; // only used by OS_Tree class
		Node(int k) : left(NULL), right(NULL), p(NULL), key(k), c(RED) {}
	friend class RB_Tree;
	friend class OS_Tree;
};

class RB_Tree {
	protected:
		virtual void leftRotate(Node *);
		virtual void rightRotate(Node *);
		void rbInsertFixup(Node *);
		void rbTransplant(Node *, Node *);
		void rbDeleteFixup(Node *);
	public:
		Node *nil, *root;
		RB_Tree() : nil(new Node(0)), root(nil) { nil->c = BLACK; }
		~RB_Tree();
		virtual void rbInsert(Node *);
		virtual void rbDelete(Node *);
		Node *rbTreeMinimum(Node *);
		Node *rbTreeSuccessor(Node *);
		void inorderTreeWalk(Node *);
};

#endif // RB_TREE_H
