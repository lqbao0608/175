int deg(Graph* G, int x) {
    int y, d = 0;
	for(y = 1; y <= G->n; y++) {
		if(G->A[x][y] != 0) {
			d++;
		}
	}
	return d;
}
