#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum color { WHITE, GRAY, BLACK };

struct Vertex {
	char key;
	color c;
	unsigned d;    // discovered timestamp
	unsigned f;    // finished timestamp
	Vertex * pred;
	vector<Vertex *> adj;
	Vertex(char key) : key(key), c(WHITE), d(0), f(0), pred(nullptr) {}
};

void dfsVisit(Vertex *u, unsigned &time, bool printTrees) {
	u->d = ++time;
	u->c = GRAY;
	for (const auto &v : u->adj) {
		if (v->c == WHITE) {
			v->pred = u;
			dfsVisit(v, time, printTrees);
		}
	}
	u->f = ++time;
	u->c = BLACK;
	if (printTrees) {
		cout << u->key << " ";
	}
}

void dfs(const vector<Vertex *> &graph, bool printTrees) {
	unsigned time = 0;
	for (const auto &u: graph) {
		if (u->c == WHITE) {
			dfsVisit(u, time, printTrees);
			if (printTrees) { cout << endl; }
		}
	}
}

struct VertexCompare {
	bool operator()(const Vertex *a, const Vertex *b) {
		return a->f > b->f;
	}
} vertexCompare;

void stronglyConnectedComponents(const vector<Vertex *> &graph) {
	// call DFS() on G to compute finishing times u.f for each vertex u
	dfs(graph, false);

	// compute G^T, the transpose of G
	// vertex set, V
	vector<Vertex *> graph_t;
	for (const auto &v : graph) {
		Vertex *v_t = new Vertex(v->key);
		v_t->f = v->f; // used for sorting G^T and later overwritten by DFS()
		graph_t.push_back(v_t);
	}
	// edge set, E^T
	for (unsigned i=0; i < graph.size(); ++i) {
		for (const auto &v : graph[i]->adj) { // create edge (v, graph[i]) in G^T
			switch(v->key) {
				case 'a'	:	graph_t[0]->adj.push_back(graph_t[i]);
								break;
				case 'b'	:	graph_t[1]->adj.push_back(graph_t[i]);
								break;
				case 'c'	:	graph_t[2]->adj.push_back(graph_t[i]);
								break;
				case 'd'	:	graph_t[3]->adj.push_back(graph_t[i]);
								break;
				case 'e'	:	graph_t[4]->adj.push_back(graph_t[i]);
								break;
				case 'f'	:	graph_t[5]->adj.push_back(graph_t[i]);
								break;
				case 'g'	:	graph_t[6]->adj.push_back(graph_t[i]);
								break;
				case 'h'	:	graph_t[7]->adj.push_back(graph_t[i]);
								break;
			}
		}
	}

	// call DFS() on G^T after sorting its vertices in order of descending u.f
	sort(graph_t.begin(), graph_t.end(), vertexCompare);
	dfs(graph_t, true);

	for (auto &v : graph_t) {
		delete v;
	}
}

int main() {
	// create the graph from Figure 22.9
	vector<Vertex *> graph = {
		new Vertex('a'),	// graph[0]
		new Vertex('b'),	// graph[1]
		new Vertex('c'),	// graph[2]
		new Vertex('d'),	// graph[3]
		new Vertex('e'),	// graph[4]
		new Vertex('f'),	// graph[5]
		new Vertex('g'),	// graph[6]
		new Vertex('h')	// graph[7]
	};

	graph[0]->adj.push_back(graph[1]);
	graph[1]->adj.push_back(graph[2]);
	graph[1]->adj.push_back(graph[4]);
	graph[1]->adj.push_back(graph[5]);
	graph[2]->adj.push_back(graph[3]);
	graph[2]->adj.push_back(graph[6]);
	graph[3]->adj.push_back(graph[2]);
	graph[3]->adj.push_back(graph[7]);
	graph[4]->adj.push_back(graph[0]);
	graph[4]->adj.push_back(graph[5]);
	graph[5]->adj.push_back(graph[6]);
	graph[6]->adj.push_back(graph[5]);
	graph[6]->adj.push_back(graph[7]);
	graph[7]->adj.push_back(graph[7]);

	stronglyConnectedComponents(graph);

	for (auto &v : graph) {
		delete v;
	}

	return 0;
}
