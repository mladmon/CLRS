#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define SIZE 8

void insertionSort(int []);

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

	insertionSort(a);

	cout << "a[0.." << SIZE-1 << "]: ";
	for (int i=0; i < SIZE; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	return 0;
}

void insertionSort(int a[]) {
	int key;
	for (int i=1; i < SIZE; i++) {
		// insert a[i] into the sorted sequence a[1..i-1]
		key = a[i];
		int j = i-1;
		while (j >= 0 && a[j] > key) {
			a[j+1] = a[j];
			j--;
		}

		a[j+1] = key;
	}
}
