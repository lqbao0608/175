#include <stdio.h>

#define MAX_N 100

typedef struct {
	int L[MAX_N][MAX_N];
	int n;
	int m;
} Graph;

void init_graph(Graph *G, int n) {
	int i, j;
	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			G->L[i][j] = 0;
		}
	}
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G, int u, int v, int w) {
	G->m++;
	G->L[u][v] = w;
	G->L[v][u] = w;
}

int mark[MAX_N];
int pi[MAX_N];
int p[MAX_N];

void Dijkstra(Graph *G, int s) {
	int i;
	for(i = 1; i <= G->n; i++) {
		mark[i] = 0;
		pi[i] = 9999;
		p[i] = -1;
	}
	pi[s] = 0;
	p[s] = -1;
	int it, u, v;
	for(it = 1; it <= G->n; it++) {
		int min_pi = 9999;
		for(i = 1; i <= G->n; i++) {
			if(mark[i] == 0 && pi[i] < min_pi) {
				min_pi = pi[i];
				u = i;
			}
		}
		mark[u] = 1;
		for(v = 1; v <= G->n; v++) {
			if(mark[v] == 0 && G->L[u][v] != 0) {
				if(pi[u] + G->L[u][v] < pi[v]) {
					pi[v] = pi[u] + G->L[u][v];
					p[v] = u;
				}
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
	int s, t;
	scanf("%d%d", &s, &t);
	Dijkstra(&G, s);
	printf("%d", pi[t]);
	return 0;
}
