#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int recursiveMatrixChain(int p[], int i, int j, vector<vector<int> > &m) {
	if (i == j) {
		m[i][i] = 0;
		return 0;
	} else {
		for (int k=i; k < j; k++) {
			int numMults = recursiveMatrixChain(p, i, k, m) +
								recursiveMatrixChain(p, k+1, j, m) + p[i-1]*p[k]*p[j];
			if (numMults < m[i][j]) {
				m[i][j] = numMults;
			}
		}
		return m[i][j];
	}
}

void lookupChain(int p[], int i, int j, vector<vector<int> > &m) {

}

void memoizedMatrixChain(int p[], vector<vector<int> > &m) {

}


/* Let us assume that to optimally parenthesize the matrix chain Ai..j, or
	Ai*Ai+1*...*Aj, we split between Ak and Ak+1, where i <= k < j. The cost
	of multiplying subproducts Ai..k and Ak+1..j is p[i-1]*p[k]*p[j] scalar
	multiplications. */
void matrixChainOrder(int p[], int n, vector<vector<int> > &m,
															vector<vector<int> > &s) {
	/* all matrix chains of length one contribute 0 scalar multiplications to
	   compute their product (i.e., all m[i,i] for i = 1..n */
	for (int i=1; i <= n; i++) {
		m[i][i] = 0;
	}

	/* solve for optimal parenthesizations of larger subproblems in order of
	   increasing matrix chain length for i = 2..n */
	for (int i=2; i <= n; i++) { // solve for matrix chains of length i = 2..n
		for (int j=1; j <= n-i+1; j++) { // solve for all matrix chains of length i
			for (int k=j; k < j+i-1; k++) { // check all possible values of k
				int numMults = m[j][k] + m[k+1][j+i-1] + p[j-1]*p[k]*p[j+i-1];
				if (numMults < m[j][j+i-1]) {
					m[j][j+i-1] = numMults;
					s[j][j+i-1] = k;
				}
			}
		}
	}
}

void printOptimalParens(vector<vector<int> > &s, int i, int j) {
	if (i == j) {
		cout << "A" << i;
	} else {
		cout << "(";
		printOptimalParens(s, i, s[i][j]);
		printOptimalParens(s, s[i][j]+1, j);
		cout << ")";
	}
}

void printTable(vector<vector<int> > &t, int n) {
	for (int i=1; i <= n; i++) {
		for (int j=i; j <= n; j++) {
			cout << "(" << i << "," << j << "):" << t[i][j] << "  ";
		}
		cout << endl;
	}
}

int main() {
	int n = 6; // number of matrices

	// matrix dimensions of A1..A6, where Ai's dimensions are p[i-1] x p[i]
	int p[] = {30, 35, 15, 5, 10, 20, 25};

	/* let m[i,j] contain the minimum number of scalar multiplications needed to
	   compute the matrix chain Ai*Ai+1*...*Aj for all 1 <= i <= j <= n */
	vector<vector<int> > m(n+1, vector<int>(n+1, INT_MAX));

	/* let s[i,j] contain a value of k at which we split the product Ai*Ai+1...*Aj
	   in an optimal parenthesization */
	vector<vector<int> > s(n+1, vector<int>(n+1, 0));

	matrixChainOrder(p, n, m, s);
	printTable(m, n); cout << endl;
	printTable(s, n); cout << endl;

	printOptimalParens(s, 1, n);
	cout << endl << endl;

	vector<vector<int> > m1(n+1, vector<int>(n+1, INT_MAX));
	recursiveMatrixChain(p, 1, n, m1);
	printTable(m1, n); cout << endl;

	return 0;
}
