#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define NULL ((void *)0)

typedef struct Noeud {
    char* valeur;
    struct Noeud* suivant_left;
    struct Noeud* suivant_right;
    int nb_noeud;
}Noeud;

typedef struct Arbre {
    Noeud* HEAD;
}Arbre;

/*
Input : Un Noeud
Output : Entier
Main : Fonction qui retourne 1 si un noeud est une feuille, 0 sinon
*/
int est_feuille(Noeud* e) {
    if (e->suivant_left == NULL && e->suivant_right == NULL) {
        return 1;
    }
    return 0;
}

/*
Input : pointeur sur un noeud
Output : None
Main : procedure qui affiche le noeud (d'une maniere plate)
*/
void afficher_elem_plat(Noeud* e) {
    if (e == NULL) return;

    if (est_feuille(e)) printf("%s", e->valeur);
    else {
        printf("(");
        afficher_elem_plat(e->suivant_left);
        printf(", ");
        afficher_elem_plat(e->suivant_right);
        printf(")");
    }
}

/*
Input : pointeur sur un arbre
Output : None
Main : procedure qui affiche un arbre 
*/
void new_affichage(Noeud* a,int* step, char mark){
    //TODO
    static int root = 0;
    static int evtime = 0;
    if (a == NULL){
        return;
    }

    if (est_feuille(a))
    {
        if (*step > evtime)
        {
            evtime = *step;
        }
        
        //Branche Feuille
        for (int i = 1; i <= evtime; i++){
            if (i == (evtime)){
                printf("----| %d%s\n",*step,a->valeur);
            }
            else {
                /*if (i == 1)
                {
                    printf("\n");
                }*/
                if (*step != evtime && i >= *step){
                    printf("-----");
                }
                else {
                    printf("     ");
                }
            }
        }
        //printf("----|");
        //printf("%d",*step);
        //printf(" %s",a->valeur);
        //printf("\n");
        //Branche +1
        if(mark == 'l'){
            if ((*step-1) != 1){
                for (int i = 1; i < *step; i++){
                    if (i == (*step-1)){
                        printf("----|\n");
                    }
                    else {
                        printf("     ");
                    }
                }
            }
        }
        else {
            if (root == 0){
                for (int i = 1; i < (*step-1); i++){
                    if (i == (*step-(*step-1))){
                        printf("----|\n");
                        if (*step-2 == 1){
                            root = 1;
                        }
                    }
                    else {
                        printf("     ");
                    }
                }
            }
        }
        *step -= 1;
    }
    else {
        /*if (a->nb_noeud > 1){
            printf("     ");
        }
        else {
            printf("----|");
        }*/
        //printf("     ");
        *step += 1;
        mark = 'l';
        new_affichage(a->suivant_left,step,mark);
        //Apres une feuille forcément un noeud
        *step += 1;
        mark = 'r';
        new_affichage(a->suivant_right,step,mark);
        *step = 0;

    }
}

int main(void){

    int step = 1;
    char mark = 'l';

    //Arbre

    Noeud A = {.valeur = "A",.nb_noeud = 1};
    Noeud B = {.valeur = "B",.nb_noeud = 1};
    Noeud C = {.valeur = "C",.nb_noeud = 1};
    Noeud D = {.valeur = "D",.nb_noeud = 1};
    Noeud E = {.valeur = "E",.nb_noeud = 1};
    Noeud T3r = {.suivant_left = &D,.suivant_right = &E,.nb_noeud = 2};
    Noeud T2l = {.suivant_left = &A,.suivant_right = &B,.nb_noeud = 1};
    Noeud T2r = {.suivant_left = &C,.suivant_right = &T3r,.nb_noeud = 1};
    Noeud T1 = {.suivant_left = &T2l,.suivant_right = &T2r,.nb_noeud = 8};

    Arbre tree = {.HEAD = &T1};
    
    new_affichage(tree.HEAD,&step,mark);
    
}