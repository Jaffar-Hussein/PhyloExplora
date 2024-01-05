/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include "utils.h"

int main(int argc, char *argv[])
{
    int SEQUENCES = 0;
    int ALIGNEMENT = 0;
    int MATRICE_DISTANCE = 0;
    int UPGMA = 0;
    int NJ = 0;

    if (argc == 1)
    {
        printf("\033[31mError: No arguments provided.\033[0m\n");
        printf("\033[32mUsage: ./phylo SEQUENCES ALIGNEMENT MATRICE_DISTANCE UPGMA NJ\033[0m\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < strlen(argv[i]); j++)
        {
            argv[i][j] = toupper((unsigned char)argv[i][j]);
        }
        if (strcmp(argv[i], "ALL") == 0)
        {
            SEQUENCES = 1;
            ALIGNEMENT = 1;
            MATRICE_DISTANCE = 1;
            UPGMA = 1;
            NJ = 1;
        }
        else if (strcmp(argv[i], "SEQUENCES") == 0)
        {
            SEQUENCES = 1;
        }
        else if (strcmp(argv[i], "ALIGNEMENT") == 0)
        {
            ALIGNEMENT = 1;
        }
        else if (strcmp(argv[i], "MATRICE_DISTANCE") == 0)
        {
            MATRICE_DISTANCE = 1;
        }
        else if (strcmp(argv[i], "UPGMA") == 0)
        {
            UPGMA = 1;
        }
        else if (strcmp(argv[i], "NJ") == 0)
        {
            NJ = 1;
        }
        else
        {
            printf("\033[31mError: Invalid argument '%s'.\033[0m\n", argv[i]);
            printf("\033[32mUsage: ./phylo SEQUENCES ALIGNEMENT MATRICE_DISTANCE UPGMA NJ\033[0m\n");
            return 1;
        }
    }
    char *file = "cat_dna.fasta";
    char *file_aligne = "cat_dna_aligne.fasta";

    if (SEQUENCES == 1)
    {
        printf("----------------");
        printf("SEQUENCES");
        printf("----------------\n");
        printf("Je vais parser le fichier : '%s'\n", file);
        show_sequences_file(file);
    }

    /*
    ALIGNEMENT
    */
    if (ALIGNEMENT == 1)
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

    if (MATRICE_DISTANCE == 1)
    {
        printf("----------------");
        printf("MATRICE DE DISTANCE");
        printf("----------------\n");
        show_distance_matrix(file_aligne);
    }

    if (UPGMA == 1)
    {
        printf("----------------");
        printf("UPGMA");
        printf("----------------\n");
        show_tree(file_aligne, 'U');
    }

    if (NJ == 1)
    {
        printf("----------------");
        printf("NEIGHBOR JOINING");
        printf("----------------\n");
        show_tree(file_aligne, 'N');
    }
}