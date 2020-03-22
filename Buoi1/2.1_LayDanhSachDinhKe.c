List neighbors(Graph *G, int x) {
    List L;
    make_null(&L);
    int e, y;
    for(y = 1; y <= G->n; y++) {
    	if(x != y) {
    		for(e = 1; e <= G->m; e++) {
	        	if(G->A[x][e] != 0 && G->A[y][e] != 0) {
	                push_back(&L, y);
	                break;
	            }
			}
    	}
    }
    return L;
}
