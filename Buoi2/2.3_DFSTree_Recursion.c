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

int size(List *L) {
	return L->size;
}

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

List neighbors(Graph *G, int x) {
	List L;
	make_null_list(&L);
	int y;
	for(y = 1; y <= G->n; y++) {
		if(y != x && G->A[x][y] != 0) {
			push_back(&L, y);
		}
	}
	return L;
}

int mark[MAX_N];
int parent[MAX_N];

void visit(Graph *G, int u, int p) {
	if(mark[u] == 1) return;
	mark[u] = 1;
	parent[u] = p;
	List L = neighbors(G, u);
	int i;
	for(i = 1; i <= size(&L); i++) {
		int v = element_at(&L, i);
		visit(G, v, u);
	}
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
	int i;
	for(i = 1; i <= G.n; i++) {
		mark[i] = 0;
		parent[i] = -1;
	}

	for(i = 1; i <= G.n; i++) {
		if(mark[i] == 0) {
			visit(&G, i, 0);
		}
	}
	for(i = 1; i <= G.n; i++) {	
		printf("%d %d\n", i, parent[i]);
	}
	return 0;
}
