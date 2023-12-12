/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include "utils.h"

const int similarity_matrix[NB_BASE][NB_BASE] = {{10, -1, -3, -4, -5},
                                                 {-1, 7, -5, -3, -5},
                                                 {-3, -5, 9, 0, -5},
                                                 {-4, -3, 0, 8, -5},
                                                 {-5, -5, -5, -5, 0}};

/*----------------------------------------------------------------------------------
Fonctions permettant de calculer le score d'alignement entre 2 chaînes de caracteres
------------------------------------------------------------------------------------*/

/*
Input : Un caractere
Output : Un entier
Main : Fonction qui prend un caractere et retourne l'index correspondant (voir l'enum Base_Azotee)
*/
int get_val_base(char a)
{
    switch (a)
    {
    case 'A':
        return A;
    case 'C':
        return C;
    case 'G':
        return G;
    case 'T':
        return T;
    case '-':
        return E;
    default:
        return -1;
    }
}

/*
Input : Deux caracteres
Output : Un entier
Main : Fonction qui prend en entier 2 caracteres et qui retourne
       le score entre les 2 caracteres suivant la matrice de similarite
*/
int similarity_score(char ch1, char ch2)
{
    return similarity_matrix[get_val_base(ch1)][get_val_base(ch2)];
}

/*
Input : Deux chaînes de caracteres s
Output : Un entier
Main : Fonction qui prend en entier 2 chaînes de caracteres et qui retourne
       le score d'alignement entre les deux chaînes
*/
int score_alignement(char *alignement1, char *alignement2)
{
    int score = 0;
    for (int i = 0; i < strlen(alignement1); i++)
    {
        score += similarity_score(alignement1[i], alignement2[i]);
    }
    return score;
}

/*
Input : Deux chaînes de caracteres et un score
Output : None
Main : Procedure qui prend en entier 2 chaînes de caracteres et un score
       Et qui fait un bel affichage montrant l'alignement et le score
*/
void print_quality_alignement(char *ali1, char *ali2, int score)
{
    printf("The alignment score : %d\n", score);
    printf("\tAlignement 1 : %s\n", ali1);
    printf("\tAlignement 2 : %s\n\n", ali2);
}

/*----------------------------
Algorithme de Needleman-Wunsch
------------------------------*/

/*
Input : 2 entiers et une matrice
Output : None
Main : Procedure qui Initialise la matrice M
*/
void initialise_M(int n, int m, int M[][m])
{
    // TODO
}

/*
Input : 2 entiers et une matrice
Output : None
Main : Procedure qui Initialise la matrice T
*/
void initialise_T(int n, int m, char T[][m])
{
    // TODO
}

/*
Input : un entier
Output : un caractere
Main : Fonction qui retourne le caractere correspondant au maximum index de la formule Mij
*/
char symbole(int entier)
{
    if (entier == 0)
    {
        return 'd';
    }
    else if (entier == 1)
    {
        return 'l';
    }
    return 'u';
}

/*
Input : une chaîne de caracteres
Output : None
Main : Procedure qui inverse une chaîne de caracteres
*/
void reverse_string(char *str)
{
    // TODO
}

/*
Input : - 2 Sequences
        - 2 index
        - 2 tailles
        - une matrice de taille n*m
        - Deux pointeurs sur des entiers
Output : None
Main : Procedure qui applique la formule Mij et qui sauvegarde
       la plus grande valeur dans le premier pointeur et l'index
       correspondant (0, 1 ou 2) dans le deuxieme.
*/
void fonction_Mij(Sequence *s1, Sequence *s2, int i, int j, int n, int m, int M[][m], int *max, int *index)
{
    // TODO
}

/*
Input : - 2 Sequences
        - Deux chaînes de caracteres
Output : None
Main : Procedure qui applique l'algorithme Needleman-Wunsch
       sur les 2 sequences et qui sauvegarde les alignements
       dans les 2 pointeurs
*/
void needleman_wunsch(Sequence seq1, Sequence seq2, char *alignement1, char *alignement2)
{
    // TODO
}
