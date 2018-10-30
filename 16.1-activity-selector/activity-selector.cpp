#include <iostream>
#include <vector>

using namespace std;

void recursiveActivitySelector(int s[], int f[], int k, int n, vector<int> &S) {
	int m = k+1;
	while (m <= n && s[m] < f[k]) {
		m++;
	}
	if (m <= n) {
		S.push_back(m);
		recursiveActivitySelector(s, f, m, n, S);
	}
}

void greedyActivitySelector(int s[], int f[], int n, vector<int> &S) {
	S.push_back(1); // add a1 to the set first
	int k = 1;
	for (int m=2; m <= 11; m++) {
		if (s[m] >= f[k]) {
			S.push_back(m);
			k = m;
		}
	}
}

void printVector(const vector<int> &v) {
	for (const int &a : v) {
		cout << "a" << a << " ";
	}
}

int main() {
	int s[] = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
	int f[] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};

	vector<int> maxSubset;
	recursiveActivitySelector(s, f, 0, 11, maxSubset);
	printVector(maxSubset);
	cout << endl;

	vector<int> maxSubset2;
	greedyActivitySelector(s, f, 11, maxSubset2);
	printVector(maxSubset2);
	cout << endl;

	return 0;
}
