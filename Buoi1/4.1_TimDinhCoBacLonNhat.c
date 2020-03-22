#include <stdio.h>

#define MAX_N 100

typedef struct {
	int A[MAX_N][MAX_N];
	int n;
	int m;
} Graph;

void init_graph(Graph *G, int n) {
	int i, j;
	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			G->A[i][j] = 0;
		}
	}
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G, int x, int y) {
	G->m++;
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

int degree(Graph *G, int x) {
	int y, deg = 0;
	for(y = 1; y <= G->n; y++) {
		if(G->A[x][y] != 0) {
			deg++;
		}
	}
	return deg;
}

int main() {
	Graph G;
	int n, m, e, u, v;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 1; e <= m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int max = degree(&G, 1);
	int i = 1;
	int x;
	for(x = 2; x <= G.n; x++) {
		if(degree(&G, x) > max) {
			max = degree(&G, x);
			i = x;
		}
	}
	printf("%d %d", i, degree(&G, i));
	return 0;
}
