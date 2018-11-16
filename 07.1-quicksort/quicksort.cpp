#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int partition(int [], int, int);
void quicksort(int [], int, int);

int main() {
	string array;
	int a[8];

	cout << "Enter a sequence of 8 integers separated by spaces: " << endl;
	getline(cin, array);
	stringstream arrayStream (array);

	for (int i=0; i < 8; i++) {
		arrayStream >> a[i];
	}

	quicksort(a, 0, 7);

	cout << "a[0..7]: ";
	for (int i=0; i < 8; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	return 0;
}

int partition(int a[], int p, int r) {
	int x = a[r];
	int i = p - 1;

	int swap;
	for (int j=p; j < r; j++) {
		if (a[j] <= x) {
			swap = a[++i];
			a[i] = a[j];
			a[j] = swap;
		}
	}

	a[r] = a[++i];
	a[i] = x;

	return i;
}

void quicksort(int a[], int p, int r) {
	int q;
	if (p < r) {
		q = partition(a, p, r);
		quicksort(a, p, q-1);
		quicksort(a, q+1, r);
	}
}
