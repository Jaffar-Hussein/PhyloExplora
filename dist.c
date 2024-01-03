

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
void appendString(char *str, char c)
{
    int length = strlen(str);
    str[length] = c;
    str[length + 1] = '\0';
}

char *readFile(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL)
        return NULL; // Impossible d'ouvrir le fichier
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);

    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char)c;
    }
    code[n] = '\0';
    return code;
}
void set_empty_string(char *str)
{
    str[0] = '\0';
}
int extract_next_sequence(char *code, int start_index, Sequence *sequence)
{
    int is_reading_id = 1;
    char id[ID_MAX_LENGTH];
    set_empty_string(id);
    char seq[seq_MAX_LENGTH];
    set_empty_string(seq);

    while (code[++start_index] != '>' && code[start_index] != '\0')
    {
        if (is_reading_id == 1)
        {
            if (code[start_index] == '\n')
            {
                is_reading_id = 0;
            } 
            else 
            {
                appendString(id, code[start_index]);
            }
        } 
        else 
        {
            if (code[start_index] != '\n')
            {
                appendString(seq, code[start_index]);
            }
        }
    }

    set_sequence(sequence, id, seq);

    if (code[start_index] == '\0')
    {
        return -1;
    }
    else 
    {
        return start_index;
    }
}

void parse_file(char *address, Sequence tab_sequences[])
{
    char *code = readFile(address);
    Sequence sequence;
    int start = 0;
    int counter = 0;

    // Keep extracting sequences until extract_next_sequence returns -1
    while (start != -1)
    {
        start = extract_next_sequence(code, start, &sequence);
        tab_sequences[counter++] = sequence;
        printf("Start : %d\n", start);
        printf("Counter : %d\n", counter);
        printf("ID ---- : %s\n", sequence.ID);
    }
}
int get_number_entries(char *address)
{
    int num = 0;
    FILE *ptr;
    char ch;
    ptr = fopen(address, "r");
    if (NULL == ptr)
    {
        printf("Le fichier ne peut pas être ouvert\n");
    }
    do
    {
        ch = fgetc(ptr);
        if (ch == '>')
        {
            num += 1;
        }
    } while (ch != EOF);
    fclose(ptr);
    return num;
}

/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

/*
Input : Deux Sequences
Output : Float
Main : Fonction qui retourne la distance entre deux sequences
*/
float distance(Sequence seq1, Sequence seq2)
{
    int substitutions = 0;
    int total = 0;
    for (int i = 0; seq1.seq[i] != '\0' && seq2.seq[i] != '\0'; i++)
    {
        if (seq1.seq[i] != '-' && seq2.seq[i] != '-')
        {
            total++;
            if (seq1.seq[i] != seq2.seq[i])
            {
                substitutions++;
            }
        }
    }
    return(float)substitutions / total;
}

/*
Input : Float
Output : Float
Main : Fonction qui applique la correction de Jukes-Cantor
*/
float jukes_cantor(float x)
{
    return -0.75 * log(1 - (4.0 / 3.0) * x);
}

/*-------------------------------------------------
Fonctions de manipulation de la matrice de distance
---------------------------------------------------*/

/*
Input : un entier et Une matrice de float
Output : None
Main : Procedure qui initialise une matrice à une matrice nulle
*/
void initialise_matrice(int entries, float matrice_distance[][entries])
{
    for (int i = 0; i < entries; i++)
    {
        for (int j = 0; j < entries; j++)
        {
            matrice_distance[i][j] = 0.0;
        }
    }
}

/*
Input : Deux entiers et Une matrice de float
Output : None
Main : Procedure qui print une matrice
*/
void print_matrix_float(int n, int m, float matrix[][m])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (j < i)
            {
                printf("%9f ", matrix[i][j]);
            }
            else
            {
                printf("     .    ");
            }
        }
        printf("\n");
    }
}

/*
Input : entier, matrice de float et une liste de sequence
Output : None
Main : Procedure qui remplit la matrice avec la distance entre les sequences
*/
void fill_distance_matrix(int entries, float distance_matrix[][entries], Sequence sequences[])
{
    for (int i = 0; i < entries; i++)
    {
        for (int j = 0; j < i; j++)
        {
            float pairwise_distance = distance(sequences[i], sequences[j]);
            distance_matrix[i][j] = jukes_cantor(pairwise_distance);
        }
    }
}

/*
Input : Un fichier
Output : None
Main : Fonction qui prend une adresse en entree et qui calcule et affiche la matrice de distance correspondant aux sequences
*/
void show_distance_matrix(char *file_aligne)
{
    int nb_entries = get_number_entries(file_aligne);
    Sequence tab_sequences_aligne[nb_entries];
    parse_file(file_aligne, tab_sequences_aligne);
    printf("Nombre d'entrees : %d\n", nb_entries);
    printf("\n");
    for (int i = 0; i < nb_entries; i++)
    {
        printf("%d : %s\n", i, tab_sequences_aligne[i].ID);
    }
    float matrice_distance[nb_entries][nb_entries];
    initialise_matrice(nb_entries, matrice_distance);
    fill_distance_matrix(nb_entries, matrice_distance, tab_sequences_aligne);
    printf("La matrice de distance calculee pour le fichier '%s' :\n", file_aligne);
    print_matrix_float(nb_entries, nb_entries, matrice_distance);
    printf("\n");
}

int main()
{
    char *file_aligne = "cat_dna_aligne.fasta";
    printf("----------------");
    printf("MATRICE DE DISTANCE");
    printf("----------------\n");
    show_distance_matrix(file_aligne);
}