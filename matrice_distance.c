/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include "utils.h"

/*
Input : Deux Sequences
Output : Float
Main : Fonction qui retourne la distance entre deux sequences 
*/
float distance(Sequence seq1, Sequence seq2) {
    //TODO
    float ev_step_count = 0.0, len = 0.0;
    for(int i = 0; seq1.seq[i] != '\0';i++){
        if ((seq1.seq != '-' && seq2.seq != '-')){
            if ((seq1.seq[i] !=  seq2.seq[i])){
                ev_step_count += 1.0;
            }
        }
        len += 1.0;
    }
    return (ev_step_count/len);
}

/*
Input : Float
Output : Float
Main : Fonction qui applique la correction de Jukes-Cantor
*/
float jukes_cantor(float x) {
    //TODO
    x = (-3.0/4.0) * logf((1.0 - ((4.0/3.0) * x)));
    return x;
}

/*-------------------------------------------------
Fonctions de manipulation de la matrice de distance
---------------------------------------------------*/

/*
Input : un entier et Une matrice de float
Output : None
Main : Procedure qui initialise une matrice à une matrice nulle
*/
void initialise_matrice(int entries, float matrice_distance[][entries]) {
    //TODO
    int j;
    for (int i = 1; i < entries; i++){
        j = 0;
        while (j < i)
        {
            matrice_distance[i][j++] = 0.0;
        }
    }
}

/*
Input : Deux entiers et Une matrice de float
Output : None
Main : Procedure qui print une matrice
*/
void print_matrix_float(int n, int m, float matrix[][m]) {
    //TODO
    int j;
    for (int i = 1; i < n; i++){
        j = 0;
        while (j < i)
        {
            printf("%.5f  ",matrix[i][j++]);
        }
        printf("\n");
    }
}

/*
Input : entier, matrice de float et une liste de sequence
Output : None
Main : Procedure qui remplit la matrice avec la distance entre les sequences
*/
void fill_distance_matrix(int entries, float matrice_distance[][entries], Sequence sequences[]) {
    //TODO
    for (int i = 0; i < entries; i++){
        for (int j = (i+1); j < entries; j++){
            matrice_distance[j][i] = jukes_cantor(distance(sequences[i],sequences[j]));
        }
    }
}

/*
Input : Un fichier
Output : None
Main : Fonction qui prend une adresse en entree et qui calcule et affiche la matrice de distance correspondant aux sequences
*/
void show_distance_matrix(char* file_aligne){
    printf("Hello World\n");
    int nb_entries = get_number_entries(file_aligne);
    printf("Get Number Entries Check : %d\n",nb_entries);
    Sequence tab_sequences_aligne[nb_entries];
    parse_file(file_aligne, tab_sequences_aligne);
    printf("Parse Check\n");
    for (int i = 0; i < nb_entries; i++) {
        affiche_sequence(&tab_sequences_aligne[i]);
        printf("\n");
    }
    float matrice_distance[nb_entries][nb_entries];
    initialise_matrice(nb_entries, matrice_distance);
    printf("Initialize Check\n");
    /*int j;
    for (int i = 1; i < nb_entries; i++){
        j = 0;
        while (j < i)
        {
            printf("%.1f",matrice_distance[i][j++]);
        }
        printf("\n");
    }*/
    fill_distance_matrix(nb_entries, matrice_distance, tab_sequences_aligne);
    printf("Fill Distance Matrix Check\n");
    printf("La matrice de distance calculee pour le fichier '%s' :\n", file_aligne);
    print_matrix_float(nb_entries, nb_entries, matrice_distance);
    printf("\n");
}
