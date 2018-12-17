#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

//#define NDEBUG
#include <cassert>

using namespace std;

struct Vertex {
	char key;
	vector<Vertex *> *tree;
	Vertex(char key) : key(key), tree(nullptr) {}
};

struct Edge {
	Vertex * v1;
	Vertex * v2;
	unsigned weight;
	Edge(Vertex *f, Vertex *s, unsigned w) : v1(f), v2(s), weight(w) {}
};

// needed by std::sort() to sort edges in order of nondecreasing weight
struct EdgeCompare {
	bool operator()(Edge * const e1, Edge * const e2) {
		return e1->weight < e2->weight;
	}
} edgeComp;

vector<Edge *> mstKruskal(const unordered_map<char, Vertex *> &V, vector<Edge *> &E) {
	vector<Edge *> A;
	for (const auto &elem : V) {
		elem.second->tree = new vector<Vertex *>(1, elem.second);
	}

	// sort the edges of G.E into nondecreasing order by weight w
	sort(E.begin(), E.end(), edgeComp);

	// this deletes |V|-1 trees
	for (const auto &edge : E) {
		if (edge->v1->tree != edge->v2->tree) {
			// A = A U {(u,v)}
			A.push_back(edge);

			// Union(u,v)
			vector<Vertex *> *v2Tree = edge->v2->tree;
			for (auto &v : *(v2Tree)) {
				v->tree = edge->v1->tree;
				edge->v1->tree->push_back(v);
			}
			assert(v2Tree != edge->v2->tree);
			assert(edge->v2->tree == edge->v1->tree);
			delete v2Tree;
		}
	}

	return A;
}

int main() {
	// create the graph from Figure 23.4
	unordered_map<char, Vertex *> vertices;
	for (char key = 'a'; key < 'j'; ++key) {
		vertices.insert({key, new Vertex(key)});
	}

	vector<Edge *> edges = {
		new Edge(vertices['a'], vertices['b'], 4),
		new Edge(vertices['a'], vertices['h'], 8),
		new Edge(vertices['b'], vertices['c'], 8),
		new Edge(vertices['b'], vertices['h'], 11),
		new Edge(vertices['c'], vertices['d'], 7),
		new Edge(vertices['c'], vertices['f'], 4),
		new Edge(vertices['c'], vertices['i'], 2),
		new Edge(vertices['d'], vertices['e'], 9),
		new Edge(vertices['d'], vertices['f'], 14),
		new Edge(vertices['e'], vertices['f'], 10),
		new Edge(vertices['f'], vertices['g'], 2),
		new Edge(vertices['g'], vertices['h'], 1),
		new Edge(vertices['g'], vertices['i'], 6),
		new Edge(vertices['h'], vertices['i'], 7)
	};

	vector<Edge *> mst = mstKruskal(vertices, edges);

	unsigned mstWeight = 0;
	for (const auto &e : mst) {
		cout << "(" << e->v1->key << "," << e->v2->key << "): " << e->weight << endl;
		mstWeight += e->weight;
	}
	cout << "MST weight: " << mstWeight << endl;

	/* delete the single remaining vector<Vertex *> *tree for any vertex; all
	   vertices belong to the same tree after mstKruskal() is finished! */
	delete(vertices['a']->tree);

	for (auto &v : vertices) {
		delete v.second;
	}

	for (auto &e : edges) {
		delete e;
	}

	return 0;
}
