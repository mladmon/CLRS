#include <iostream>
#include <string>
#include <exception>
#include <chrono>
#include <random>
#include <unordered_set>
#include <vector>

using namespace std;

template <class T>
void print(const vector<T> &v, const string &name) {
	cout << name << "[ ";
	for (const T &e : v) {
		cout << e << " ";
	}
	cout << "]" << endl;
}

int partition(vector<int> &v, int p, int r) {
	int pivot = v[r];
	int i = p-1;
	for (int j=p; j < r; j++) {
		if (v[j] <= pivot) {
			int swap = v[++i];
			v[i] = v[j];
			v[j] = swap;
		}
	}
	v[r] = v[++i];
	v[i] = pivot;

	return i;
}

int random(int p, int r) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(p, r);

	return distribution(generator);
}

int randomizedPartition(vector<int> &v, int p, int r) {
	int i = random(p, r);
	int swap = v[i];
	v[i] = v[r];
	v[r] = swap;

	return partition(v, p, r);
}

/* Return the ith order statistic from a set of n distinct numbers (i.e., the
   ith smallest number) */
int randomizedSelect(vector<int> &v, int p, int r, int i) {
	if (p == r) {
		return v[p];
	}

	int q = randomizedPartition(v, p, r);
	int k = q - p + 1;

	if (i == k) {
		return v[q];
	} else if (i < k) {
		return randomizedSelect(v, p, q-1, i);
	} else {
		return randomizedSelect(v, q+1, r, i-k);
	}
}

int main() {
	// Ask the user for set size, n, and integer, i, in the range [1-n]
	string str;
	int n = 10, i;
	cout << "Enter a desired set size, n: ";
	getline(cin, str);
	try {
		n = stoi(str);
	} catch (exception &e) {
		cerr << e.what() << ": you're an idiot. Using default value n = " << n << endl;
	}

	cout << "Enter an integer, i, in the range [1," << n << "]: ";
	getline(cin, str);
	try {
		i = stoi(str);
		if (i < 1 || i > n) { throw i; }
	} catch (exception &e) {
		cerr << e.what() << ": you're an even bigger idiot. Using default value i = "
			<< n/2 << endl;
		i = n/2;
	} catch (int num) {
		cerr << num << "... really? You're quite possibly the biggest idiot known"
			<< " to man. Using default value i = " << n/2 << endl;
		i = n/2;
	}

	// Generate a set S[0..n-1] of n distinct numbers
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(1, 100);

	unordered_set<int> S;
	int numInserts = 0;
	while (S.size() != (unsigned)n) {
		S.insert(distribution(generator));
		numInserts++;
	}
	cout << "numInserts: " << numInserts << endl;
	cout << "S.size(): " << S.size() << endl;

	// Copy elements of S into a vector V[0..n-1] whose elements we can index
	vector<int> V(S.size());
	int index = 0;
	for (const int &x : S) {
		V[index++] = x;
	}
	print(V, "V");

	// Call randomizedSelect() to find the ith smallest number in V[0..n-1]
	int ithSmallestNum = randomizedSelect(V, 0, V.size()-1, i);

	string suffix = "th";
	switch (i % 10) {
		case 1:
			if (i != 11) {
				suffix = "st";
			}
			break;
		case 2:
			if (i != 12) {
				suffix = "nd";
			}
			break;
		case 3:
			if (i != 13) {
				suffix = "rd";
			}
	}

	cout << "The " << i << suffix << " smallest number in the set is "
		<< ithSmallestNum << endl;

	return 0;
}
