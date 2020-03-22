#include <stdio.h>

#define MAX_ELEMENTS 100
#define MAX_N 100

typedef struct {
	int data[MAX_ELEMENTS];
	int size;
} List;

void make_null_list(List *L) {
	L->size = 0;
}

void push_back(List *L, int x) {
	L->data[L->size] = x;
	L->size++;
}

int element_at(List *L, int p) {
	return L->data[p-1];
}

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

int distance_from(Graph *G, List *L, int u) {
	int min_dist = 9999;
	int min_v = -1;
	int i;
	for(i = 1; i <= L->size; i++) {
		int v = element_at(L, i);
		if(G->L[u][v] != 0 && G->L[u][v] < min_dist) {
			min_dist = G->L[u][v];
			min_v = v;
		}
	}
	return min_v;
}

int mark[MAX_N];

int Prim(Graph *G, Graph *T) {
	List L;
	make_null_list(&L);
	int i;
	for(i = 1; i <= G-> n; i++) {
		mark[i] = 0;
	}
	push_back(&L, 1);
	mark[1] = 1;
	init_graph(T, G->n);
	int sum_w = 0;
	for(i = 1; i <= (G->n)-1; i++) {
		int min_dist = 9999;
		int u, v, min_u, min_v;
		for(u = 1; u <= G->n; u++) {
			if(mark[u] == 0) {
				v = distance_from(G, &L, u);
				if(v != -1 && G->L[u][v] < min_dist) {
					min_dist = G->L[u][v];
					min_u = u;
					min_v = v;
				}
			}
		}
		push_back(&L, min_u);
		mark[min_u] = 1;
		add_edge(T, min_u, min_v, min_dist);
		sum_w += min_dist;
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
	int sum_w = Prim(&G, &T);
	printf("%d\n", sum_w);
	for(u = 1; u <= T.n; u++) {
		for(v = 1; v <= T.n; v++) {
			if(T.L[u][v] != 0 && T.L[v][u] != 0 && u < v) {
				printf("%d %d %d\n", u, v, T.L[u][v]);
			}
		}
	}
	return 0;
}
