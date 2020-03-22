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
}

int pi[MAX_N][MAX_N];
int next[MAX_N][MAX_N];

void Floy_Warshall(Graph *G) {
	int i, j, k;
	for(i = 1; i <= G->n; i++) {
		for(j = 1; j <= G->n; j++) {
			if(G->L[i][j] != 0) {
				pi[i][j] = G->L[i][j];
				next[i][j] = j;
			}
			else {
				pi[i][j] = 9999;
				next[i][j] = -1;
			}
		}
	}
	for(i = 1; i <= G->n; i++) {
		pi[i][i] = 0;
	}
	for(k = 1; k <= G->n; k++) {
		for(i = 1; i <= G->n; i++) {
			for(j = 1;j <= G->n; j++) {
				if(pi[i][k] != 9999 && pi[k][j] != 9999) {
					if(pi[i][k] + pi[k][j] < pi[i][j]) {
						pi[i][j] = pi[i][k] + pi[k][j];
						next[i][j] = next[i][k];
					}
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
	Floy_Warshall(&G);
	int i, j;
	for(i = 1; i <= G.n; i++) {
		for(j = 1; j <= G.n; j++) {
			printf("%d -> %d: ", i, j);
			if(pi[i][j] != 9999) {
				printf("%d\n", pi[i][j]);
			}
			else {
				printf("oo\n");
			}
		}
	}
	return 0;
}
