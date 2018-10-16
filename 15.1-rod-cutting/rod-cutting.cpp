#include <iostream>

using namespace std;

// Recursive top-down implementation: O(2^n)
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

// Dynamic programming: top-down with memoization
int memoizedCutRodAux(int p[], int n, int r[]) {
	if (n == 0 || (n > 0 && r[n] > 0)) { 	// we already know the value of r[n]
		// ... so do nothing
	} else {											// calculate r[n] for the first time,
		int max_r = -1;
		for (int i=0; i < n; i++) {
			int r_i = p[i] + memoizedCutRodAux(p, n-i-1, r);
			if (r_i > max_r) {
				max_r = r_i;
			}
		}
		r[n] = max_r;								// store it,
	}

	return r[n];									// and return it!
}

int memoizedCutRod(int p[], int n) {
	// create an auxiliary array, r, to store revenues as they're computed
	int r[n+1] = {}; // empty initializer sets all values to 0

	return memoizedCutRodAux(p, n, r);
}

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

	int r2 = memoizedCutRod(p, n);
	cout << "memoizedCutRod(): $" << r2 << endl;

	return 0;
}
