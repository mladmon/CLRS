#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
void print(const vector<T> &vec, const string &name) {
	cout << name << "[ ";
	for (auto const &e : vec) {
		cout << e << " ";
	}
	cout << "]" << endl;
}

void insertionSort(vector<float> &v) {
	float key;
	for (int i=1; i < v.size(); i++) {
		// insert vec[i] into the sorted sequence v[0..i-1]
		key = v[i];
		int j = i-1;
		while (j >= 0 && v[j] > key) {
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = key;
	}
}

void bucketSort(vector<float> &A) {
	vector< vector<float> > B(A.size());

	for (auto const &elem : A) {
		B[(int)floor(A.size()*elem)].push_back(elem);
	}

	for (auto &elem : B) {
		insertionSort(elem);
	}

	int k = 0;
	for (int i=0; i < B.size(); i++) {
		for (int j=0; j < B[i].size(); j++) {
			A[k++] = B[i][j];
		}
		print(B[i], "B"+to_string(i));
	}
}

int main() {
	// Ask user for an array length, n
	unsigned long n = 10;
	cout << "Enter a desired array length, n: ";
	string str;
	getline(cin, str);
	try {
		n = stoul(str);
	} catch (exception &e) {
		cerr << e.what() << ": Invalid input. Using default value n = " << n
			<< "." << endl;
	}
	cout << "n: " << n << endl;

	/* Generate an array A[0..n-1] of n real numbers that are uniformly and
	   independently distributed over the interval [0, 1) */
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<float> distribution(0.0, 1.0);

	vector<float> A(n);
	for (auto &elem: A) {
		elem = distribution(generator);
	}

	print(A, "A");
	bucketSort(A);
	print(A, "A");

	return 0;
}
