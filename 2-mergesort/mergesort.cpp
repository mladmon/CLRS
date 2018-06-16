#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define SIZE 8

void merge(int [], int, int, int);
void mergeSort(int [], int, int);

int main() {
	string array;
	int a[SIZE];

	cout << "Enter a sequence of " << SIZE
				<< " integers separated by spaces: " << endl;
	getline(cin, array);
	stringstream arrayStream (array);

	for (int i=0; i < SIZE; i++) {
		arrayStream >> a[i];
	}

	mergeSort(a);

	cout << "a[0.." << SIZE-1 << "]: ";
	for (int i=0; i < SIZE; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	return 0;
}

void merge(int a[], int p, int q, int r) {
	// insert code here
}

void mergeSort(int a[], int p, int r) {
	// insert code here
}
