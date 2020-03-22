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
	int size;
} Stack;

void make_null_stack(Stack *S) {
	S->size = 0;
}

void push(Stack *S, int x) {
	S->data[S->size] = x;
	S->size++;
}

int top(Stack *S) {
	return S->data[(S->size)-1];
}

void pop(Stack *S) {
	S->size--;
}

int empty_stack(Stack *S) {
	return S->size == 0;
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

Stack S;
int num[MAX_N];
int min_num[MAX_N];
int on_stack[MAX_N];
int idx;
int count;

int min(int x, int y){
	if(x < y) return x;
	else return y;
}

void strong_connect(Graph *G, int x) {
	num[x] = min_num[x] = idx;
	idx++;
	push(&S, x); on_stack[x]= 1;
	List L = neighbors(G, x);
	int i;
	for(i = 1; i <= size(&L); i++) {
		int y = element_at(&L, i);
		if(num[y] == -1) {
			strong_connect(G, y);
			min_num[x] = min(min_num[x], min_num[y]);
		}
		else if(on_stack[y] == 1) {
			min_num[x] = min(min_num[x], num[y]);
		}
	}
	if(num[x] == min_num[x]) {
		int w;
		do {
			w = top(&S);
			pop(&S);
			on_stack[w] = 0;
		} while(w != x);
		count++;
	}
}
int main() {
	Graph G;
	int n, m, e, u, v, p;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 1; e <= m; e++) {
		scanf("%d%d%d", &u, &v, &p);
		if(p == 1) {
			add_edge(&G, u, v);
		}
		else if(p == 2) {
			add_edge(&G, u, v);
			add_edge(&G, v, u);
		}
	}
	int i;
	for(i = 1; i <= G.n; i++) {
		num[i] = -1;
		on_stack[i] = 0;
	}
	idx = 1;
	count = 0;
	for(i = 1; i <= G.n; i++) {
		if(num[i] == -1) {
			strong_connect(&G, i);
		}
	}
	if(count == 1) {
		printf("OKIE");
	}
	else {
		printf("NO");
	}
	return 0;
}
