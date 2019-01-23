#include <iostream>
#include <limits>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

struct vertex;
typedef vector<vertex *> flow_network;

struct edge {
	int c;		// capacity c(u,v)
	int f;		// flow f(u,v)
	int c_f;		// residual capacity c_f(u,v)
	edge(int capacity) : c(capacity), f(0), c_f(capacity) {}
};

struct vertex {
	char key;
	int e;										// excess flow e(u)
	int h;										// height h(u)
	list<vertex *> N;							// neighbor list u.N
	list<vertex *>::iterator current;	// vertex under consideration in u.N
	unordered_map<vertex *, edge *> adj;
	vertex(char key) : key(key), e(0), h(0) {}
};

// Applies when: u is overflowing, c_f(u,v) > 0, and u.h = v.h + 1
// Action: push delta_f(u,v) = min(u.e, c_f(u,v)) units of flow from u to v
void push(vertex *u, vertex *v) {
	// determine the maximum amount of flow, delta_f, we can push from u to v
	int delta_f = u->adj[v]->c_f;
	if (u->e < delta_f) {
		delta_f = u->e;
	}
	// update the flow of whichever edge, (u,v) or (v,u), is in E accordingly
	if (u->adj[v]->c > 0) { // edge (u,v) is in E
		u->adj[v]->f += delta_f;
		// update residual capacities of edges in E_f
		u->adj[v]->c_f -= delta_f;
		v->adj[u]->c_f += delta_f;
	} else { // edge (v,u) is in E, so we "push" flow to v by reducing flow to u
		v->adj[u]->f -= delta_f;
		// update residual capacities of edges in E_f
		v->adj[u]->c_f += delta_f;
		u->adj[v]->c_f -= delta_f;
	}
	// update the vertices' excess flows
	u->e -= delta_f;
	v->e += delta_f;
}

/* Applies when: u is overflowing and for all v in V such that (u,v) is in E_f,
   we have u.h <= v.h */
// Action: increase the height of u
void relabel(vertex *u) {
	int min_height = numeric_limits<int>::max();
	for (auto const &elem : u->adj) {
		vertex *v = elem.first;
		edge *e = elem.second;
		if (e->c_f > 0) { // edge (u,v) is E_f
			if (v->h < min_height) {
				min_height = v->h;
			}
		}
	}
	u->h = min_height + 1;
}

void initializePreflow(const flow_network &G, vertex *s) {
	for (auto const &v : G) {
		v->h = 0;
		v->e = 0;
	}
	for (auto const &v : G) {
		for (auto const &elem : v->adj) {
			edge *e = elem.second;
			if (e->c > 0) { // edge e is in E
				e->f = 0;
			}
		}
	}
	s->h = G.size();
	for (auto const &elem : s->adj) {
		vertex *v = elem.first;
		edge *e = elem.second;
		if (e->c > 0) { // edge (s,v) is in E (we check in case we allow edges to s in G)
			e->f = e->c;
			// update residual capacities of edges in E_f
			e->c_f = 0;
			v->adj[s]->c_f = e->c;
			// update the vertices' excess flows
			v->e = e->c;
			s->e -= e->c;
		}
	}
}

void discharge(vertex *u) {
	while (u->e > 0) {
		// note, v = *(u->current)
		if (u->current == u->N.end()) {
			relabel(u);
			u->current = u->N.begin();
		} else if (u->adj[*(u->current)]->c_f > 0 && u->h == (*(u->current))->h+1) {
			push(u, *(u->current));
		} else {
			u->current++;
		}
	}
}

void relabelToFront(const flow_network &G, vertex *s, vertex *t) {
	initializePreflow(G, s);
	list<vertex *> L;
	for (auto const &v : G) {
		if (v != s && v != t) { // v is in G.V - {s,t}
			L.push_front(v);
			v->current = v->N.begin();
		}
	}
	list<vertex *>::iterator it = L.begin();
	while (it != L.end()) {
		vertex *u = *it;
		int old_height = u->h;
		discharge(u);
		if (u->h > old_height) { // move u to the front of list L
			L.erase(it);		// remove u from its current position in L
			L.push_front(u);	// add u to the front of L
			it = L.begin();	// update it to point to u in its new position
		}
		++it;
	}
}

int main() {
	// create the flow network G of Figure 26.10
	// vertex set, V
	flow_network G = {
		new vertex('s'), // G[0]
		new vertex('x'), // G[1]
		new vertex('y'), // G[2]
		new vertex('z'), // G[3]
		new vertex('t')  // G[4]
	};

	// edge set, E
	G[0]->adj[G[1]] = new edge(12);
	G[0]->adj[G[2]] = new edge(14);
	G[1]->adj[G[2]] = new edge(5);
	G[1]->adj[G[4]] = new edge(16);
	G[2]->adj[G[3]] = new edge(8);
	G[3]->adj[G[1]] = new edge(7);
	G[3]->adj[G[4]] = new edge(10);

	// create G' = (V, E') from G, where E' = {(u,v) : (u,v) or (v,u) is in E}
	// edge set, E'-E
	G[1]->adj[G[0]] = new edge(0);
	G[2]->adj[G[0]] = new edge(0);
	G[2]->adj[G[1]] = new edge(0);
	G[4]->adj[G[1]] = new edge(0);
	G[3]->adj[G[2]] = new edge(0);
	G[1]->adj[G[3]] = new edge(0);
	G[4]->adj[G[3]] = new edge(0);

	// from G' = (V, E'), it's trivial to create each vertex's neighbor list, u.N
	for (auto const &u : G) {
		for (auto const &elem : u->adj) {
			vertex *v = elem.first;
			u->N.push_back(v);
		}
	}

	relabelToFront(G, G[0], G[4]);

	// preflow f is now a max flow; calculate and print it
	int max_flow = 0;
	for (auto const &elem : G[0]->adj) {
		max_flow += elem.second->f;
	}
	cout << "max flow: " << max_flow << endl;

	// print the corresponding flow network, G
	for (auto const &u : G) {
		cout << u->key << ".e: " << u->e << endl;
		for (auto const &elem : u->adj) {
			vertex *v = elem.first;
			edge *e = elem.second;
			if (e->c > 0) { // edge (u,v) is in E
				cout << "(" << u->key << "," << v->key << ") " << e->f << "/"
						<< e->c << " " << e->c_f << endl;
			}
		}
	}

	// clean up dynamic memory
	for (auto &u : G) {
		for (auto &elem : u->adj) {
			delete elem.second;
		}
		delete u;
	}

	return 0;
}
