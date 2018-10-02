#include <iostream>
#include <new>
#include <chrono>
#include <random>
#include <unordered_set>

#include "os-tree.h"

using namespace std;

int main(int argc, char *argv[]) {
	// size n of our order-statistic tree
	unsigned n = 10;

	/* Generate an order-statistic tree of size n from a uniformly random set of
	   keys */
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(1, 3*n);

	unordered_set<int> keys;
	while (keys.size() < n) {
		keys.insert(distribution(generator));
	}

	OS_Tree t;
	for (const int &key : keys) {
		t.rbInsert(new Node(key));
	}

	// test order-statistic tree operations for correctness
	cout << "t.root->key: " << t.root->key << endl;
	cout << "The root's rank is: " << t.osRank(t.root) << endl;
	t.inorderTreeWalk(t.root); cout << endl;

	Node *i = t.osSelect(t.root, 7);
	cout << "The 7th smallest element is: " << i->key << endl;
	cout << "The rank of its successor is "
		<< t.osRank(t.rbTreeSuccessor(i)) << endl;

	cout << "Deleting node of rank 5" << endl;
	t.rbDelete(t.osSelect(t.root, 5));

	cout << "t.root->key: " << t.root->key << endl;
	cout << "The root's rank is: " << t.osRank(t.root) << endl;
	t.inorderTreeWalk(t.root); cout << endl;
	cout << "Node " << i->key << "'s new rank is: " << t.osRank(i) << endl;
	cout << "The rank of its successor is "
		<< t.osRank(t.rbTreeSuccessor(i)) << endl;

	return 0;
}
