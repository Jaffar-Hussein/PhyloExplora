/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include "utils.h"

void set_id(Sequence *sequence, char *ID)
{
    int length = strlen(ID);
    for (int i = 0; i < length; i++)
    {
        sequence->ID[i] = ID[i];
    }
    sequence->ID[length] = '\0';
}

/*
Input : une sequence et une chaîne de caracteres
Output : None
Main : Initialise la chaîne de caracteres en tant que sequence pour l'objet sequence
*/
void set_seq(Sequence *sequence, char *seq)
{
    int length = strlen(seq);
    for (int i = 0; i < length; i++)
    {
        sequence->seq[i] = seq[i];
    }
    sequence->seq[length] = '\0';
}

/*
Input : une sequence et un entier
Output : Un caractere
Main : Retourne le nucleotide correspondant à l'index
*/
char get_nucleotide(Sequence *sequence, int i)
{
    return sequence->seq[i];
}

/*
Input : une sequence et deux chaînes de caracteres
Output : None
Main : Initialise l'ID et la sequence pour l'objet sequence
*/
void set_sequence(Sequence *sequence, char *ID, char *seq)
{
    set_id(sequence, ID);
    set_seq(sequence, seq);
}

void set_empty_string(char *str)
{
    str[0] = '\0';
}

void appendString(char *str, char c)
{
    int length = strlen(str);
    str[length] = c;
    str[length + 1] = '\0';
}
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
    int gap_penalty = similarity_matrix[0][get_val_base('-')];

    // fill the first row
    for (int j = 0; j < m; j++)
    {
        M[j][0] = j * gap_penalty;
    }

    // fill the first column
    for (int i = 0; i < n; i++)
    {
        M[0][i] = i * gap_penalty;
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
    for (int j = 1; j < m; j++)
    {
        T[0][j] = 'l';
    }

    // fill the first column
    for (int i = 1; i < n; i++)
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
    int score_diagonal = M[i - 1][j - 1] + similarity_score(s1->seq[i - 1], s2->seq[j - 1]);
    int score_left = M[i][j - 1] + similarity_score(s1->seq[i - 1], '-');
    int score_up = M[i - 1][j] + similarity_score('-', s2->seq[j - 1]);
    // get the max
    *max = max3(score_diagonal, score_left, score_up);
    // send back the index
    if (*max == score_left)
        *index = 1;
    else if (*max == score_up)
        *index = 2;
    else
        *index = 0;
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
    int n = strlen(seq1.seq) + 1;
    int m = strlen(seq2.seq) + 1;

    // The scoring and traceback matrices
    int M[n][m];
    char T[n][m];

    // Initialize the matrices
    initialise_M(n, m, M);
    initialise_T(n, m, T);
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            int max, index;
            fonction_Mij(&seq1, &seq2, i, j, n, m, M, &max, &index);
            M[i][j] = max;
            T[i][j] = symbole(index);
        }
    }

    // Traceback and build the alignments
    int i = n - 1;
    int j = m - 1;
    while (T[i][j] != 'o')
    {
        if (T[i][j] == 'd')
        {
            appendString(alignement1, seq1.seq[i - 1]);
            appendString(alignement2, seq2.seq[j - 1]);
            i--;
            j--;
        }
        else if (T[i][j] == 'u')
        {
            appendString(alignement1, seq1.seq[i - 1]);
            appendString(alignement2, '-');
            i--;
        }
        else // T[i][j] == 'l'
        {
            appendString(alignement1, '-');
            appendString(alignement2, seq2.seq[j - 1]);
            j--;
        }
    }

    // Reverse the alignments
    reverse_string(alignement1);
    reverse_string(alignement2);
}

int main()
{
    printf("----------------");
    printf("ALIGNEMENT");
    printf("----------------\n");

    char *ali1 = "-ACTCCTGA";
    char *ali2 = "ATCTCGTGA";
    print_quality_alignement(ali1, ali2, score_alignement(ali1, ali2));

    ali1 = "A-CTCCTGA";
    ali2 = "ATCTCGTGA";
    print_quality_alignement(ali1, ali2, score_alignement(ali1, ali2));

    ali1 = "AC-TCCTGA";
    ali2 = "ATCTCGTGA";
    print_quality_alignement(ali1, ali2, score_alignement(ali1, ali2));

    char alignement1[seq_MAX_LENGTH];
    char alignement2[seq_MAX_LENGTH];
    set_empty_string(alignement1);
    set_empty_string(alignement2);

    Sequence seq1;
    set_sequence(&seq1, "Sequence 1", "ACTCCTGA");
    Sequence seq2;
    set_sequence(&seq2, "Sequence 2", "ATCTCGTGA");
    needleman_wunsch(seq1, seq2, alignement1, alignement2);

    printf("On cherche à aligner '%s' et '%s' en utilisant l'algorithme Needleman Wunsch, on obtient comme alignement :\n", seq1.seq, seq2.seq);
    print_quality_alignement(alignement1, alignement2, score_alignement(alignement1, alignement2));
}