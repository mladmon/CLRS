#ifndef RB_TREE_H
#define RB_TREE_H

#include <new>

enum color { RED, BLACK };

class Node {
	private:
		Node *left, *right, *p;
		int key;
		color c;
		int size; // only used by OS_Tree class
	public:
		Node(int k) : left(NULL), right(NULL), p(NULL), key(k), c(RED) {}
	friend class RB_Tree;
	friend class OS_Tree;
	friend int main(int, char **); // so we can print values for debugging
};

class RB_Tree {
	protected:
		Node *nil, *root;
		virtual void leftRotate(Node *);
		virtual void rightRotate(Node *);
		void rbInsertFixup(Node *);
		void rbTransplant(Node *, Node *);
		void rbDeleteFixup(Node *);
	public:
		RB_Tree() : nil(new Node(0)), root(nil) { nil->c = BLACK; }
		~RB_Tree();
		virtual void rbInsert(Node *);
		virtual void rbDelete(Node *);
		Node *rbTreeMinimum(Node *);
		Node *rbTreeSuccessor(Node *);
		void inorderTreeWalk(Node *);
	friend int main(int, char**); // so we can access root for debugging
};

#endif // RB_TREE_H
