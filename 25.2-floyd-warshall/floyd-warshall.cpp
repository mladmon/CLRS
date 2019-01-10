#include <iostream>
#include <limits>
#include <vector>

using namespace std;

typedef vector<vector<int> > matrix;

void print(const matrix &g) {
	for (unsigned i=0; i < g.size(); ++i) {
		for (unsigned j=0; j < g[i].size(); ++j) {
			cout << g[i][j] << " ";
		}
		cout << endl;
	}
}

matrix transitiveClosure(const matrix &G) {
	int n = G.size();
	matrix T(n, vector<int>(n, 0));
	for (int i=0; i < n; ++i) {
		for (int j=0; j < n; ++j) {
			if (i == j || G[i][j] != numeric_limits<int>::max()) {
				T[i][j] = 1;
			}
		}
	}
	cout << "T0" << endl; print(T);

	for (int k=0; k < n; ++k) {
		for (int i=0; i < n; ++i) {
			for (int j=0; j < n; ++j) {
				if (!T[i][j]) {
					T[i][j] = T[i][k] && T[k][j];
				}
			}
		}
		cout << "T" << k+1 << endl; print(T);
	}

	return T;
}

matrix floydWarshall(const matrix &W) {
	int n = W.size();
	matrix D = W;	// D_0
	cout << "D0" << endl; print(D);
	for (int k=0; k < n; ++k) {
//		matrix D_k = D;
		for (int i=0; i < n; ++i) {
			for (int j=0; j < n; ++j) {
				if (D[i][k] != numeric_limits<int>::max() && D[k][j] != numeric_limits<int>::max()) {
					if (D[i][k]+D[k][j] < D[i][j]) {
						D/*_k*/[i][j] = D[i][k]+D[k][j];
					}
				}
			}
		}
		cout << "D" << k+1 << endl; print(D);
//		D = D_k;		// update D_k-1 to D_k before next iteration
	}

	return D;		// D_n
}

int main() {
	// create the graph from Figure 25.1
	int infinity = numeric_limits<int>::max();
	matrix W = {
		{0, 3, 8, infinity, -4},
		{infinity, 0, infinity, 1, 7},
		{infinity, 4, 0, infinity, infinity},
		{2, infinity, -5, 0, infinity},
		{infinity, infinity, infinity, 6, 0}
	};

	matrix D = floydWarshall(W);
	cout << "D" << endl; print(D); cout << endl;

	matrix fig25_5 = {
		{0, infinity, infinity, infinity},
		{infinity, 0, 1, 1},
		{infinity, 1, 0, infinity},
		{1, infinity, 1, 0}
	};

	matrix T = transitiveClosure(fig25_5);
	cout << "T" << endl; print(T);

	return 0;
}
