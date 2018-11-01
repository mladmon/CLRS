#include <iostream>
#include <functional>		// std::hash
#include <unordered_set>	// std::unordered_set
#include <queue>				// std::priority_queue

using namespace std;

class Node {
		char c;
		int freq;
	public:
		const Node *left, *right;
		Node(int freq) : c('\0'), freq(freq) {}
		Node(char c, int freq) : c(c), freq(freq) {}
		// needed for Node's use in unordered_set container
		// note: added comparison between frequencies as well to make this implementation of Huffman() work... will fix
		bool operator==(const Node &other) const { return (c == other.c) && freq == other.freq; }
		// needed for Node's use in priority_queue container
		// note: implemented as freq > other.freq to implement min priority_queue!
		bool operator<(const Node &other) const { return freq > other.freq; }
		char getChar() const { return c; }
		int getFreq() const { return freq; }
};

// needed for Node's use in unordered_set container
template <> struct std::hash<Node> {
	size_t operator()(const Node &n) const {
		return hash<char>()(n.getChar());
	}
};

/* This bad implementatin of huffman() uses memory on the stack instead of
   dynamically allocated memory, so we need to be careful when assigning z.left
   and z.right. They need to point to the addresses of corresponding nodes in
   C, not Q since we're copying and destroying Nodes quite often. this
   implementation adds newly created z nodes to C as well, so their addresses
   are used to assign subsequent z.left and z.right... this is bad I know. I
   also had to modify the operator== to include checking frequencies because
   I'm now inserting multiple characters into C with c set to '\0'! Next version
   will use pointers and pass the function a min priority_queue from main().
   This was a good learning experience for how memory works and which addresses
   to use... you really have to understand what's going on to make this bad
   version work.
*/
Node huffman(unordered_set<Node> &C) {
	int n = C.size();

	priority_queue<Node> Q;
	for (const Node &c : C) {
		Q.push(c);
	}

	for (int i=1; i <= n-1; i++) {
		Node x = Q.top();
		Q.pop();
		Node y = Q.top();
		Q.pop();

		Node z(x.getFreq() + y.getFreq());
		z.left = &(*(C.find(x)));
		z.right = &(*(C.find(y)));
		C.insert(z);
		Q.push(z);
	}

	cout << "Q.size(): " << Q.size() << endl;
	return Q.top();
}

int main() {
	unordered_set<Node> C({
		Node('a', 45),
		Node('b', 13),
		Node('c', 12),
		Node('d', 16),
		Node('e', 9),
		Node('f', 5)
	});

/*	unordered_set<Node>::const_iterator it = C.find(Node('b', 13));
	if (it == C.end()) {
		cout << "Character not found!" << endl;
	} else {
		cout << "Character is in the set!" << endl;
		cout << "c: " << it->getChar() << endl;
		cout << "address: " << &(*it) << endl;
	}*/

	cout << "C.size(): " << C.size() << endl;
	Node root = huffman(C);
	cout << "C.size(): " << C.size() << endl;

	// depth 0
	cout << "root.getFreq(): " << root.getFreq() << endl;

	// depth 1
	cout << "root.left->getChar(): " << root.left->getChar() << endl;
	cout << "root.left->getFreq(): " << root.left->getFreq() << endl;
	cout << "root.right->getFreq(): " << root.right->getFreq() << endl;

	// depth 2
	cout << "root.right->left->getFreq(): " << root.right->left->getFreq() << endl;
	cout << "root.right->right->getFreq(): " << root.right->right->getFreq() << endl;


	// depth 3
	cout << "root.right->left->left->getchar(): " << root.right->left->left->getChar() << endl;
	cout << "root.right->left->left->getFreq(): " << root.right->left->left->getFreq() << endl;
	cout << "root.right->left->right->getchar(): " << root.right->left->right->getChar() << endl;
	cout << "root.right->left->right->getFreq(): " << root.right->left->right->getFreq() << endl;

	cout << "root.right->right->left->getFreq(): " << root.right->right->left->getFreq() << endl;
	cout << "root.right->right->right->getchar(): " << root.right->right->right->getChar() << endl;
	cout << "root.right->right->right->getFreq(): " << root.right->right->right->getFreq() << endl;

	// depth 4
	cout << "root.right->right->left->left->getChar(): " << root.right->right->left->left->getChar() << endl;
	cout << "root.right->right->left->left->getFreq(): " << root.right->right->left->left->getFreq() << endl;

	cout << "root.right->right->left->right->getChar(): " << root.right->right->left->right->getChar() << endl;
	cout << "root.right->right->left->right->getFreq(): " << root.right->right->left->right->getFreq() << endl;

	return 0;
}
