#ifndef merge_h
#define merge_h

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "RAG.h"

/**
* @fn void perform_merge(rag adj, double seuil);
* @brief Cette fonction effectue itterativement des fusions de blocks jusqu'a le depassement du seuil passe en parametre.
* @file merge.c
* @date 2022-01-06
*
* @param adj poiteur vers la structure RAG.
* @param seuil le seuil pour la verification.
*/
void perform_merge(rag adj, double seuil);

#endif
