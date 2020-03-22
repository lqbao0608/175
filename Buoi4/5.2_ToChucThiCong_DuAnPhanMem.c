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
	int data[MAX_ELEMENTS];
	int front;
	int rear;
} Queue;

void make_null_queue(Queue *Q) {
	Q->front = 0;
	Q->rear = -1;
}

void en_queue(Queue *Q, int x) {
	Q->rear++;
	Q->data[Q->rear] = x;
}

int front(Queue *Q) {
	return Q->data[Q->front];
}

void de_queue(Queue *Q) {
	Q->front++;
}

int empty_queue(Queue *Q) {
	return Q->front > Q->rear;
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

List topo_sort(Graph *G) {
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
	Queue Q;
	make_null_queue(&Q);
	for(i = 1; i <= G->n; i++) {
		if(d[i] == 0) {
			en_queue(&Q, i);
		}
	}
	List L;
	make_null_list(&L);
	while(empty_queue(&Q) == 0) {
		int u = front(&Q);
		de_queue(&Q);
		push_back(&L, u);
		int v;
		for(v = 1; v <= G->n; v++) {
			if(G->A[u][v] != 0) {
				d[v]--;
				if(d[v] == 0) {
					en_queue(&Q, v);
				}
			}
		}
	}
	return L;
}

int min(int x, int y) {
	if(x < y) return x;
	return y;
}

int max(int x, int y) {
	if(x > y) return x;
	return y;
}

int main() {
	Graph G;
	int n, i, u, v;
	scanf("%d", &n);
	init_graph(&G, n+2);
	int d[MAX_N];
	for(v = 1; v <= n; v++) {
		scanf("%d", &d[v]);
		do {
			scanf("%d", &u);
			add_edge(&G, u, v);
		} while(u != 0);
	}
	d[n+1] = d[n+2] = 0;
	for(v = 1; v <= n; v++) {
		int deg_neg = 0;
		for(u = 1; u <= n; u++) {
			if(G.A[u][v] != 0) {
				deg_neg++;
			}
		}
		if(deg_neg == 0) {
			add_edge(&G, n+1, v);
		}
	}
	for(u = 1; u <= n; u++) {
		int deg_pos = 0;
		for(v = 1; v <= n; v++) {
			if(G.A[u][v] != 0) {
				deg_pos++;
			}
		}
		if(deg_pos == 0) {
			add_edge(&G, u, n+2);
		}
	}
	List L = topo_sort(&G);
	int t[MAX_N], T[MAX_N];
	for(i = 1; i <= n+2; i++) {
		t[i] = -9999;
		T[i] = 9999;
	}
	t[n+1] = 0;
	for(i = 1; i <= size(&L); i++) {
		int v = element_at(&L, i);
		for(u = 1; u <= G.n; u++) {
			if(G.A[u][v] != 0) {
				t[v] = max(t[v], t[u] + d[u]);
			}
		}
	}
	T[n+2] = t[n+2];
	for(i = size(&L)-1; i >= 1; i--) {
		int u = element_at(&L, i);
		for(v = 1; v <= G.n; v++) {
			if(G.A[u][v] != 0) {
				T[u] = min(T[u], T[v] - d[u]);
			}
		}
	}
	for(i = 1; i <= n+2; i++) {
		if(t[i] == T[i]) {
			printf("%d\n", i);
		}
	}
	return 0;
}
