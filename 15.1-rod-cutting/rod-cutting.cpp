#include <iostream>

int cutRod(int p[], int n) {
	// base case: rod of length 0 inches generates $0 in revenue
	if (n == 0) {
		return 0;
	}

	int max_r = -1; // initially set to -1 becauase can't have negative revenue
	for (int i=0; i < n; i++) {
		int r = p[i] + cutRod(p, n-i-1);
		if (r > max_r) {
			max_r = r;
		}
	}

	return max_r;
}

using namespace std;

int main() {
	// sample price table for rods of length i, in inches
	int p[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

	// Ask user for desired rod length, n, in inches
	int n;
	cout << "Enter desired rod length, n, in the range [1,10]: ";
	cin >> n;

	// Determine max revenue, r, for optimal decomposition of a rod of length n
	int r = cutRod(p, n);

	cout << "Maximum revenue obtained for cutting a rod of length " << n
		<< " is: $" << r << endl;

	return 0;
}
