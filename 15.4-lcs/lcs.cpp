#include <iostream>
#include <vector>

using namespace std;

void lcsLength(vector<char> x, vector<char> y, vector<vector<int> > &c) {
	for (unsigned i=1; i <= x.size(); i++) {
		for (unsigned j=1; j <= y.size(); j++) {
			if (x[i-1] == y[j-1]) {
				c[i][j] = c[i-1][j-1] + 1;
			} else if (c[i-1][j] >= c[i][j-1]) {
				c[i][j] = c[i-1][j];
			} else {
				c[i][j] = c[i][j-1];
			}
		}
	}
}

void printLCS(vector<vector<int> > &c, vector<char> x, int i, int j) {
	if (i == 0 || j == 0) {
		return;
	}
	if (c[i][j-1] > c[i-1][j]) {
		printLCS(c, x, i, j-1);
	} else if (c[i][j] > c[i-1][j]) {
		printLCS(c, x, i-1, j-1);
		cout << x[i-1];
	} else {
		printLCS(c, x, i-1, j);
	}
}

template <class T>
void printTable(vector<vector<T> > &t) {
	for (unsigned i=0; i < t.size(); i++) {
		for (unsigned j=0; j < t[i].size(); j++) {
			cout << t[i][j] << " ";
		}
		cout << endl;
	}
}

template <class T>
void printVector(vector<T> &v) {
	for (const auto &elem : v) {
		cout << elem << " ";
	}
	cout << endl;
}

int main() {
	vector<char> x{'A', 'B', 'C', 'B', 'D', 'A', 'B'};
	vector<char> y{'B', 'D', 'C', 'A', 'B', 'A'};

	vector<vector<int> > c(x.size()+1, vector<int>(y.size()+1, 0));

	cout << "x: ";
	printVector(x);
	cout << "y: ";
	printVector(y);
	cout << endl;

	lcsLength(x, y, c);
	printTable(c);
	cout << endl;

	cout << "printLCS(): ";
	printLCS(c, x, x.size(), y.size());
	cout << endl;

	return 0;
}
