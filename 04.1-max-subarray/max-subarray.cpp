#include <iostream>
#include <climits>

using namespace std;

class Subarray {
		int left, right;
		int value;
	public:
		Subarray(int l, int r, int val) : left(l), right(r), value(val) {}
		int getLeft() {return left;}
		int getRight() {return right;}
		int getValue() {return value;}
};

Subarray findMaxCrossingSubarray(int a[], int low, int mid, int high) {
	int leftSum = INT_MIN, rightSum = INT_MIN;
	int leftMax, rightMax;

	// find the largest left subarray: a[i..mid]
	int sum = 0;
	for (int i=mid; i >= low; i--) {
		sum+=a[i];
		if (sum > leftSum) {
			leftSum = sum;
			leftMax = i;
		}
	}

	// find the largest right subarray: a[mid+1..i]
	sum = 0;
	for (int i=mid+1; i <= high; i++) {
		sum+=a[i];
		if (sum > rightSum) {
			rightSum = sum;
			rightMax = i;
		}
	}

	Subarray max(leftMax, rightMax, leftSum + rightSum);
	return max;
}

Subarray findMaxSubarray(int a[], int low, int high) {
	if (high == low) {
		return Subarray(low, high, a[low]);
	} else {
		int mid = (low + high) / 2;

		Subarray maxLeft = findMaxSubarray(a, low, mid);
		Subarray maxRight = findMaxSubarray(a, mid+1, high);
		Subarray maxCross = findMaxCrossingSubarray(a, low, mid, high);

		if (maxLeft.getValue() >= maxRight.getValue() &&
							maxLeft.getValue() >= maxCross.getValue())
			return maxLeft;
		else if (maxRight.getValue() >= maxLeft.getValue() &&
							maxRight.getValue() >= maxCross.getValue())
			return maxRight;
		else
			return maxCross;
	}
}

int main() {
	int size = 16;
	int array[size] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

	Subarray maxSubarray = findMaxSubarray(array, 0, size-1);

	cout << "Maximum subarray is a[" << maxSubarray.getLeft() << ".."
			<< maxSubarray.getRight() << "]: " << maxSubarray.getValue() << endl;

	return 0;

}
