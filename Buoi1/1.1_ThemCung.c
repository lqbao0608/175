void add_edge(Graph *G, int e, int x, int y) {
	G->A[x][e] = 1;
	G->A[y][e] = 1;
}
