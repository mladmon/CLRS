#include <iostream>
#include <vector>
#include <unordered_set>	// std::unordered_set
#include <queue>				// std::priority_queue

using namespace std;

class Node {
		char c;
		int freq;
	public:
		Node *left, *right;
		Node(int freq) : c('_'), freq(freq) {}
		Node(char c, int freq) : c(c), freq(freq), left(NULL), right(NULL) {}
		char getChar() const { return c; }
		int getFreq() const { return freq; }
};

// needed for priority_queue<Node *> container Compare template parameter
// note the use of '>' in order to implement a min priority_queue
struct CompareNodePtr {
	bool operator()(const Node *pt1, const Node *pt2) const {
		return pt1->getFreq() > pt2->getFreq();
	}
};

Node * huffman(const unordered_set<Node *> &C) {
	priority_queue<Node *, vector<Node *>, CompareNodePtr> Q;
	for (Node *c : C) {
		Q.push(c);
	}

	for (unsigned i=0; i < C.size()-1; i++) {
		Node *x = Q.top();
		Q.pop();
		Node *y = Q.top();
		Q.pop();

		Node *z = new Node(x->getFreq() + y->getFreq());
		z->left = x;
		z->right = y;
		Q.push(z);
	}

	return Q.top();
}

void printNodes(Node *np) {
	if (np != NULL) {
		cout << np->getChar() << ":" << np->getFreq() << endl;
		printNodes(np->left);
		printNodes(np->right);
	}
}

void deleteNodes(Node *np) {
	if (np != NULL) {
		deleteNodes(np->left);
		deleteNodes(np->right);
		cout << "Deleting " << np->getChar() << ":" << np->getFreq() << endl;
		delete np;
	}
}

int main() {
	unordered_set<Node *> C({
		new Node('a', 45),
		new Node('b', 13),
		new Node('c', 12),
		new Node('d', 16),
		new Node('e', 9),
		new Node('f', 5)
	});

	Node *root = huffman(C);
	printNodes(root);
	deleteNodes(root);

	return 0;
}
