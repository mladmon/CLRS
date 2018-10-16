#include <iostream>

using namespace std;

// Recursive top-down implementation: O(2^n)
int cutRod(int p[], int n) {
	// base case: a rod of length 0 inches generates $0 in revenue
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

// Dynamic programming: bottom-up
int bottomUpCutRod(int p[], int n) {
	// create an auxiliary array, r, to store revenues as they're computed
	int r[n+1];
	r[0] = 0; // a rod of length 0 inches generates $0 in revenue

	// calculate max revenue for rods of length i inches, in order, from 1..n
	for (int i=1; i <= n; i++) {
		int max_r = -1;
		for (int j=0; j < i; j++) {
			int r_j = p[j] + r[i-j-1];
			if (r_j > max_r) {
				max_r = r_j;
			}
		}
		r[i] = max_r;
	}

	return r[n];
}

int extendedBottomUpCutRod(int p[], int n, int s[]) {
	int r[n+1];
	r[0] = 0;

	for (int i=1; i <= n; i++) {
		int max_r = -1;
		for (int j=0; j < i; j++) {
			int r_j = p[j] + r[i-j-1];
			if (r_j > max_r) {
				max_r = r_j;
				s[i] = j+1;
			}
		}
		r[i] = max_r;
	}

	return r[n];
}

void printCutRodSolution(int p[], int n) {
	int s[n];
	int max_r = extendedBottomUpCutRod(p, n, s);
	cout << "extendedBottomUpCutRod(): $" << max_r << endl;

	// print the optimal decomoposition of a rod of length n inches
	cout << "printCutRodSolution(): " << n << " = ";
	while (n > 0) {
		cout << s[n] << " ";
		n -= s[n];
	}
	cout << endl;
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

	int r3 = bottomUpCutRod(p, n);
	cout << "bottomUpCutRod(): $" << r3 << endl;

	printCutRodSolution(p, n);

	return 0;
}
