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
void initialise_M(int n, int m, int M[n][m])
{
    // fill the first gap
    M[0][0] = 0;

    // fill the first row
    for (int j = 1; j < m; j++)
    {
        M[0][j] = M[0][j - 1] - 5;
    }

    // fill the first column
    for (int i = 1; i < n; i++)
    {
        M[i][0] = M[i - 1][0] - 5;
    }
}

/*
Input : 2 entiers et une matrice
Output : None
Main : Procedure qui Initialise la matrice T
*/
void initialise_T(int n, int m, char T[n][m])
{
    // fill the first gap
    T[0][0] = 'o';

    // fill the first row
    for (int j = 1; j < m + 1; j++)
    {
        T[0][j] = 'l';
    }

    // fill the first column
    for (int i = 1; i < n + 1; i++)
    {
        T[i][0] = 'u';
    }
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
void strrev(char *str)
{
    if (str)
    {
        char *start = str;
        char *end = start + strlen(str) - 1;
        char temp;

        while (end > start)
        {
            temp = *start;
            *start = *end;
            *end = temp;

            start++;
            end--;
        }
    }
}
/*
Input : une chaîne de caracteres
Output : None
Main : Procedure qui inverse une chaîne de caracteres
*/
void reverse_string(char *str)
{
    strrev(str);
}
/**
 * Returns the maximum value among three integers.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @param c The third integer.
 * @return The maximum value among a, b, and c.
 */
int max3(int a, int b, int c)
{
    if (a >= b && a >= c)
    {
        return a;
    }
    else if (b >= a && b >= c)
    {
        return b;
    }
    else
    {
        return c;
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
void fonction_Mij(Sequence *s1, Sequence *s2, int i, int j, int n, int m, int M[n][m], int *max, int *index)
{
    // Mij = max(M,-1,-1 + s(A, B), M,-1 + S(A, gap), Mi-j + s(B, gap))
    // printf("seq1 : %s\n", s1->seq);
    // printf("seq2 : %s\n", s2->seq);
    int score_diagonal = M[i - 1][j - 1] + similarity_score(s1->seq[j - 1], s2->seq[i - 1]);
    int score_left = M[i][j - 1] + similarity_score(s1->seq[j - 1], '-');
    int score_up = M[i - 1][j] + similarity_score('-', s2->seq[i - 1]);
    // max of the 3 scores
    // if (i = 7 && j == 6)
    // {
    //     printf("M : %d\n", M[i - 1][j - 1]);
    //     printf("score_diagonal : %d\n", score_diagonal);
    //     printf("score_left : %d\n", score_left);
    //     printf("score_up : %d\n", score_up);
    // }
    *max = max3(score_diagonal, score_left, score_up);
    printf("score on row %d and column %d : %d\n", i, j, max3(score_diagonal, score_left, score_up));

    // send back the index
    if (*max == score_left)
    {
        *index = 1;
    }
    else if (*max == score_up)
    {
        *index = 2;
    }
    else
    {
        *index = 0;
    }
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
    // Create the sizes of the tables and add 1 for the gap
    int n = strlen(seq1.seq) + 1;
    int m = strlen(seq2.seq) + 1;

    // printf("n : %d\n", n);
    // printf("m : %d\n", m);
    // The max and index to be passed by reference
    int max = 0;
    int index = 0;
    // The two tables
    int M[n][m];
    char T[n][m];

    initialise_M(n, m, M);
    initialise_T(n, m, T);

    // Fill the spaces as of index 1,1
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            fonction_Mij(&seq1, &seq2, i, j, n, m, M, &max, &index);
            printf("max i = %d , j = %d : %d\n", i, j, max);
            M[i][j] = max;
            T[i][j] = symbole(index);
        }
    }

    // print the last position
    printf("$$$max : %d\n", M[m][n]);
    // Print the M matrix
    // Print column numbers
    printf("\t");
    for (int j = 0; j < m; j++)
    {
        printf("Col%d\t", j);
    }
    printf("\n");

    // Print each row with its row number
    for (int i = 0; i < n; i++)
    {
        printf("Row%d\t", i); // print row number
        for (int j = 0; j < m; j++)
        {
            printf("%d\t", M[i][j]); // print cell value
        }
        printf("\n");
    }
    printf("\n");
    // Getting the best alignment by the traceback matrix
    int i = n;
    int j = m;
    while (T[i][j] != 'o')
    {
        if (T[i][j] == 'd')
        {

            appendString(alignement1, seq1.seq[j--]);
            appendString(alignement2, seq2.seq[j--]);
            // i--;
            // j--;
        }
        else if (T[i][j] == 'l')
        {
            appendString(alignement1, '-');
            appendString(alignement2, seq2.seq[j--]);
            // j--;
        }
        else
        {
            appendString(alignement1, seq1.seq[i--]);
            appendString(alignement2, '-');
            // i--;
        }
    }

    reverse_string(alignement1);
    reverse_string(alignement2);

    printf("alignement1 : %s\n", alignement1);
    printf("alignement2 : %s\n", alignement2);
}
