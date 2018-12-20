#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

struct Vertex {
	char key;
	int d;										// shortest-path estimate
	Vertex * pred;								// v.pi
	vector<pair<Vertex *, int> > adj;	// list of edges to adjacent vertices
	Vertex(char k) : key(k) {}
};

void initSingleSource(const unordered_map<char, Vertex *> &graph, Vertex *s) {
	for (const auto &elem : graph) {
		elem.second->d = numeric_limits<int>::max();
		elem.second->pred = nullptr;
	}
	s->d = 0;
}

void relax(Vertex *u, Vertex *v, int weight) {
	//cout << "v->d: " << v->d << " u->d: " << u->d << " weight: " << weight << endl;
	if (v->d > static_cast<long>(u->d) + weight) { // type conversion needed to avoid overflow
		v->d = u->d + weight;
		v->pred = u;
	}
}

bool bellmanFord(const unordered_map<char, Vertex *> &graph, Vertex *s) {
	initSingleSource(graph, s);
	// make |V|-1 passes over the edges in G.E
	for (unsigned i=0; i < graph.size()-1; ++i) {
		for (const auto &elem : graph) {
			Vertex *u = elem.second;
			for (const auto &edge : u->adj) {
				Vertex *v = edge.first;
				int weight = edge.second;
				relax(u, v, weight);
			}
		}
	}

	// check for negative-weight cycles
	for (const auto &elem : graph) {
		Vertex *u = elem.second;
		for (const auto &edge : u->adj) {
			Vertex *v = edge.first;
			int weight = edge.second;
			if (v->d > u->d + weight) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	// create the graph from Figure 24.4
	// vertex set, G.V
	unordered_map<char, Vertex *> graph = {
		{'s', new Vertex('s')},
		{'t', new Vertex('t')},
		{'x', new Vertex('x')},
		{'y', new Vertex('y')},
		{'z', new Vertex('z')}
	};
	// edge set, G.E
	graph['s']->adj.push_back(make_pair(graph['t'], 6));	// return value from std::make_pair() is a temporary (unnamed) object of type pair<Vertex *, int> that's passed to std::vector.push_back() as an rvalue reference, so its contents are moved to the new element being added to the vector
	graph['s']->adj.push_back(make_pair(graph['y'], 7));
	graph['t']->adj.push_back({graph['x'], 5});				// same effects as above, but uses list initialization to initialize a temporary (unnamed) object of type pair<Vertex *, int>
	graph['t']->adj.push_back({graph['y'], 8});
	graph['t']->adj.push_back({graph['z'], -4});
	graph['x']->adj.push_back(make_pair(graph['t'], -2));
	graph['y']->adj.push_back(make_pair(graph['x'], -3));
	graph['y']->adj.push_back(make_pair(graph['z'], 9));
	graph['z']->adj.push_back(make_pair(graph['s'], 2));
	graph['z']->adj.push_back(make_pair(graph['x'], 7));

	bool noNegativeWeightCycles = bellmanFord(graph, graph['s']);
	if (noNegativeWeightCycles) {
		cout << "graph contains no negative-weight cycles" << endl;
		for (const auto &elem : graph) {
			Vertex *u = elem.second;
			cout << " d(s," << u->key << "): " << u->d;
			if (u->pred != nullptr) {
				cout << "\t" << u->key << "->pred: " << u->pred->key;
			}
			cout << endl;
		}
	}

	for (auto &elem : graph) {
		delete elem.second;
	}

	return 0;
}
