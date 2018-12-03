#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

enum color { WHITE, GRAY, BLACK };

struct Vertex {
	string key;
	color c;
	unsigned d;    // discovered timestamp
	unsigned f;    // finished timestamp
	Vertex * pred;
	vector<Vertex *> adj;
	Vertex(string key) : key(key), c(WHITE), d(0), f(0), pred(nullptr) {}
};

void dfsVisit(Vertex *u, unsigned &time, list<Vertex *> &l) {
	u->d = ++time;
	u->c = GRAY;
	for (const auto &v : u->adj) {
		if (v->c == WHITE) {
			dfsVisit(v, time, l);
		}
	}
	u->f = ++time;
	u->c = BLACK;
	l.push_front(u);
}

list<Vertex *> dfs(const unordered_map<string, Vertex *> &graph) {
	unsigned time = 0;
	list<Vertex *> l;
	for (const auto &u : graph) {
		if (u.second->c == WHITE) {
			dfsVisit(u.second, time, l);
		}
	}

	return l;
}

list<Vertex *> topologicalSort(const unordered_map<string, Vertex *> &graph) {
	return dfs(graph);
}

int main() {
	// create the graph from Figure 22.7
	unordered_map<string, Vertex *> graph = {
		{"undershorts", new Vertex("undershorts")},
		{"socks", new Vertex("socks")},
		{"watch", new Vertex("watch")},
		{"pants", new Vertex("pants")},
		{"shoes", new Vertex("shoes")},
		{"shirt", new Vertex("shirt")},
		{"belt", new Vertex("belt")},
		{"tie", new Vertex("tie")},
		{"jacket", new Vertex("jacket")}
	};

	graph["undershorts"]->adj.push_back(graph["pants"]);
	graph["undershorts"]->adj.push_back(graph["shoes"]);
	graph["socks"]->adj.push_back(graph["shoes"]);
	graph["pants"]->adj.push_back(graph["belt"]);
	graph["pants"]->adj.push_back(graph["shoes"]);
	graph["shirt"]->adj.push_back(graph["belt"]);
	graph["shirt"]->adj.push_back(graph["tie"]);
	graph["belt"]->adj.push_back(graph["jacket"]);
	graph["tie"]->adj.push_back(graph["jacket"]);

	list<Vertex *> dag = topologicalSort(graph);

	for (const auto &u : dag) {
		cout << u->key << ": " << u->d << "/" << u->f << endl;
	}

	return 0;
}
