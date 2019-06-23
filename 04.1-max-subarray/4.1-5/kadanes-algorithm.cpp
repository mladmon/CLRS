#include <iostream>

using namespace std;

class Subarray {
		int l, r;
		int val;
	public:
		Subarray(int l, int r, int val) : l(l), r(r), val(val) {}
		void setLeft(int left) {l = left;}
		int getLeft() {return l;}
		void setRight(int right) {r = right;}
		int getRight() {return r;}
		void setValue(int sum) {val = sum;}
		int getValue() {return val;}
};

/*	loop invariant:
	max contains the maximum nonempty, contiguous subarray of a[0..j-1],
	currentMax contains the maximum nonempty, contiguous subarray of
	a[i..j-1], and currentLeft contains the left index of currentMax, i.

	Initialization:
	Before the first iteration, j=1 and i=0, and max must contain the maximum
	subarray of a[0..1-1], or a[0]. The maximum nonempty, contiguous subarray
	of an array containing only one element is simply the array itself, and
	max correctly stores a[0] and indices (0,0). Similarly, currentMax is
	initialized to a[0], and currentLeft is initialized to 0.

	Maintenance:
	To see that each iteration maintains the loop invariant, note that knowing
	the maximum nonempty, contiguous subarray of a[i..j-1], currentMax, the
	maximum nonempty, contiguous subarray of a[i..j] is the maximum of
	a[i..j-1] + a[j] and a[j]. The first line calculates a[i..j-1] + a[j] and
	stores the value in a variable named sum. Suppose a[j] is the maximum of
	the two values. The loop executes the else statements and correctly
	updates currentMax and the left index, i, to a[j] and j, respectively.
	Otherwise, currentMax is set to sum and the left index, i, remains
	unchanged. currentMax now contains the maximum nonempty, contiguous
	subarray of a[i..j] and currentLeft contains its left index, i. Last, the
	loop checks if currentMax is larger than the value contained in max. If it
	is, max's value is updated to currentMax, its left index is set to
	currentLeft, and right index is set to j (the right-most element of
	a[i..j]). max now contains the maximum nonempty, contiguous subarray of
	a[0..j]. Incrementing j at the end of the for loop reestablishes the loop
	invariant for the next iteration.

	Termination:
	At termination, j = size, and by the loop invariant, max contains the
	maximum nonempty, contiguous subarray of a[0..size-1] which is the entire
	array. Hence, we have found the maximum subarray of a (value and indices).
*/

int main() {
	int size = 13;
	int a[size] = {1, 7, -13, -4, 2, 3, -4, 5, 3, -1, 2, -3, -5};

	Subarray max(0, 0, a[0]);	// maximum subarray of a[0..j-1]
	int currentMax = a[0];		// the running max subarray of a[i..j-1]
	int currentLeft = 0;			// left index, i, of the running max subarray

	int sum = 0;
	for (int j=1; j < size; j++) {
		sum = currentMax + a[j];
		if (sum > a[j]) {			// max subarray of a[i..j] is a[i..j-1] + a[j]
			currentMax = sum;
		} else {						// max subarray of a[i..j] is a[j]
			currentMax = a[j];
			currentLeft = j;
		}

		//cout << "sum: " << sum << endl;
		//cout << "currentMax: " << currentMax << endl;
		//cout << "currentLeft: " << currentLeft << endl;
		//cout << "j: " << j << endl << endl;

		// update max if a[i..j] is larger than a[0..j-1]
		if (currentMax > max.getValue()) {
			max.setValue(currentMax);
			max.setLeft(currentLeft);
			max.setRight(j);
		}
	}

	cout << "a [ ";
	for (int i=0; i < size; i++) {
		cout << a[i] << " ";
	}
	cout << "]" << endl;

	cout << "Maximum subarray is a[" << max.getLeft() << ".." << max.getRight()
			<< "]: " << max.getValue() << endl;

	return 0;
}
