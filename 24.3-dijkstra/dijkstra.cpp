#include <iostream>
#include <utility>
#include <limits>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Vertex {
	char key;
	int d;										// shortest-path estimate
	Vertex * pred;								// predecessor in the shortest-paths tree
	vector<pair<Vertex *, int> > adj;	// adjacency list (edge = vertex, weight)
	Vertex(char key) : key(key) {}
};

struct PathCompare {
	bool operator()(Vertex * const a, Vertex * const b) {
		return a->d > b->d; // to implement min priority queue
	}
} pathComp;

void initSingleSource(const unordered_map<char, Vertex *> &graph, Vertex *s) {
	for (const auto &elem : graph) {
		elem.second->d = numeric_limits<int>::max();
		elem.second->pred = nullptr;
	}
	s->d = 0;
}

void relax(Vertex *u, Vertex *v, int weight) {
	if (v->d > static_cast<long>(u->d) + weight) {
		v->d = u->d + weight;
		v->pred = u;
	}
}

// use a vector<Vertex *> and std::sort() to implement min priority queue (inefficiently)
void dijkstra(const unordered_map<char, Vertex *> &graph, Vertex *s) {
	initSingleSource(graph, s);

	vector<Vertex *> Q;
	for (const auto &elem : graph) { Q.push_back(elem.second); }
	sort(Q.begin(), Q.end(), pathComp);

	while (!Q.empty()) {
		Vertex *u = Q.back();
		for (auto const &edge : u->adj) {
			Vertex *v = edge.first;
			int weight = edge.second;
			relax(u, v, weight);
		}
		Q.pop_back();
		sort(Q.begin(), Q.end(), pathComp);
	}
}

void printPath(Vertex *s, Vertex *v) {
	if (v == s) {
		cout << s->key << " ";
	} else if (v->pred == nullptr) {
		cout << "no path from " << s->key << " to " << v->key << " exists";
	} else {
		printPath(s, v->pred);
		cout << v->key << " ";
	}
}

void printShortestPaths(const unordered_map<char, Vertex *> &graph, Vertex *s) {
	for (auto const &elem : graph) {
		Vertex *v = elem.second;
		if (v->d == numeric_limits<int>::max()) {
			cout << "d(s," << v->key << "): " << v->d << "  | shortest path: ";
		}
		else {
			cout << "d(s," << v->key << "): " << v->d << "           | shortest path: ";
		}
		printPath(s, v);
		cout << endl;
	}
}

int main() {
	// create the graph from Figure 24.6
	unordered_map<char, Vertex *> graph = {
		{'s', new Vertex('s')},
		{'t', new Vertex('t')},
		{'x', new Vertex('x')},
		{'y', new Vertex('y')},
		{'z', new Vertex('z')}
	};

	graph['s']->adj.push_back(make_pair(graph['t'], 10));
	graph['s']->adj.push_back(make_pair(graph['y'], 5));
	graph['t']->adj.push_back(make_pair(graph['x'], 1));
	graph['t']->adj.push_back(make_pair(graph['y'], 2));
	graph['x']->adj.push_back(make_pair(graph['z'], 4));
	graph['y']->adj.push_back(make_pair(graph['t'], 3));
	graph['y']->adj.push_back(make_pair(graph['x'], 9));
	graph['y']->adj.push_back(make_pair(graph['z'], 2));
	graph['z']->adj.push_back(make_pair(graph['s'], 7));
	graph['z']->adj.push_back(make_pair(graph['x'], 6));

	dijkstra(graph, graph['s']);
	printShortestPaths(graph, graph['s']);

	for (auto &elem : graph) {
		delete elem.second;
	}

	return 0;
}
