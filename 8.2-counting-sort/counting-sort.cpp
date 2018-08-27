#include <iostream>
#include <string>
#include <array>
#include <random>
#include <chrono>

using namespace std;

#define n 10
#define k 20

template<size_t SIZE>
void print(const array<int,SIZE> &arr) {
	for (int i=0; i < arr.size()-1; i++) {
		cout << arr[i] << " ";
	}
	cout << arr[arr.size()-1];
}

int main() {
/*	string str;
	int n = 20, k = 10;

	cout << "Enter an array length, n: ";
	getline(cin, str);
	try {
		n = stoi(str);
	} catch (exception e) {
		cout << "Entered invalid argument. Using default n = 20." << endl;
	}

	cout << "Enter an integer, k, such that k = O(n): ";
	getline(cin, str);
	try {
		k = stoi(str);
	} catch (exception e) {
		cout << "Entered invalid argument. Using default k = 10." << endl;
	} */

	// Create an input array, A[0..n-1], with elements in the range 0-k
	array<int, n> A;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0,k);
	for (int &element : A) {
		element = distribution(generator);
	}

	cout << "A["; print(A); cout << "]" << endl;

	// Create an array, C[0..k], with all elements initialized to 0
	array<int, k+1> C = {};

	// Let C[i] contain the number of elements in A equal to i
	for (int i=0; i < A.size(); i++) {
		C[A[i]]++;
	}

	cout << "C["; print(C); cout << "]" << endl;

	// Let C[i] contain the number of elements less than or equal to i
	for (int i=1; i < C.size(); i++) {
		C[i]+=C[i-1];
	}

	cout << "C["; print(C); cout << "]" << endl;

	// Create an array, B[0..n-1] that contanis the elements of A in sorted order
	array<int, n> B;
	for (int i = A.size()-1; i >= 0; i--) {
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}

	cout << "B["; print(B); cout << "]" << endl;

	return 0;
}
