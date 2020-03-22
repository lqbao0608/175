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

int empty_list(List *L) {
	return L->size == 0;
}

void copy_list(List *src, List *dest) {
	make_null_list(dest);
	int i;
	for(i = 0; i <= (src->size)-1; i++) {
		push_back(dest, src->data[i]);
	}
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

int rank[MAX_N];

void ranking(Graph *G) {
	int d[MAX_N];
	int i, j;
	for(i = 1; i <= G->n; i++) {
		d[i] = 0;
	}
	for(i = 1; i <= G->n; i++) {
		for(j = 1; j <= G->n; j++) {
			if(G->A[i][j] != 0) {
				d[j]++;
			}
		}
	}
	List L1;
	make_null_list(&L1);
	for(i = 1; i <= G->n; i++) {
		if(d[i] == 0) {
			push_back(&L1, i);
		}
	}
	int k = 0;
	while(empty_list(&L1) == 0) {
		List L2;
		make_null_list(&L2);
		for(i = 1; i <= size(&L1); i++) {
			int u = element_at(&L1, i);
			rank[u] = k;
			int v;
			for(v = 1; v <= G->n; v++) {
				if(G->A[u][v] != 0) {
					d[v]--;
					if(d[v] == 0) {
						push_back(&L2, v);
					}
				}
			}
		}
		copy_list(&L2, &L1);
		k++;
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
	ranking(&G);
	int i;
	for(i = 1; i <= G.n; i++) {
		printf("%d\n", rank[i]);
	}
	return 0;
}
