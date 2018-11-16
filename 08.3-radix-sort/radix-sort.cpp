#include <iostream>
#include <string>
#include <exception>
#include <chrono>
#include <random>
#include <climits>
#include <vector>
#include <cmath>

using namespace std;

void print(const vector<int> &vec, const string &name) {
	cout << name << "[ ";
	for (auto const &e : vec) {
		cout << e << " ";
	}
	cout << "]" << endl;
}

void countingSort(const vector<int> &A, vector<int> &B, int lsb, int msb) {
	cout << "lsb: " << lsb << endl;
	cout << "msb: " << msb << endl;

	// Each digit is a value in the range [0..k-1], where k = 2^(msb-lsb+1) = 2^r
	unsigned k = 0b1 << (msb-lsb + 1);
	cout << "countingSort::k = " << k << endl;

	/* Create an array, A_i[0..n-1], that contains the values of the "digit" i
	   of each element in A[0..n-1] for the current "digit" we're sorting on */
	vector<int> A_i(A.size());
	for (int j=0; j < A.size(); j++) {
		A_i[j] = (A[j] >> lsb) & (k-1);
	}
	print(A_i, "A_i");

	// Create an array, C[0..k-1], with each element initialized to 0
	vector<int> C(k, 0);

	for (int j=0; j < A_i.size(); j++) {
		C[A_i[j]]++;
	}

	for (int j=1; j < C.size(); j++) {
		C[j] += C[j-1];
	}

	for (int j=A_i.size()-1; j >= 0; j--) {
		B[C[A_i[j]]-1] = A[j];
		C[A_i[j]]--;
	}
}

void radixSort(vector<int> &A) {
	// b is the size of each array element, or key, in bits
	unsigned b = sizeof(int)*8;
	cout << "b: " << b << endl;

	/* r <= b is the size of each "digit" in bits, chosen to minimize the
	   expression O((b/r)(n+2^r)) */
	unsigned r = (unsigned) floor(log2(A.size()));
	if (b < r) {
		r = b;
	}
	cout << "r: " << r << endl;

	// d is the number of "digits" each element, or key, contains
	unsigned d = (unsigned) ceil((float)b/r);
	cout << "d: " << d << endl;

	/* Use a stable counting sort algorithm to sort A[0..n-1] incrementally on
	   each "digit" from right to left (i.e., "digit" 0 to d-1 where 0 is the
	   lowest-order "digit"). Let B[0..n-1] contain the partially-sorted array
	   after each iteration. After the last iteration, B contains A in sorted
	   order. */
	vector<int> B(A.size());
	unsigned lsb, msb;
	for (int i=0; i < d; i++) {
		// Calculate the lsb and msb of the current "digit", i, we're sorting on
		lsb = i*r;
		msb = lsb + (r-1);
		if (msb > (b-1)) {
			msb = b-1;
		}
		countingSort(A, B, lsb, msb);
		A = B;
	}
}

int main(int argc, char *argv[]) {
	string str;
	unsigned long n = 32;

	cout << "Enter a desired array length, n: ";
	getline (cin, str);
	try {
		n = stoul(str);
	} catch (exception &e) {
		cerr << e.what() <<  ": Invalid input. Using default n = " << n
			<< "." << endl;
	}

	/* Create an input array, A[0..n-1], of uniformly random values chosen from
	   the range [0..100] */
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0, 100);
	vector<int> A(n);
	for (auto &elem : A) {
		elem = distribution(generator);
	}
	print(A, "A");

	// Sort A[0..n-1] using the radix sort algorithm
	radixSort(A);
	print(A, "A");

	return 0;
}
