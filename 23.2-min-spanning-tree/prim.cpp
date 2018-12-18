#include <iostream>
#include <utility>
#include <limits>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Vertex {
	char key;
	unsigned minWeight;
	Vertex * pred;
	vector<pair<Vertex *, unsigned> > adj;
	Vertex(char key) : key(key), minWeight(numeric_limits<unsigned>::max()), pred(nullptr) {}
};

// used with std::sort() to implement a DYNAMIC min priority queue :)
struct LightEdge {
	bool operator()(Vertex * const u, Vertex * const v) {
		return u->minWeight > v->minWeight;
	}
} lightEdge;

void mstPrim(const unordered_map<char, Vertex *> &G, Vertex * const r) {
	r->minWeight = 0;

	vector<Vertex *> Q;
	for (const auto &elem : G) { Q.push_back(elem.second); }
	sort(Q.begin(), Q.end(), lightEdge);

	while (!Q.empty()) {
		Vertex *u = Q.back();
		for (const auto &edge : u->adj) {
			Vertex *v = edge.first;
			unsigned weight = edge.second;
			if (find(Q.begin(), Q.end(), v) != Q.end() && weight < v->minWeight) {
				v->pred = u;
				v->minWeight = weight;
			}
		}
		Q.pop_back();
		sort(Q.begin(), Q.end(), lightEdge);
	}
}

int main() {
	// create the graph from Figure 23.5
	unordered_map<char, Vertex *> graph;
	for (char key='a'; key < 'j'; ++key) {
		graph[key] = new Vertex(key);
	}

	graph['a']->adj.push_back(make_pair(graph['b'], 4));
	graph['a']->adj.push_back(make_pair(graph['h'], 8));
	graph['b']->adj.push_back(make_pair(graph['a'], 4));
	graph['b']->adj.push_back(make_pair(graph['c'], 8));
	graph['b']->adj.push_back(make_pair(graph['h'], 11));
	graph['c']->adj.push_back(make_pair(graph['b'], 8));
	graph['c']->adj.push_back(make_pair(graph['d'], 7));
	graph['c']->adj.push_back(make_pair(graph['f'], 4));
	graph['c']->adj.push_back(make_pair(graph['i'], 2));
	graph['d']->adj.push_back(make_pair(graph['c'], 7));
	graph['d']->adj.push_back(make_pair(graph['e'], 9));
	graph['d']->adj.push_back(make_pair(graph['f'], 14));
	graph['e']->adj.push_back(make_pair(graph['d'], 9));
	graph['e']->adj.push_back(make_pair(graph['f'], 10));
	graph['f']->adj.push_back(make_pair(graph['c'], 4));
	graph['f']->adj.push_back(make_pair(graph['d'], 14));
	graph['f']->adj.push_back(make_pair(graph['e'], 10));
	graph['f']->adj.push_back(make_pair(graph['g'], 2));
	graph['g']->adj.push_back(make_pair(graph['f'], 2));
	graph['g']->adj.push_back(make_pair(graph['h'], 1));
	graph['g']->adj.push_back(make_pair(graph['i'], 6));
	graph['h']->adj.push_back(make_pair(graph['a'], 8));
	graph['h']->adj.push_back(make_pair(graph['b'], 11));
	graph['h']->adj.push_back(make_pair(graph['g'], 1));
	graph['h']->adj.push_back(make_pair(graph['i'], 7));
	graph['i']->adj.push_back(make_pair(graph['c'], 2));
	graph['i']->adj.push_back(make_pair(graph['g'], 6));
	graph['i']->adj.push_back(make_pair(graph['h'], 7));

	mstPrim(graph, graph['a']);
	// print minimum spanning tree edges (v, v.pi) and associated weights
	unsigned mstWeight = 0;
	for (char key='b'; key < 'j'; ++key) { // each vertex other than root, 'a'
		cout << "(" << key << "," << graph[key]->pred->key << "): ";
		for (const auto &edge : graph[key]->adj) {
			if (edge.first == graph[key]->pred) {
				cout << edge.second << endl;
				mstWeight += edge.second;
			}
		}
	}
	cout << "mst weight: " << mstWeight << endl;

	for (auto &v : graph) {
		delete v.second;
	}

	return 0;
}
