#include <stdio.h>

#define MAX_N 100
#define MAX_M 500

typedef struct {
	int u;
	int v;
	int w;
} Edge;

typedef struct {
	Edge edges[MAX_M];
	int n;
	int m;
} Graph;

void init_graph(Graph *G, int n) {
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G, int u, int v, int w) {
	G->m++;
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m].w = w;
}

int pi[MAX_N];
int p[MAX_N];

void Bellman_Ford(Graph *G, int s) {
	int i;
	for(i = 1; i <= G->n; i++) {
		pi[i] = 9999;
		p[i] = -1;
	}
	pi[s] = 0;
	p[s] = -1;
	int it;
	for(it = 1; it <= G->n; it++) {
		for(i = 1; i <= G->m; i++) {
			int u = G->edges[i].u;
			int v = G->edges[i].v;
			int w = G->edges[i].w;
			if(pi[u] + w < pi[v]) {
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
}

int main() {
	Graph G;
	int n, m, e, u, v, w;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 1; e <= m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	Bellman_Ford(&G, 1);
	int i;
	for(i = 1; i <= G.n; i++) {
		printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
	}
	return 0;
}
