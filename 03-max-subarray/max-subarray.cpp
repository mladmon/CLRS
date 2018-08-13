#include <iostream>
#include <climits>

using namespace std;

class maxSubarray {
		int left, right;
		int value;
	public:
		maxSubarray(int l, int r, int val) : left(l), right(r), value(val) {}
		void setIndices(int l, int r) {left = l; right = r;}
		void setValue(int val) {value = val;}
		int getLeft() {return left;}
		int getRight() {return right;}
		int getValue() {return value;}
};

maxSubarray findMaxCrossingSubarray(int a[], int low, int mid, int high) {
	int leftSum = INT_MIN, rightSum = Int_MIN;
	int leftMax, rightMax;
	int sum = 0;

	// calculate the largest left subarray: a[i..mid]
	for (int i=mid; i >= low; i--) {
		sum+=a[i];
		if (sum > leftSum) {
			leftSum = sum;
			leftMax = i;
		}
	}


	maxSubarray max(0,0,0);
	return max;
}

int main() {
	int size = 16;
	int array[size] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};



	return 0;

}
