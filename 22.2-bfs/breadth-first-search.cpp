#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

enum color { WHITE, GRAY, BLACK };

struct Vertex {
	char key;
	color c;
	Vertex * pred;
	int d;
	vector<Vertex *> adj;
	Vertex(char key) : key(key), c(WHITE), pred(nullptr), d(-1) {}
};

void bfs(Vertex *s) {
	// color the source vertex gray, set its distance to 0, and enqueue it
	s->c = GRAY;
	s->d = 0;
	queue<Vertex *> q;
	q.push(s);

	// inspect the adj list of each gray vertex, u, building a breadth-first tree
	while (!q.empty()) {
		Vertex *u = q.front();
		for (const auto &v : u->adj) {
			if (v->c == WHITE) {
				v->c = GRAY;
				v->pred = u;
				v->d = u->d + 1;
				q.push(v);
			}
		}
		u->c = BLACK;
		q.pop();
	}
}

void printPath(Vertex *s, Vertex *v) {
	if (v == s) {
		cout << s->key << " ";
	} else if (v->pred == nullptr) {
		cout << "No path from " << s->key << " to " << v->key << " exists.";
	} else {
		printPath(s, v->pred);
		cout << v->key << " ";
	}
}

int main() {
	// first create the undirected graph from Figure 22.3
	// vertex set, V
	Vertex *r = new Vertex('r');
	Vertex *s = new Vertex('s');
	Vertex *t = new Vertex('t');
	Vertex *u = new Vertex('u');
	Vertex *v = new Vertex('v');
	Vertex *w = new Vertex('w');
	Vertex *x = new Vertex('x');
	Vertex *y = new Vertex('y');

	// edge set, E
	r->adj.push_back(s); /*r->adj.push_back(v);*/
	s->adj.push_back(r); s->adj.push_back(w);
	t->adj.push_back(u); t->adj.push_back(w); t->adj.push_back(x);
	u->adj.push_back(t); u->adj.push_back(x); u->adj.push_back(y);
	v->adj.push_back(r);
	w->adj.push_back(s); w->adj.push_back(t); w->adj.push_back(x);
	x->adj.push_back(t); x->adj.push_back(u); x->adj.push_back(w); x->adj.push_back(y);
	y->adj.push_back(u); y->adj.push_back(x);

	// graph, G = (V, E)
	unordered_map<char, Vertex *> graph({
		{r->key, r},
		{s->key, s},
		{t->key, t},
		{u->key, u},
		{v->key, v},
		{w->key, w},
		{x->key, x},
		{y->key, y}
	});

	/* you can access vertices directly, via graph['key'], or via graph[v->key],
	   the last method being a bit superfluous */
	bfs(s);
	printPath(s, v); cout << endl;
	printPath(s, graph['u']); cout << endl;
	printPath(s, graph[y->key]); cout << endl;
	cout << graph['v']->key << ".d: " << graph['v']->d << endl;
	cout << graph['y']->key << ".d: " << graph['y']->d << endl;

	delete r;
	delete s;
	delete t;
	delete u;
	delete v;
	delete w;
	delete x;
	delete y;

	return 0;
}
