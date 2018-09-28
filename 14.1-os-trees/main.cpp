#include <iostream>
#include <new>
#include <chrono>
#include <random>
#include <unordered_set>

#include "rb-tree.h"

using namespace std;

int main(int argc, char *argv[]) {
	// size n of our red-black tree
	unsigned n = 10;

	// Generate a red-black tree of size n from a uniformly random set of keys
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(1, 3*n);

	unordered_set<int> keys;
	while (keys.size() < n) {
		keys.insert(distribution(generator));
	}

	RB_Tree t;
	for (const int &key : keys) {
		t.rbInsert(new Node(key));
	}

	// test red-black tree operations for correctness
	cout << "t.root->key: " << t.root->key << endl;
	t.inorderTreeWalk(t.root); cout << endl;

	return 0;
}
