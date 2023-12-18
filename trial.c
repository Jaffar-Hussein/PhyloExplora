#include "utils.h"
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
void initialise_M(int n, int m, int M[n][m])
{
    // fill the first gap
    M[0][0] = 0;

    // fill the first row
    for (int j = 0; j < m + 1; j++)
    {
        M[0][j] = M[0][j - 1] - 5;
    }

    // fill the first column
    for (int i = 1; i < n + 1; i++)
    {
        M[i][0] = M[i - 1][0] - 5;
    }
}

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
    // Mij = max(M,-1,-1 + s(A, B), M,-1 + S(A, gap), Mi-j + s(B, gap))
    int score_diagonal = M[i - 1][j - 1] + similarity_score(s1->seq[j - 1], s2->seq[i - 1]);
    int score_left = M[i][j - 1] + similarity_score(s1->seq[j - 1], '-');
    int score_up = M[i - 1][j] + similarity_score('-', s2->seq[i - 1]);
    // max of the 3 scores
    *max = max3(score_diagonal, score_left, score_up);

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
    int n = strlen(seq2.seq) + 1;
    int m = strlen(seq1.seq) + 1;
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
            M[i][j] = max;
            T[i][j] = symbole(index);
        }
    }
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
    {
        if (T[i][j] == 'd')
        {

            appendString(alignement1, seq1.seq[i]);
            appendString(alignement2, seq2.seq[j]);
            i--;
            j--;
        }
        else if (T[i][j] == 'l')
        {
            appendString(alignement1, '-');
            appendString(alignement2, seq2.seq[j]);
            j--;
        }
        else
        {
            appendString(alignement1, seq1.seq[i]);
            appendString(alignement2, '-');
            i--;
        }
    }
}

int main()
{
    int n = 5;
    int m = 5;
    int M[n][m];
    char T[n][m];
    initialise_M(n, m, M);
    initialise_T(n, m, T);

    char alignement1[seq_MAX_LENGTH];
    char alignement2[seq_MAX_LENGTH];
    set_empty_string(alignement1);
    set_empty_string(alignement2);

    Sequence seq1;
    set_sequence(&seq1, "Sequence 1", "ACTCCTGA");
    Sequence seq2;
    set_sequence(&seq2, "Sequence 2", "ATCTCGTGA");
    needleman_wunsch(seq1, seq2, alignement1, alignement2);
    // Display Matrix
    for (int i = 0; i < n; i++)
    {
        printf("\n");
        printf("\n\t");
        for (int j = 0; j < m; j++)
        {
            printf("Col %d\t", j);
        }
        printf("\n");
        for (int i = 0; i < n; i++)
        {
            printf("Row %d\t", i);
            for (int j = 0; j < m; j++)
            {
                printf("%d\t ", M[i][j]);
            }
            printf("\n");
        }
    }

    printf("\n");
}