#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

struct Vertex;

typedef vector<Vertex *> graph;
typedef vector<vector<int> > matrix;

struct edge {
	Vertex *v;
	int w;
	int w_hat;
	edge(Vertex *v, int w) : v(v), w(w) {}
};

struct Vertex {
	char key;
	int d;
	int h;
	Vertex * pred;
	vector<edge> adj;
	Vertex(char c) : key(c) {}
};

void initSingleSource(const graph &G, Vertex *s) {
	for (auto const &v : G) {
		v->d = numeric_limits<int>::max();
		v->pred = nullptr;
	}
	s->d = 0;
}

void relax(Vertex *u, Vertex *v, int weight) {
	if (u->d != numeric_limits<int>::max() && v->d > u->d + weight) {
		v->d = u->d + weight;
		v->pred = u;
	}
}

bool bellmanFord(const graph &G, Vertex *s) {
	initSingleSource(G, s);
	// make |V|-1 passes over the edges in G.E
	for (unsigned i=0; i < G.size()-1; ++i) {
		for (auto const &u : G) {
			for (auto const  &e : u->adj) { // edge e
				relax(u, e.v, e.w);
			}
		}
	}

	// check for negative-weight cycles
	for (auto const &u : G) {
		for (auto const &e : u->adj) { // edge e
			if (e.v->d > u->d + e.w) {
				return false;
			}
		}
	}
	return true;
}

struct PathCompare {
	bool operator()(Vertex * const a, Vertex * const b) {
		return a->d > b->d; // '>' operator used to implement min priority queue
	}
} pathComp;

/* This implementation uses a vector<Vertex *> and std::sort() to implement a
   min priority queue, inefficiently, since implementing an efficient priority
   queue is not the focus of this exercise. */
void dijkstra(const graph &G, Vertex *s) {
	initSingleSource(G, s);

	vector<Vertex *> Q; // our min priority queue
	for (auto const &v : G) Q.push_back(v);
	sort(Q.begin(), Q.end(), pathComp);

	while (!Q.empty()) {
		Vertex *u = Q.back(); // vertex u with minimum shortest-path estimate, d
		for (auto const &e : u->adj) { // edge e
			relax(u, e.v, e.w_hat);
		}
		Q.pop_back();
		sort(Q.begin(), Q.end(), pathComp);
	}
}

matrix johnson(graph &G) {
	// compute graph G' from G
	Vertex *s = new Vertex('s');
	for (auto const &v : G) s->adj.push_back(edge(v, 0));
	G.push_back(s);

	// compute matrix D = (d_uv)
	int n = G.size()-1;
	matrix D = vector(n, vector<int>(n, numeric_limits<int>::max()));
	if (bellmanFord(G, s) == false) {
		cout << "the input graph contains a negative-weight cycle" << endl;
		// restore graph G from G'
		delete G.back(); G.pop_back();
	} else {
		// set h(v) values to d(s, v) computed by the Bellman-Ford algorithm
		for (auto const &v : G) v->h = v->d;
		// set w_hat values
		for (auto const &u : G) {
			for (auto &e : u->adj) { // edge e
				e.w_hat = e.w + u->h - e.v->h;
			}
		}
		// restore graph G from G'
		delete G.back(); G.pop_back();
		for (unsigned u=0; u < G.size(); ++u) {
			// compute d_hat(u, v) for all v in G.V using Dijkstra's algorithm
			dijkstra(G, G[u]);
			// set d_uv values
			for (unsigned v=0; v < G.size(); ++v) {
				D[u][v] = G[v]->d + G[v]->h - G[u]->h;
			}
		}
	}

	return D;
}

void print(const matrix &m) {
	for (unsigned i=0; i < m.size(); ++i) {
		for (unsigned j=0; j < m[i].size(); ++j) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	// create the graph from Figure 25.1
	// vertex set, G.V
	graph G = {
		new Vertex('1'),
		new Vertex('2'),
		new Vertex('3'),
		new Vertex('4'),
		new Vertex('5')
	};

	// edge set, G.E
	G[0]->adj.push_back(edge(G[1], 3));
	G[0]->adj.push_back(edge(G[2], 8));
	G[0]->adj.push_back(edge(G[4], -4));
	G[1]->adj.push_back(edge(G[3], 1));
	G[1]->adj.push_back(edge(G[4], 7));
	G[2]->adj.push_back(edge(G[1], 4));
	G[3]->adj.push_back(edge(G[0], 2));
	G[3]->adj.push_back(edge(G[2], -5));
	G[4]->adj.push_back(edge(G[3], 6));

	matrix D = johnson(G);
	cout << "D" << endl; print(D);

	for (auto &v : G) {
		delete v;
	}

	return 0;
}
