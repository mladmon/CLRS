#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

enum color { WHITE, GRAY, BLACK };

struct Vertex {
	char key;
	color c;
	unsigned d;			// discovered timestamp
	unsigned f;			// finished timestamp
	int minWeight;		// shortest-path estimate
	Vertex * pred;
	vector<pair<Vertex *, int> > adj;
	Vertex(char key) : key(key), c(WHITE), d(0), f(0), pred(nullptr) {}
};

void dfsVisit(Vertex *u, unsigned &time, list<Vertex *> &l) {
	u->d = ++time;
	u->c = GRAY;
	for (const auto &edge : u->adj) {
		Vertex *v = edge.first;
		if (v->c == WHITE) {
			v->pred = u;
			dfsVisit(v, time, l);
		}
	}
	u->f = ++time;
	u->c = BLACK;
	l.push_front(u);
}

list<Vertex *> dfs(const unordered_map<char, Vertex *> &graph) {
	unsigned time = 0;
	list<Vertex *> l;
	for (const auto &elem : graph) {
		if (elem.second->c == WHITE) {
			dfsVisit(elem.second, time, l);
		}
	}

	return l;
}

list<Vertex *> topologicalSort(const unordered_map<char, Vertex *> &graph) {
	return dfs(graph);
}

void initSingleSource(const unordered_map<char, Vertex *> &graph, Vertex *s) {
	for (const auto &elem : graph) {
		elem.second->minWeight = numeric_limits<int>::max();
		elem.second->pred = nullptr;
	}
	s->minWeight = 0;
}

void relax(Vertex *u, Vertex *v, int uvWeight) {
	if (v->minWeight > static_cast<long>(u->minWeight) + uvWeight) {
		v->minWeight = u->minWeight + uvWeight;
		v->pred = u;
	}
}

void dagShortestPaths(const unordered_map<char, Vertex *> &graph, Vertex *s) {
	list<Vertex *> vertices = topologicalSort(graph);
	initSingleSource(graph, s);
	for (auto const &u : vertices) {
		for (auto const &edge : u->adj) {
			relax(u, edge.first, edge.second);
		}
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

int main() {
	// create the graph from Figure 24.5
	// vertex set, V
	unordered_map<char, Vertex *> graph = {
		{'r', new Vertex('r')},
		{'s', new Vertex('s')},
		{'t', new Vertex('t')},
		{'x', new Vertex('x')},
		{'y', new Vertex('y')},
		{'z', new Vertex('z')}
	};

	// edge set, E
	graph['r']->adj.push_back(make_pair(graph['s'], 5));
	graph['r']->adj.push_back(make_pair(graph['t'], 3));
	graph['s']->adj.push_back(make_pair(graph['t'], 2));
	graph['s']->adj.push_back(make_pair(graph['x'], 6));
	graph['t']->adj.push_back(make_pair(graph['x'], 7));
	graph['t']->adj.push_back(make_pair(graph['y'], 4));
	graph['t']->adj.push_back(make_pair(graph['z'], 2));
	graph['x']->adj.push_back(make_pair(graph['y'], -1));
	graph['x']->adj.push_back(make_pair(graph['z'], 1));
	graph['y']->adj.push_back(make_pair(graph['z'], -2));

	dagShortestPaths(graph, graph['s']);

	for (auto const &elem : graph) {
		Vertex *v = elem.second;
		if (v->minWeight == numeric_limits<int>::max()) {
			cout << "d(s," << v->key << "): " << v->minWeight << "  | shortest path: ";
		}
		else {
			cout << "d(s," << v->key << "): " << v->minWeight << "           | shortest path: ";
		}
		printPath(graph['s'], v);
		cout << endl;
	}

	for (auto &elem : graph) {
		delete elem.second;
	}

	return 0;
}
