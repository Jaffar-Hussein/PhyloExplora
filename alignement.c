/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include "utils.h"

const int similarity_matrix[NB_BASE][NB_BASE] = {{10, -1, -3, -4, -5},
                                                 {-1,  7, -5, -3, -5},
                                                 {-3, -5,  9,  0, -5},
                                                 {-4, -3,  0,  8, -5},
                                                 {-5, -5, -5, -5,  0}};


/*----------------------------------------------------------------------------------
Fonctions permettant de calculer le score d'alignement entre 2 chaînes de caracteres
------------------------------------------------------------------------------------*/

/*
Input : Un caractere
Output : Un entier
Main : Fonction qui prend un caractere et retourne l'index correspondant (voir l'enum Base_Azotee)
*/
int get_val_base(char a) {
    //TODO
    switch (a)
    {
    case 'A':
        return A;
    case 'T':
        return T;
    case 'C':
        return C;
    case 'G':
        return G;
    default:
        return E;
    }
}

/*
Input : Deux caracteres 
Output : Un entier
Main : Fonction qui prend en entier 2 caracteres et qui retourne 
       le score entre les 2 caracteres suivant la matrice de similarite
*/
int similarity_score(char ch1, char ch2) {
    //TODO
    return (similarity_matrix[get_val_base(ch1)][get_val_base(ch2)]);
}

/*
Input : Deux chaînes de caracteres s
Output : Un entier
Main : Fonction qui prend en entier 2 chaînes de caracteres et qui retourne 
       le score d'alignement entre les deux chaînes
*/
int score_alignement(char* alignement1, char* alignement2) {
    //TODO
    int score_pairwise, score_t = 0;
    for (int i = 0; alignement1[i] != '\0'; i++){
        score_pairwise = similarity_score(alignement1[i],alignement2[i]);
        score_t += score_pairwise; 
    }
    return score_t;
}

/*
Input : Deux chaînes de caracteres et un score
Output : None
Main : Procedure qui prend en entier 2 chaînes de caracteres et un score
       Et qui fait un bel affichage montrant l'alignement et le score
*/
void print_quality_alignement(char* ali1, char* ali2, int score) {
    //TODO
    printf("Le score d'alignement : %d\n\t%s\n\t%s\n",score,ali1,ali2);
}

/*----------------------------
Algorithme de Needleman-Wunsch
------------------------------*/

/*
Input : 2 entiers et une matrice
Output : None
Main : Procedure qui Initialise la matrice M
*/
void initialise_M(int n, int m, int M[n][m]) {
    //TODO
    for (int i = 0; i <= (m+n-2); i++){
        if (i == 0){
            M[0][0] = 0;
        } 
        else if (i < m){
            //First Row
            M[0][i] = M[0][i-1] + similarity_matrix[0][get_val_base('-')];
        }
        else {
            //First Column
            M[(i-m+1)][0] = M[(i-m)][0] + similarity_matrix[0][get_val_base('-')];
        }  
    }
}

/*
Input : 2 entiers et une matrice
Output : None
Main : Procedure qui Initialise la matrice T
*/
void initialise_T(int n, int m, char T[n][m]) {
    //TODO
    for (int i = 0; i <= (m+n-2); i++){
        if (i == 0){
            T[0][0] = 'o';
        } 
        else if (i < m){
            //First Row
            T[0][i] = symbole(1);
        }
        else {
            //First Column
            T[(i-m+1)][0] = symbole(2);
        }  
    }
}

/*
Input : un entier
Output : un caractere
Main : Fonction qui retourne le caractere correspondant au maximum index de la formule Mij
*/
char symbole(int entier) {
    if (entier == 0) {
        return 'd';
    }
    else if (entier == 1) {
        return 'l';
    }
    return 'u';
}

/*
Input : une chaîne de caracteres
Output : None
Main : Procedure qui inverse une chaîne de caracteres
*/
void reverse_string(char* str) {
    //TODO
    char save;
    int rev = 0;
    for (int i = (strlen(str)-1); i >= rev; i--){
        save = str[i];
        str[i] = str[rev];
        str[rev++] = save;
    }
}

int max_matrix(int n, int m, int M[n][m], int i, int j, int* index, Sequence* s1, Sequence* s2){
    int score_up = M[i-1][j] + similarity_score(s2->seq[j-1],'_');
    int score_left = M[i][j-1] + similarity_score(s1->seq[i-1],'_');
    int score_diag = M[i-1][j-1] + similarity_score(s1->seq[i-1],s2->seq[j-1]);
    if (score_up >= score_left && score_up > score_diag){
        *index = 2;
        return score_up;
    }
    else if (score_left >= score_up && score_left > score_diag){
        *index = 1;
        return score_left;
    }
    else {
        *index = 0;
        return score_diag;
    }
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
void fonction_Mij(Sequence* s1, Sequence* s2, int i, int j, int n, int m, int M[n][m], int* max, int* index) {
    //TODO
    *max = max_matrix(n,m,M,i,j,index,s1,s2);
}

/*
Input : - 2 Sequences
        - Deux chaînes de caracteres
Output : None
Main : Procedure qui applique l'algorithme Needleman-Wunsch
       sur les 2 sequences et qui sauvegarde les alignements
       dans les 2 pointeurs
*/
void needleman_wunsch(Sequence seq1, Sequence seq2, char* alignement1, char* alignement2) {
    //TODO
    int max, n = strlen(seq1.seq)+1, m = strlen(seq2.seq)+1;
    int index;
    int M[n][m];
    char T[n][m];
    initialise_M(n,m,M);
    initialise_T(n,m,T);
    //
    printf("Check initialisation\n");
    printf("Check Matrix M\n");
    /*for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%d",M[i][j]);
        }
        printf("\n");
    }
    printf("Check Matrix T\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%c",T[i][j]);
        }
        printf("\n");
    }
    */
    int z = 0;
    for (int i = 1; i < n; i++){
        for (int j = 1; j < m; j++){
            fonction_Mij(&seq1,&seq2,i,j,n,m,M,&max,&index);
            M[i][j] = max; 
            T[i][j] = symbole(index);
        }
    }
    printf("Check MIJ\n");
    printf("Verfication matrix M\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%d ",M[i][j]);
        }
        printf("\n");
    }
    printf("Verfication matrix T\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%c ",T[i][j]);
        }
        printf("\n");
    }
    //Trace-back
    int i = (n-1), j = (m-1);
   
    while (T[i][j] != 'o'){

        //printf("Starting from the end of the matrix\n");

        if (T[i][j] == 'd'){
            appendString(alignement1,seq1.seq[i-1]);
            appendString(alignement2,seq2.seq[j-1]);
            --i, --j;
        }
        else if (T[i][j] == 'l'){
            appendString(alignement1,'-');
            appendString(alignement2,seq2.seq[j-1]);
            --j;
        }
        else {
            appendString(alignement1,seq1.seq[i-1]);
            appendString(alignement2,'-');
            --i;
        }
    }

    printf("TraceBack\n");

    printf("Check reverse string\n");
}







