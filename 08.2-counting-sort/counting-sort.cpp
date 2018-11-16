#include <iostream>
#include <string>
#include <array>
#include <random>
#include <chrono>

using namespace std;

#define n 10
#define k 20

template<size_t N>
void print(const array<int,N> &arr) {
	for (int i=0; i < arr.size()-1; i++) {
		cout << arr[i] << " ";
	}
	cout << arr[arr.size()-1];
}

template<size_t N>
void countingSort(const array<int, N> &A, array<int, N> &B) {
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


	for (int i = A.size()-1; i >= 0; i--) {
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}
}

int main() {
	// Create an input array, A[0..n-1], with elements in the range 0-k
	array<int, n> A;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0,k);
	for (int &element : A) { // range-based for loop: each element is an int &
		element = distribution(generator);
	}
	cout << "A["; print(A); cout << "]" << endl;

	// Create an array, B[0..n-1] that contanis the elements of A in sorted order
	array<int, n> B;
	countingSort(A, B);
	cout << "B["; print(B); cout << "]" << endl;

	return 0;
}
