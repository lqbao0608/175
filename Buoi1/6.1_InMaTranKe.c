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

int main() {
	freopen("dt1.txt", "r", stdin);
	Graph G;
	int n, m, e, u, v;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 1; e <= m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int i, j;
	for(i = 1; i <= G.n; i++) {
		for(j = 1; j <= G.n; j++) {
			if(G.A[i][j] != 0) {
				printf("1 ");
			}
			else {
				printf("0 ");
			}
		}
		printf("\n");
	}
	return 0;
}
