#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "RAG.h"


/*structure pour les moments d'ordre 1 , 2 et 3*/
struct moments{
	int M0;
	double M1[3];
	double M2[3];
};
typedef struct cellule* cellule;

/*structure pour les voisins d'un block*/
struct cellule{
	int block;
	cellule next;
};

typedef struct moments* moments;
/*structure pour manipuler l'image*/
struct RAG{
	image img;
	int nb_blocks;
	long double erreur_partition;
	moments m;
	int * father;
	cellule *neighbors;
};
typedef struct RAG * rag;

/*fonction pour creer un RAG*/
extern rag create_RAG(image img, int n,int m){
    rag adj = malloc(sizeof(struct RAG));
    adj->img = img;
    adj->nb_blocks = n*m;
    init_moments_priv(adj, n, m);
    init_father_priv(adj);
    init_neighbors_priv(adj, n, m);
    init_partition_error_priv(adj);
    return adj;
}

/*initialiser les moments des blocks de l'image*/
static void init_moments_priv(rag adj, int n, int m){
    int i;
    adj->m = malloc(adj->nb_blocks * sizeof(struct moments));
    for (i=0;i<adj->nb_blocks;i++){
        /*on calcule les moments a l'aide de cette fonction presente dans moment.c*/
        give_moments(adj->img, i, n, m, &(adj->m[i].M0), &(adj->m[i].M1), &(adj->m[i].M2));
    }
}

/*initialiser le pere de chaque block*/
static void init_father_priv(rag adj){
    int i;
    adj->father = malloc(adj->nb_blocks * sizeof(int));
    for (i=0;i<adj->nb_blocks;i++){
        /*le pere est initialiser a lui meme*/
        adj->father[i] = i;    
    }
    
}
/*initialiser les voisins de chaque block*/
static void init_neighbors_priv(rag adj, int n, int m){
    adj->neighbors = malloc(adj->nb_blocks * sizeof(struct cellule));
    int i;
    int j;
    for (i=0; i<adj->nb_blocks; i++){
        adj->neighbors[i] = NULL;
    }
    /*on parcourt tout les blocks*/
    for (j=0;j<adj->nb_blocks;j++){  
        if (j+n < n*m ){
            /*voisin du bas*/
            cellule c = malloc(sizeof(struct cellule));
            c->block = j+n;
            c->next = adj->neighbors[j];
            adj->neighbors[j] = c;
        }

        if ((j+1) % m != 0){
            /*voisin de droite*/
            cellule c = malloc(sizeof(struct cellule));
            c->block = j+1;
            c->next = adj->neighbors[j];
            adj->neighbors[j] = c;
        }    
    }
}

/*initialiser l'erreur quadratique des blocks*/
static void init_partition_error_priv(rag adj){
    int i;
    int dim = image_give_dim(adj->img);
    adj->erreur_partition = 0;
    for (i=0;i<adj->nb_blocks;i++){
        /*on calcule l'erreur a partir de la formule qui se trouve dans la page 4 de l'enonce*/
        if (dim == 1){
            adj->erreur_partition = adj->erreur_partition + (adj->m[i].M2)[0] - ((adj->m[i].M1)[0] * (adj->m[i].M1)[0])/(adj->m[i].M0);
        }else{
            adj->erreur_partition = adj->erreur_partition + (adj->m[i].M2)[0] - ((adj->m[i].M1)[0] * (adj->m[i].M1)[0])/(adj->m[i].M0);
            adj->erreur_partition = adj->erreur_partition + (adj->m[i].M2)[1] - ((adj->m[i].M1)[1] * (adj->m[i].M1)[1])/(adj->m[i].M0);
            adj->erreur_partition = adj->erreur_partition + (adj->m[i].M2)[2] - ((adj->m[i].M1)[2] * (adj->m[i].M1)[2])/(adj->m[i].M0);
        }
    
    }

}
/*renvoie la valeur de l'augmentation d'erreur quadratique*/
extern double RAG_give_closest_region(rag adj,int* i, int* j){
    long double temp_calc = 0;
    int k;
    int dim = image_give_dim(adj->img);
    /*moment d'ordre 0 du block B*/
    double M0_B = adj->m[0].M0;
    /*moment d'ordre 0 du block B_prime*/
    double M0_Bp = adj->m[1].M0;
    long double norme;
    /*la couleur moyenne du block B*/
    double mu_B[3];
    /*la couleur moyenne du block B_prime*/
    double mu_Bp[3];
    /*on utilise la formule dans l'enonce pour calculer le min*/
    long double min = -1;
    for(k=0;k<adj->nb_blocks;k++){
        /*Modification pour eviter un probleme de voisins (question 6.2)*/
        (adj->neighbors[k]) = (adj->neighbors[adj->father[k]]);
        
        if(adj->father[k] == k){
            /*le nombre de voisins d'un block*/
            cellule c = adj->neighbors[k];

            while (c != NULL){
                if (adj->father[adj->father[c->block]]==adj->father[c->block]) { 
                    if (k != adj->father[c->block]){
                        M0_B = adj->m[k].M0;
                        M0_Bp = adj->m[adj->father[c->block]].M0;
                        if (dim == 1){
                            mu_B[0]= ((adj->m[k].M1)[0])/M0_B;
                            mu_Bp[0]= ((adj->m[adj->father[c->block]].M1)[0])/M0_Bp;

                            norme = (mu_B[0] - mu_Bp[0])*(mu_B[0] - mu_Bp[0]);
                        }else{
                            mu_B[0]= ((adj->m[k].M1)[0])/M0_B;
                            mu_B[1]= ((adj->m[k].M1)[1])/M0_B;
                            mu_B[2]= ((adj->m[k].M1)[2])/M0_B;
                            
                            mu_Bp[0] = ((adj->m[adj->father[c->block]].M1)[0])/M0_Bp;
                            mu_Bp[1] = ((adj->m[adj->father[c->block]].M1)[1])/M0_Bp;
                            mu_Bp[2] = ((adj->m[adj->father[c->block]].M1)[2])/M0_Bp;

                            norme = (mu_B[0] - mu_Bp[0])*(mu_B[0] - mu_Bp[0]) + (mu_B[1] - mu_Bp[1])*(mu_B[1] - mu_Bp[1]) + (mu_B[2] - mu_Bp[2])*(mu_B[2] - mu_Bp[2]);
                        }
                        temp_calc = (M0_B * M0_Bp)/(M0_B + M0_Bp) *  norme;

                        /*si l'erreur est inferieur a la valeur minimal on initialise les deux blocks i et j*/
                        if(min == -1 || temp_calc < min){
                            min = temp_calc;
                            *i = k;
                            /*on initialise j par le voisin de droite*/
                            *j = (adj->father[c->block]);
                        }
                    }
                c = c->next;
                }
            }
        }
    }
    return min;    
}

void RAG_merge_region(rag adj,int i,int j){
    int k=0;
    int l;
    int dim = image_give_dim(adj->img);  
    /*moment d'ordre 0 du block B*/
    double M0_B = adj->m[i].M0;
    /*moment d'ordre 0 du block B_prime*/
    double M0_Bp = adj->m[j].M0;
    long double norme;
    double mu_B[3];
    double mu_Bp[3];
    /*Mis a jour de l'erreur de partition*/
    /*la couleur moyenne du block definie par M1/M0 du block B*/
    if (dim == 1){
        mu_B[0]= ((adj->m[i].M1)[0])/M0_B;
        mu_Bp[0]= ((adj->m[j].M1)[0])/M0_Bp;

        norme = (mu_B[0] - mu_Bp[0])*(mu_B[0] - mu_Bp[0]);
    }else{
        
        mu_B[0]= ((adj->m[i].M1)[0])/M0_B;
        mu_B[1]= ((adj->m[i].M1)[1])/M0_B;
        mu_B[2]= ((adj->m[i].M1)[2])/M0_B;
        /*la couleur moyenne du block definie par M1/M0 du block B_prime*/
        
        mu_Bp[0] = ((adj->m[j].M1)[0])/M0_Bp;
        mu_Bp[1] = ((adj->m[j].M1)[1])/M0_Bp;
        mu_Bp[2] = ((adj->m[j].M1)[2])/M0_Bp;

        
        norme = (mu_B[0] - mu_Bp[0])*(mu_B[0] - mu_Bp[0]) + (mu_B[1] - mu_Bp[1])*(mu_B[1] - mu_Bp[1]) + (mu_B[2] - mu_Bp[2])*(mu_B[2] - mu_Bp[2]);
    }
    adj->erreur_partition = (M0_B * M0_Bp)/(M0_B + M0_Bp) *  norme;

    /*Mis a jour des moments*/
    adj->m[j].M0 = adj->m[j].M0 + adj->m[i].M0;
    if (dim == 1){
        (adj->m[j].M1)[0] = (adj->m[j].M1)[0] + (adj->m[i].M1)[0];
        (adj->m[j].M2)[0] = (adj->m[j].M2)[0] + (adj->m[i].M2)[0];
    }else{   
        for(k=0; k<3; k++){
            (adj->m[j].M1)[k] = (adj->m[j].M1)[k] + (adj->m[i].M1)[k];
            (adj->m[j].M2)[k] = (adj->m[j].M2)[k] + (adj->m[i].M2)[k];
        }
    }
    
    adj->father[i] = j;
    /*Mis a jour des voisins*/
    cellule c = adj->neighbors[i];
    while (c != NULL){
        if((c->block != j)){
            cellule c_temp = malloc(sizeof(struct cellule));
            c_temp->block = c->block;
            c_temp->next = adj->neighbors[j];
            adj->neighbors[j] = c_temp; 
        }
        c = c->next;
    }
    adj->neighbors[i] = NULL;
}

extern void RAG_normalize_parents(rag adj){
    int i;
    for (i=0; i<adj->nb_blocks; i++){
        adj->father[i] = adj->father[adj->father[i]];
    }
}

/*cette fonction calcule la couleur moyenne du pere du block i*/
extern void RAG_give_mean_color(rag adj, int i, int* mean_color){
    int dim = image_give_dim(adj->img);

    if (dim == 1){
        mean_color[0] = adj->m[adj->father[i]].M1[0] / adj->m[adj->father[i]].M0;
    }else{
        mean_color[0] = adj->m[adj->father[i]].M1[0] / adj->m[adj->father[i]].M0;
        mean_color[1] = adj->m[adj->father[i]].M1[1] / adj->m[adj->father[i]].M0;
        mean_color[2] = adj->m[adj->father[i]].M1[2] / adj->m[adj->father[i]].M0;
    }
    
   
}


image create_output_image(rag adj, int n, int m){
    int i;
    int j;
    int k;
    image img = adj->img;
    image img_out;/*l'image de sortie*/
    int dim = image_give_dim(img);
    int L = image_give_largeur(img);
    int H = image_give_hauteur(img);
    int mean_color[3];
    unsigned char mean_tab[3]; 
    int n_block;

    img_out = FAIRE_image();/*creer une image vide*/
    image_initialize(img_out, dim, L, H);/*initialiser les parametres de l'image*/
    for (i=0; i<H; i++){
        for (j=0; j<L; j++){
            n_block = j/(L/n) + (i/(H/m))*n;/*calcule du numero du block*/
                
            RAG_give_mean_color(adj, n_block, mean_color);
            if (dim == 1){
                mean_tab[0] = (unsigned char)mean_color[0];/*caster le tableau en unsigned char pour l'utiliser dans la fonction image_write_pixel*/
            }else{
                for (k=0; k<3; k++){
                    mean_tab[k] = (unsigned char)mean_color[k];
                }
            }
            image_write_pixel(img_out, i, j, mean_tab);
                
                
        }
    }
    
    return img_out;
}

extern long double get_erreur_partition(rag adj){
    return adj->erreur_partition;
}
/*liberation des allocations dynamiques*/
extern void free_all(rag adj){
    free(adj->m);
    free(adj->father);
    free(adj->neighbors);
    free(adj);
}