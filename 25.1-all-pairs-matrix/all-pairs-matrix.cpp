#include <iostream>
#include <vector>
#include <limits>

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

matrix extendShortestPaths(const matrix &L, const matrix &W) {
	int n = L.size();
	matrix L_prime(n, vector<int>(n, numeric_limits<int>::max()));
	for (int i=0; i < n; ++i) {
		for (int j=0; j < n; ++j) {
			for (int k=0; k < n; ++k) {
				// if either l_ik or w_kj is infinity, there is no path i~>k->j
				if (L[i][k] != numeric_limits<int>::max() && W[k][j] != numeric_limits<int>::max()) {
					if (/*static_cast<long>(*/L[i][k]/*)*/+W[k][j] < L_prime[i][j])
						L_prime[i][j] = L[i][k]+W[k][j];
				}
			}
		}
	}

	return L_prime;
}

matrix slowAllPairsShortestPaths(const matrix &W) {
	matrix L = W;
	cout << "L1" << endl; print(L);
	for (unsigned m=2; m < W.size(); ++m) {
		L = extendShortestPaths(L, W);
		cout << "L" << m << endl; print(L);
	}

	return L;
}

matrix fasterAllPairsShortestPaths(const matrix &W) {
	matrix L = W;
	cout << "L1" << endl; print(L);
	unsigned m = 1;
	while (m < W.size()-1) {
		L = extendShortestPaths(L, L);
		m *= 2;
		cout << "L" << m << endl; print(L);
	}

	return L;
}

int main() {
	// create the graph from Figure 25.1 in adjacency-matrix representation
	int infinity = numeric_limits<int>::max();
	matrix W = {
		{0, 3, 8, infinity, -4},
		{infinity, 0, infinity, 1, 7},
		{infinity, 4, 0, infinity, infinity},
		{2, infinity, -5, 0, infinity},
		{infinity, infinity, infinity, 6, 0}
	};
	cout << "W" << endl; print(W);

	matrix D = slowAllPairsShortestPaths(W);
	cout << "D" << endl; print(D); cout << endl;

	D = fasterAllPairsShortestPaths(W);
	cout << "D" << endl; print(D);

	matrix fig25_2 = {
		{0, infinity, infinity, infinity, -1, infinity},
		{1, 0, infinity, 2, infinity, infinity},
		{infinity, 2, 0, infinity, infinity, -8},
		{-4, infinity, infinity, 0, 3, infinity},
		{infinity, 7, infinity, infinity, 0, infinity},
		{infinity, 5, 10, infinity, infinity, 0}
	};

	cout << endl << "Figure 25.2" << endl;
	D = slowAllPairsShortestPaths(fig25_2);
	cout << "D" << endl; print (D); cout << endl;
	D = fasterAllPairsShortestPaths(fig25_2);
	cout << "D" << endl; print(D);

	return 0;
}
