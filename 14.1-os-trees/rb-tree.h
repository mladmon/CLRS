#ifndef RB_TREE_H
#define RB_TREE_H

#include <new>

enum color { RED, BLACK };

class Node {
	friend class RB_Tree;
	private:
		Node *left, *right, *p;
	public:
		int key;
		color c;
		Node(int k) : left(NULL), right(NULL), p(NULL), key(k), c(RED) {}
};

class RB_Tree {
	private:
		void leftRotate(Node *);
		void rightRotate(Node *);
		void rbInsertFixup(Node *);
		void rbTransplant(Node *, Node *);
		void rbDeleteFixup(Node *);
	public:
		Node *nil, *root;
		RB_Tree() : nil(new Node(0)), root(nil) { nil->c = BLACK; }
		~RB_Tree();
		void rbInsert(Node *);
		void rbDelete(Node *);
		Node *rbTreeMinimum(Node *);
		Node *rbTreeSuccessor(Node *);
		void inorderTreeWalk(Node *);
};

#endif // RB_TREE_H
