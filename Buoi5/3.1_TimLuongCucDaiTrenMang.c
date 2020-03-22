#include <stdio.h>

#define MAX_ELEMENTS 100
#define MAX_N 100

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
	int C[MAX_N][MAX_N];
	int F[MAX_N][MAX_N];
	int n;
	int m;
} Graph;

void init_graph(Graph *G, int n) {
	int i, j;
	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			G->C[i][j] = 0;
		}
	}
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G, int u, int v, int c) {
	G->m++;
	G->C[u][v] = c;
}

typedef struct {
	int dir;
	int pre;
	int sigma;
} Label;

Label labels[MAX_N];

void init_flow(Graph *G) {
	int i, j;
	for(i = 1; i <= G->n; i++) {
		for(j = 1; j <= G->n; j++) {
			G->F[i][j] = 0;
		}
	}
}

int min(int a, int b) {
	if(a < b) return a;
	else return b;
}

int FordFullkerson(Graph *G, int s, int t) {
	init_flow(G);
	Queue Q;
	int sum_flow = 0;
	do {
		int i;
		for(i = 1; i <= G->n; i++) {
			labels[i].dir = 0;
		}
		labels[s].dir = 1;
		labels[s].pre = s;
		labels[s].sigma = 9999;
		make_null_queue(&Q);
		en_queue(&Q, s);
		int found = 0;
		while(empty_queue(&Q) == 0) {
			int u = front(&Q);
			de_queue(&Q);
			int v;
			for(v = 1; v <= G->n; v++) {
				if(labels[v].dir == 0 && G->C[u][v] != 9999 && G->F[u][v] < G->C[u][v]) {
					labels[v].dir = +1;
					labels[v].pre = u;
					labels[v].sigma = min(labels[u].sigma, G->C[u][v] - G->F[u][v]);
					en_queue(&Q, v);
				}
				if(labels[v].dir == 0 && G->C[u][v] != 9999 && G->F[v][u] > 0){
					labels[v].dir = -1;
					labels[v].pre = u;
					labels[v].sigma = min(labels[u].sigma,G->F[v][u]);
					en_queue(&Q, v);
				}
			}
			if(labels[t].dir != 0) {
				found = 1;
				break;
			}
		}
		if(found == 1) {
			int v = t;
			int sigma = labels[t].sigma;
			sum_flow += sigma;
			while(v != s) {
				int u = labels[v].pre;
				if(labels[v].dir > 0) {
					G->F[u][v] = G->F[u][v] + sigma;
				}
				else {
					G->F[v][u] = G->F[v][u] - sigma;
				}
				v = u;
			}
		}
		else break;
	} while(1);
	return sum_flow;
}

int main() {
	Graph G;
	int n, m, e, u, v, c;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 1; e <= m; e++) {
		scanf("%d%d%d", &u, &v, &c);
		add_edge(&G, u, v, c);
	}
	int max_flow = FordFullkerson(&G, 1, n);
	printf("Max flow: %d", max_flow);
	printf("\nX0: ");
	int i;
	for(i = 1; i <= G.n; i++) {
		if(labels[i].dir != 0) {
			printf("%d ", i);
		}
	}
	printf("\nY0: ");
	for(i = 1; i <= G.n; i++) {
		if(labels[i].dir == 0) {
			printf("%d ", i);
		}
	}
	return 0;
}
