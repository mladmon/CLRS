#include <iostream>
#include <limits>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

struct Vertex;

typedef unordered_map<char, Vertex *> flow_network;
enum color { WHITE, GRAY, BLACK };

struct edge {
	Vertex *v;
	int c;		// capacity c(u,v)
	int f;		// flow f(u,v)
	int c_f;		// residual capacity c_f(u,v)
	edge(Vertex *v, int capacity) : v(v), c(capacity), f(0), c_f(capacity) {}
};

struct Vertex {
	char key;
	color c;
	int d;
	Vertex * pred;
	unordered_map<Vertex *, edge *> adj;
	Vertex(char key) : key(key), c(WHITE), d(-1), pred(nullptr) {}
};

// modified to perform breadth-first search on G_f
void bfs(flow_network &G, Vertex *s) {
	for (auto &v_pair : G) {
		Vertex *u = v_pair.second;
		u->c = WHITE;
		u->d = -1;
		u->pred = nullptr;
	}
	s->c = GRAY;
	s->d = 0;
	queue<Vertex *> q;
	q.push(s);
	while (!q.empty()) {
		Vertex *u = q.front();
		for (const auto &e_pair : u->adj) {
			edge *e = e_pair.second;
			// only edges w/ nonzero residual capacity are in G_f
			if (e->c_f > 0) {
				if (e->v->c == WHITE) {
					e->v->c = GRAY;
					e->v->pred = u;
					e->v->d = u->d + 1;
					q.push(e->v);
				}
			}
		}
		u->c = BLACK;
		q.pop();
	}
}

bool findAugmentingPath(Vertex *s, Vertex *v, vector<Vertex *> &p) {
	if (v == s) {
		p.push_back(s);
	} else if (v->pred == nullptr) {
		return false;
	} else {
		findAugmentingPath(s, v->pred, p);
		p.push_back(v);
	}
	return true;
}

/* if an edge has a nonzero capacity, c(u,v), it is an edge in G. If an edge
	has a nonzero residual capacity, c_f(u,v), it is an edge in residual
	network G_f. Note, an edge may be in both, G and G_f. */
int fordFulkerson(flow_network &G, Vertex *s, Vertex *t) {
	vector<Vertex *> p;	// augmenting path
	bfs(G, G['s']);		// performs breadth-first search on G_f
	while (findAugmentingPath(G['s'], G['t'], p)) {
		int residualCapacityOfP = numeric_limits<int>::max();
		for (unsigned i=1; i < p.size(); ++i) {
			int c_fi = p[i-1]->adj[p[i]]->c_f;
			if (c_fi < residualCapacityOfP) {
				residualCapacityOfP = c_fi;
			}
		}

		for (unsigned i=1; i < p.size(); ++i) {
			if (p[i-1]->adj[p[i]]->c > 0) { // edge (p[i-1], p[i]) is in E
				p[i-1]->adj[p[i]]->f += residualCapacityOfP;
				// restore G_f (residual capacities of edges on p need to be updated)
				p[i-1]->adj[p[i]]->c_f -= residualCapacityOfP;
				p[i]->adj[p[i-1]]->c_f += residualCapacityOfP;
			} else { // edge (p[i], p[i-1]) is in E
				p[i]->adj[p[i-1]]->f -= residualCapacityOfP;
				// restore G_f (residual capacities of edges on p need to be updated)
				p[i]->adj[p[i-1]]->c_f += residualCapacityOfP;
				p[i-1]->adj[p[i]]->c_f -= residualCapacityOfP;
			}
		}

		p.clear();
		bfs(G, G['s']);
	}

	int maxFlow = 0;
	for (auto const &e_pair : s->adj) {
		edge *e = e_pair.second;
		maxFlow += e->f;
	}

	return maxFlow;
}

int main() {
	// create the flow network G of Figure 26.1(b)
	// vertex set, V
	flow_network G = {
		{'s', new Vertex('s')},
		{'w', new Vertex('w')},	// v1
		{'x', new Vertex('x')},	// v2
		{'y', new Vertex('y')},	// v3
		{'z', new Vertex('z')},	// v4
		{'t', new Vertex('t')}
	};

	// edge set, E
	G['s']->adj[G['w']] = new edge(G['w'], 16);
	G['s']->adj[G['x']] = new edge(G['x'], 13);
	G['w']->adj[G['y']] = new edge(G['y'], 12);
	G['x']->adj[G['w']] = new edge(G['w'], 4);
	G['x']->adj[G['z']] = new edge(G['z'], 14);
	G['y']->adj[G['x']] = new edge(G['x'], 9);
	G['y']->adj[G['t']] = new edge(G['t'], 20);
	G['z']->adj[G['y']] = new edge(G['y'], 7);
	G['z']->adj[G['t']] = new edge(G['t'], 4);

	// create G' = (V, E') from G, where E' = {(u,v) : (u,v) or (v,u) is in E}
	// edge set, E'-E
	G['w']->adj[G['s']] = new edge(G['s'], 0);
	G['x']->adj[G['s']] = new edge(G['s'], 0);
	G['y']->adj[G['w']] = new edge(G['w'], 0);
	G['w']->adj[G['x']] = new edge(G['x'], 0);
	G['z']->adj[G['x']] = new edge(G['x'], 0);
	G['x']->adj[G['y']] = new edge(G['y'], 0);
	G['t']->adj[G['y']] = new edge(G['y'], 0);
	G['y']->adj[G['z']] = new edge(G['z'], 0);
	G['t']->adj[G['z']] = new edge(G['z'], 0);

	int maxFlow = fordFulkerson(G, G['s'], G['t']);
	cout << "max flow: " << maxFlow << endl;

	for (auto &v_pair : G) {
		Vertex *v = v_pair.second;
		for (auto &e_pair : v->adj) {
			edge *e = e_pair.second;
			delete e;
		}
		delete v;
	}

	return 0;
}
