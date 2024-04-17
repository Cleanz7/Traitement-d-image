#ifndef moment_h
#define moment_h

#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "point.h"

/**
* @fn extern void give_moments(image img, int i, int n, int m, int* zero, double* un, double* deux);
* @brief Cette fonction calcule les moments d'ordre zero, un et deux du block i.
* @file moment.c
* @date 2022-01-06
*
* @param img l'image a traiter.
* @param i indice du block.
* @param n nombre de block par ligne.
* @param m nombre de block par colonne.
* @param zero un pointeur qui pointe vers le moment d'ordre zero.
* @param un un pointeur qui pointe vers un tableau de double : le moment d'ordre un.
* @param deux un pointeur qui pointe vers un tableau de double :le moment d'ordre deux.
*/
extern void give_moments(image img, int i, int n, int m, int* zero, double* un, double* deux);

#endif