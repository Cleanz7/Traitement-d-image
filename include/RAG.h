#ifndef RAG_h
#define RAG_h

#include <stdio.h>
#include <stdlib.h>


typedef struct RAG * rag;

/**
* @fn extern rag create_RAG(image img, int n,int m);
* @brief Cette fonction permet de creer un RAG a partir d'une image.
* @file RAG.c
* @date 2022-01-07
*
* @param img l'image a partir de laquelle on creer une RAG.
* @param n nombre de blocks par ligne.
* @param m nombre de blocks par collone.
* @return cette fonction return le RAG creer.
*/
extern rag create_RAG(image img, int n,int m);

static void init_moments_priv(rag adj, int n, int m);

static void init_father_priv(rag adj);

static void init_neighbors_priv(rag adj, int n, int m);

static void init_partition_error_priv(rag adj);

/**
* @fn extern double RAG_give_closest_region(rag adj,int* i, int* j);
* @brief Cette fonction renvoie les deux blocks dont la fusion provoque le moindre erreur quadratique.
* @file RAG.c
* @date 2022-01-07
*
* @param adj pointeur vers la structure RAG.
* @param i pointeur du premier block a fusionner.
* @param j pointeur du deuxieme block a fusionner.
* @return la valeur de l'augmentation d'erreur quadratique.
*/
extern double RAG_give_closest_region(rag adj,int* i, int* j);

/**
* @fn void RAG_merge_region(rag adj,int i,int j);
* @brief fusionne les deux regions passees en parametres.
* @file RAG.c
* @date 2022-01-07
*
* @param adj pointeur vers la structure RAG.
* @param i indice du premier block a fusionner.
* @param j indice du deuxieme block a fusionner.
*/
void RAG_merge_region(rag adj,int i,int j);

/**
* @fn extern void RAG_normalize_parents(rag adj);
* @brief remplace le pere de chaque block par le pere du pere du block.
* @file RAG.c
* @date 2022-01-07
*
* @param adj pointeur vers la structure RAG.
*/
extern void RAG_normalize_parents(rag adj);

/**
* @fn extern void RAG_give_mean_color(rag adj, int i, int* mean_color);
* @brief calcule la couleur moyenne du pere du block i.
* @file RAG.c
* @date 2022-01-07
*
* @param adj pointeur vers la structure RAG.
* @param i indice du block dont on veut calculer la couleur moyenne.
* @param mean_color un tableau qui contient la valeur moyenne des 3 couleurs.
*/
extern void RAG_give_mean_color(rag adj, int i, int* mean_color);

/**
* @fn image create_output_image(rag, int , int);
* @brief genere une image ou chaque block est colore avec la couleur moyenne de son block parent.
* @file RAG.c
* @date 2022-01-07
*
* @param adj pointeur vers la structure RAG.
* @param n nombre de blocks par ligne.
* @param mean_color nombre de blocks par collone.
* @return l'image cree.
*/
image create_output_image(rag, int , int);

/**
* @fn extern long double get_erreur_partition();
* @brief renvoie l'erreur de partition de la RAG.
* @file RAG.c
* @date 2022-01-07
*
* @param adj pointeur vers la structure RAG.
* @return l'erreur de partition.
*/
extern long double get_erreur_partition();

/**
* @fn extern void free_all(rag adj);
* @brief effectue des liberations des allocations dynamiques.
* @file RAG.c
* @date 2022-01-07
*
* @param adj pointeur vers la structure RAG.
*/
extern void free_all(rag adj);

#endif