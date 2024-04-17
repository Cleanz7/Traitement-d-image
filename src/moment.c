#include <stdio.h>
#include <stdlib.h>

#include "moment.h"
#include "image.h"
#include "point.h"

extern void give_moments(image img, int i, int n, int m, int* zero, double* un, double* deux){
	int k;
	int j;
	struct point p;
	int L = image_give_largeur(img);
	int H = image_give_hauteur(img);
	/*calcule du moment d'ordre 0*/
	*zero = (L/n)*(H/m);
	int coordx = L/n;
	int coordy = H/m;
	p.coordx = (i%n)*coordx;
	p.coordy = (i/n)*coordy;
	image_move_to(img,&p);
	int temp_tab[3];
	int dim = image_give_dim(img);
	if (dim == 1){
		un[0] = 0;
		deux[0] = 0;
	}else{
		/*initialiser le moment d'ordre 1*/
		un[0] = 0;
		un[1] = 0;
		un[2] = 0;
		/*initialiser le moment d'ordre 2*/
		deux[0] = 0;
		deux[1] = 0;
		deux[2] = 0;
	}

	for(k=0;k<coordy;k++){
		for(j=0;j<coordx;j++){
			if (dim == 1){
				un[0] = un[0] + image_lire_pixel(img)[0];
				deux[0] = deux[0] + image_lire_pixel(img)[0]*image_lire_pixel(img)[0];

			}
			else{
				temp_tab[0] = image_lire_pixel(img)[0];
				temp_tab[1] = image_lire_pixel(img)[1];
				temp_tab[2] = image_lire_pixel(img)[2];
				/*calcule du moment d'ordre 1*/
				un[0] = un[0] + temp_tab[0];
				un[1] = un[1] + temp_tab[1];
				un[2] = un[2] + temp_tab[2];

				/*calcule du moment d'ordre 2*/
				deux[0] = deux[0] + temp_tab[0]*temp_tab[0];
				deux[1] = deux[1] + temp_tab[1]*temp_tab[1];
				deux[2] = deux[2] + temp_tab[2]*temp_tab[2];
			}

			image_pixel_droite(img);

		}
		p.coordx = (i%n)*coordx;
		p.coordy = (i/n)*coordy - k;
		image_move_to(img,&p);/*passe au pixel suivant*/
	}

}

