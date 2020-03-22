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

int parent[MAX_N];

int find_root(int u) {
	if(parent[u] == u) return u;
	else return find_root(parent[u]);
}

int Kruskal(Graph *G, Graph *T) {
	int i, j;
	for(i = 1; i <= (G->m)-1; i++) {
		for(j = i+1; j <= G->m; j++) {
			if(G->edges[i].w > G->edges[j].w) {
				Edge temp = G->edges[i];
				G->edges[i] = G->edges[j];
				G->edges[j] = temp;
			}
		}
	}
	for(i = 1; i <= G->n; i++) {
		parent[i] = i;
	}
	init_graph(T, G->n);
	int sum_w = 0;
	for(i = 1; i <= G->m; i++) {
		int u = G->edges[i].u;
		int v = G->edges[i].v;
		int w = G->edges[i].w;
		int root_u = find_root(u);
		int root_v = find_root(v);
		if(root_u != root_v) {
			add_edge(T, u, v, w);
			parent[root_v] = root_u;
			sum_w += w;
		}
	}
	return sum_w;
}

int main() {
	Graph G, T;
	int n, m, e, u, v, w;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 1; e <= m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	int sum_w = Kruskal(&G, &T);
	printf("%d\n", sum_w);
	int i;
	for(i = 1; i <= T.m; i++) {
		if(T.edges[i].u > T.edges[i].v) {
			int temp = T.edges[i].u;
			T.edges[i].u = T.edges[i].v;
			T.edges[i].v = temp;
		}
		printf("%d %d %d\n", T.edges[i].u, T.edges[i].v, T.edges[i].w);
	}
	return 0;
}
