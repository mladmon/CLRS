#include <iostream>
#include <string>
#include <sstream>
#include <limits>

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

	mergeSort(a, 0, SIZE-1);

	cout << "a[0.." << SIZE-1 << "]: ";
	for (int i=0; i < SIZE; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	return 0;
}

void merge(int a[], int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	int left[n1+1], right[n2+1];

	for (int i=0; i < n1; i++) {
		left[i] = a[p+i];
	}

	for (int i=0; i < n2; i++) {
		right[i] = a[q+1+i];
	}

	left[n1]  = numeric_limits<int>::max();
	right[n2] = numeric_limits<int>::max();

	int i = 0, j = 0;
	for (int k=p; k <= r; k++) {
		if (left[i] <= right[j])
			a[k] = left[i++];
		else
			a[k] = right[j++];
	}
}

void mergeSort(int a[], int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		mergeSort(a, p, q);
		mergeSort(a, q+1, r);
		merge(a, p, q, r);
	}
}
