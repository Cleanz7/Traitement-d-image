#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "RAG.h"

void perform_merge(rag adj, double seuil){
    int i,j;
    long double err;
    err = get_erreur_partition(adj); 
    long double err_init = err;
    double tmp=0;
    while (err < seuil*err_init && tmp != -1){
        /*cherche la meilleur fusion et recalcule l'erreur de partition*/
        err += RAG_give_closest_region(adj, &i, &j);
        tmp = RAG_give_closest_region(adj, &i, &j);
        RAG_merge_region(adj, i, j);/*fusion des deux block*/
        RAG_normalize_parents(adj);
    }
}

