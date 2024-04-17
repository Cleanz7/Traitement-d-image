/*
* ENSICAEN
* 6 Boulevard Marechal Juin
* F-14050 Caen Cedex
*
* This file is owned by ENSICAEN students.
* No portion of this document may be reproduced, copied
* or revised without written permission of the authors.
*/


/**
* @author Clement JANTET <clement.jantet@ecole.ensicaen.fr>
* @author Achraf ABOULAKJAM <achraf.aboulakjam@ecole.ensicaen.fr>
* @version 1.0.4 - 2022-01-05
*
* @todo gerer la liberation de memoire.
* @bug probleme de dimension lorsque l'image n'est pas carre, il faut mettre un nombres de blocks multiple des dimensions de l'image.
* @file main.c
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "RAG.h"
#include "merge.h"

typedef struct RAG * rag;

int main(int argc, char* argv[]){
    image img_out;/*l'image de sortie*/
    image img;
    if (argc != 5){/*tester si le nombre de parametre de l'executable est verifier*/
        printf("Erreur syntaxe : nom_image nb_blocks_ligne nb_blocks_colonne seuil\n");
        exit(EXIT_FAILURE);
    }

    rag adj;

    char* nom_img = argv[1];
    int nb_blocks_ligne = atoi(argv[2]);
    int nb_blocks_colonne = atoi(argv[3]);
    double seuil = atof(argv[4]);

    char * destinationFilename = (char *)malloc(12*sizeof(char));
    strcpy(destinationFilename, "output");
    char *extension;
    extension = strrchr(nom_img, '.');
    strcat(destinationFilename, extension);
    img = FAIRE_image();
    image_charger(img, nom_img);
    /*creation du RAG a partir des parametres*/
    adj = create_RAG(img, nb_blocks_ligne, nb_blocks_colonne);
    /*fusion des blocks*/
    perform_merge(adj, seuil);
    /*creation de l'image de sortie*/
    img_out = create_output_image(adj, nb_blocks_ligne, nb_blocks_colonne);
    /*sauvgarde de l'image de sortie*/
    image_sauvegarder(img_out, destinationFilename);
    free(destinationFilename);
    free_all(adj);
    printf("Conversion effectuee !\n");
    return 0;
}
