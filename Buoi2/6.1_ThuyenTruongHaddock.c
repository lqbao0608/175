#include <stdio.h>

#define MAX_ELEMENTS 100
#define MAX_N 100
#define WHITE 0
#define GRAY 1
#define BLACK 2

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

int color[MAX_N];
int cycle;

void visit(Graph *G, int u) {
	color[u] = GRAY;
	List L = neighbors(G, u);
	int i;
	for(i = 1; i <= size(&L); i++) {
		int v = element_at(&L, i);
		if(color[v] == WHITE) {
			visit(G, v);
		}
		else if(color[v] == GRAY) {
			cycle = 1;
			return;
		}
	}
	color[u] = BLACK;
}

int contains_cycle(Graph *G) {
	int i;
	for(i = 1; i <= G->n; i++) {
		color[i] = WHITE;
	}
	cycle = 0;
	for(i = 1; i <= G->n; i++) {
		if(color[i] == WHITE) {
			visit(G, i);
		}
	}
	return cycle;
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
	if(contains_cycle(&G) == 0) {
		printf("YES");
	}
	else {
		printf("NO");
	}
	return 0;
}
