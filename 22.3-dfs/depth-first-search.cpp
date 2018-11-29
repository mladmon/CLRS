#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

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

void dfsVisit(Vertex *u, unsigned &time) {
	u->d = ++time;			// white vertex u has just been discovered
	u->c = GRAY;
	for (const auto &v : u->adj) {
		if (v->c == WHITE) {
			v->pred = u;
			dfsVisit(v, time);
		}
	}
	u->f = ++time;
	u->c = BLACK;
}

void dfs(const unordered_map<char, Vertex *> &graph) {
	unsigned time = 0;
	/* unordered_map<char, Vertex *>::const_iterator it = graph.begin(); */
	for (auto it = graph.begin(); it != graph.end(); ++it) {
		if (it->second->c == WHITE) {
			dfsVisit(it->second, time);
		}
	}
}

int main() {
	// create the graph from Figure 22.4
	// vertex set, V
	unordered_map<char, Vertex *> graph;
	for (char c='u'; c < '{'; ++c) {
		graph.insert({c, new Vertex(c)});
	}

	// edge set, E
	graph['u']->adj.push_back(graph['v']);
	graph['u']->adj.push_back(graph['x']);
	graph['v']->adj.push_back(graph['y']);
	graph['w']->adj.push_back(graph['y']);
	graph['w']->adj.push_back(graph['z']);
	graph['x']->adj.push_back(graph['v']);
	graph['y']->adj.push_back(graph['x']);
	graph['z']->adj.push_back(graph['z']);

	dfs(graph);
	for (auto &elem : graph) {
		cout << elem.first << ": " << elem.second->d << "/" << elem.second->f << endl;
	}

	assert(graph['v']->pred->pred->key == 'y');
	assert(graph['u']->pred == nullptr);
	assert(graph['w']->pred == nullptr);
	assert(graph['z']->pred == nullptr);

	/*for (auto it = graph.begin(); it != graph.end(); ++it) {
		cout << "Deleting " << it->first << endl;
		delete it->second;
	}*/
	// here's another, C++11's range-based for loop; elements are pair objects
	for (auto &v : graph) {
		cout << "Deleting " << v.first << endl;
		delete v.second;
	}

	return 0;
}
