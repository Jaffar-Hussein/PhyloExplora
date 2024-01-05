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
        printf("\033[32mUsage: ./phylo ALL\033[0m\n");
        printf("\033[32mUsage: ./phylo SEQUENCES ALIGNEMENT MATRICE_DISTANCE UPGMA NJ\033[0m\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < strlen(argv[i]); j++)
        {
            argv[i][j] = toupper(argv[i][j]);
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
            printf("\033[32mUsage: ./phylo ALL\033[0m\n");
            printf("\033[32mUsage: ./phylo SEQUENCES ALIGNEMENT MATRICE_DISTANCE UPGMA NJ\033[0m\n");
            return 1;
        }
    }
    char *file = "cat_dna.fasta";
    char *file_aligne = "cat_dna_aligne.fasta";

    // LOGOOOOO
    const char *title[] = {
        "",
        "",
        "",
        "____  _           _         _____            _                     ",
        "|  _ \\| |__  _   _| | ___   | ____|_  ___ __ | | ___  _ __ ___ _ __ ",
        "| |_) | '_ \\| | | | |/ _ \\  |  _| \\ \\/ / '_ \\| |/ _ \\| '__/ _ \\ '__|",
        "|  __/| | | | |_| | | (_) | | |___ >  <| |_) | | (_) | | |  __/ |   ",
        "|_|   |_| |_|\\__, |_|\\___/  |_____/_/\\_\\ .__/|_|\\___/|_|  \\___|_|   ",
        "             |___/                     |_|                          ",
        "",
        "",
        "",
    };

    const char *lions[] = {
        "|\\_                \\|\\||             ",
        "  -' | `.             -- ||||/       ",
        "/7      `-._        /7   |||||/            ",
        "/            `-.____/    |||||||/`-.____________",
        "\\-'_                \\-' |||||||||               `-._",
        " -- `-.              -/||||||||\\                `` -.`",
        "       |\\              /||||||\\             \\_  |   `\\\\",
        "       | \\  \\_______...-//|||\\|________...---'\\  \\    \\\\\\",
        "       |  \\  \\            ||  |  \\ ``-.__--. | \\  |    ``-.__--.",
        "       |  |\\  \\          / |  |\\  \\   ``---'/ / | |       ``---'",
        "     _/  / _|  )      __/_/  / _|  )     __/ / _| |",
        "    /,__/ /,__/      /,_/,__/_/,__/     /,__/ /,__/          tbk"};

    int lines1 = sizeof(title) / sizeof(title[0]);
    int lines2 = sizeof(lions) / sizeof(lions[0]);
    int max_lines = lines1 > lines2 ? lines1 : lines2;

    printf(COLOR_GREEN);
    for (int i = 0; i < max_lines; i++)
    {
        if (i < lines1)
        {
            printf("%-70s", title[i]);
        }
        else
        {
            printf("%-70s", "");
        }

        if (i < lines2)
        {
            printf("%s", lions[i]);
        }
        printf("\n");
    }
    printf(COLOR_RESET);
    // Ascciii Art

    if (SEQUENCES == 1)
    {
        printf("---------------- ");
        printf(BOLD_TEXT UNDERLINE_TEXT "SEQUENCES" COLOR_RESET);
        printf(" ----------------\n\n");
        printf("Je vais parser le fichier : '%s'\n\n", file);
        show_sequences_file(file);
    }

    /*
    ALIGNEMENT
    */
    if (ALIGNEMENT == 1)
    {
        printf("---------------- ");
        printf(BOLD_TEXT UNDERLINE_TEXT "ALIGNEMENT" COLOR_RESET);
        printf(" ----------------\n\n");

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

        printf("\nOn cherche à aligner '%s' et '%s' en utilisant l'algorithme Needleman Wunsch, on obtient comme alignement :\n\n", seq1.seq, seq2.seq);
        print_quality_alignement(alignement1, alignement2, score_alignement(alignement1, alignement2));
    }

    if (MATRICE_DISTANCE == 1)
    {
        printf("\n---------------- ");
        printf(BOLD_TEXT UNDERLINE_TEXT "MATRICE DE DISTANCE" COLOR_RESET);
        printf(" ----------------\n\n");
        show_distance_matrix(file_aligne);
    }

    if (UPGMA == 1)
    {
        printf("---------------- ");
        printf(BOLD_TEXT UNDERLINE_TEXT "UPGMA" COLOR_RESET);
        printf("----------------\n");
        show_tree(file_aligne, 'U');
    }

    if (NJ == 1)
    {
        printf("---------------- ");
        printf(BOLD_TEXT UNDERLINE_TEXT "NEIGHBOR JOINING" COLOR_RESET);
        printf(" ----------------\n\n");
        show_tree(file_aligne, 'N');
    }
}