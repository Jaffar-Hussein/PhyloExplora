#include "utils.h"

float distance(Sequence seq1, Sequence seq2)
{
    float substitutions = 0;
    float total = 0;
    int length = strlen(seq1.seq);

    for (int i = 0; i < length; i++)
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
    // printf (float)substitutions / total;
    // printf("substitutions: %f\n", substitutions/total);
    return substitutions / total;
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
            matrice_distance[i][j] = 0;
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
void fill_distance_matrix(int entries, float matrice_distance[][entries], Sequence sequences[])
{
    for (int i = 0; i < entries; i++)
    {
        for (int j = 0; j < entries; j++)

        {
            float p_distance = distance(sequences[i], sequences[j]);

            matrice_distance[j][i] = jukes_cantor(p_distance);
        }
    }
    // print whole matrix

    // for(int i = 0; i < entries; i++){
    //     for(int j = 0; j < entries; j++){
    //         printf("%f ", matrice_distance[i][j]);
    //     }
    //     printf("\n");
    // }
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

    float matrice_distance[nb_entries][nb_entries];
    initialise_matrice(nb_entries, matrice_distance);
    fill_distance_matrix(nb_entries, matrice_distance, tab_sequences_aligne);
    printf("La matrice de distance calculee pour le fichier '%s' :\n", file_aligne);
    print_matrix_float(nb_entries, nb_entries, matrice_distance);
    printf("\n");
}

/*------------------------------------------------
Fonctions de manipulation de chaînes de caracteres
--------------------------------------------------*/

/*
Input : une chaîne de caracteres et un caractere
Output : None
Main : Ajoute le caractere à la fin de la chaîne de caracteres
*/
void appendString(char *str, char c)
{
    int length = strlen(str);
    str[length] = c;
    str[length + 1] = '\0';
}

/*
Input : une chaîne de caracteres
Output : None
Main : Initialise la chaîne de caracteres comme une chaîne vide
*/
void set_empty_string(char *str)
{
    str[0] = '\0';
}

/*------------------------------------
Fonctions de manipulation de sequences
--------------------------------------*/

/**
 * Sets the ID of a Sequence object.
 *
 * @param sequence The Sequence object to set the ID for.
 * @param ID The ID to set.
 */
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

/*
Input : une sequence
Output : None
Main : Effectue l'affichage de la sequence
*/
void affiche_sequence(Sequence *sequence)
{
    printf("\t*ID : %s\n\t*Sequence : %s\n", sequence->ID, sequence->seq);
}

/*-------------------------------
Fonctions de manipulation de fichiers
---------------------------------*/

/*
Input : Adresse d'un fichier
Output : Nombre de sequences dans le fichier
Main : Compte le nombre de sequences presentes dans le fichier
*/
// https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/
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

/*
Input : Adresse d'un fichier
Output : Une chaîne de caracteres
Main : Fonction qui lit un fichier et retourne la chaîne de caracteres
*/
// https://stackoverflow.com/a/15713419
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

/*
Input : - une chaîne de caracteres correspondant au code
        - un entier correspondant à la position start, à partir de laquelle on va commencer à chercher
        - Une sequence qu'on va set à partir de l'information trouvee dans le code
Output : - un entier correspondant à la position où on a fini de "lire"
Main : Fonction qui prend le code ainsi qu'une position start, elle va chercher la prochaine sequence
       definie apres le start et set l'objet sequence avec cette information.
       Elle retourne ensuite la derniere position qui est lu. Pour le cas de la derniere
       sequence elle retourne -1
*/
int extract_next_sequence(char *code, int start, Sequence *sequence)
{
    int flag = 0;
    char id[ID_MAX_LENGTH];
    char seq[seq_MAX_LENGTH];
    set_empty_string(id);
    set_empty_string(seq);

    // Increment start at the beginning of the loop
    while (code[++start] != '>' && code[start] != '\0')
    {
        // If we haven't encountered a newline character yet, we're still reading the ID
        if (code[start] != '\n' && flag == 0)
        {
            appendString(id, code[start]);
        }
        else
        {
            // Once we encounter a newline character, we start reading the sequence
            flag = 1;
            if (code[start] != '\n' && code[start] != '>')
            {
                appendString(seq, code[start]);
            }
        }
    }

    // If we've reached the end of the string, return -1
    if (code[start] == '\0')
    {
        return -1;
    }
    else
    {
        // Otherwise, set the sequence and return the current position
        set_sequence(sequence, id, seq);
        return start;
    }
}

/*
Input : Adresse d'un fichier et une liste de sequences
Output : None
Main : Fonction qui lit un fichier, remplit la liste avec les sequences trouvees dans le fichier
*/
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
    }
}

/*
Input : Adresse d'un fichier
Output : None
Main : Parse le fichier, sauvegarde les sequences dans une liste.
       Puis affiche une sequence une par une.
*/
void show_sequences_file(char *file)
{
    int nb_entries = get_number_entries(file);
    printf("Nombre d'entrees : %d\n", nb_entries);
    printf("\n");
    Sequence tab_sequences[nb_entries];
    parse_file(file, tab_sequences);

    for (int i = 0; i < nb_entries; i++)
    {
        affiche_sequence(&tab_sequences[i]);
        printf("\n");
    }
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

/*
---------------------------
Fonctions de matrice de float
-----------------------------*/

/*
Input : un entier, 2 matrices de float
Output : None
Main : Procedure qui copie l'ancienne matrice dans le nouveau
*/
void set_copy(int entries, float new_tab[][entries], float old_tab[][entries])
{
    for (int i = 0; i < entries; i++)
    {
        for (int j = 0; j < entries; j++)
        {
            new_tab[i][j] = old_tab[i][j];
        }
    }
}

/*
Input : - 2 entiers
        - une matrice de float
        - un pointeur sur un float
        - 2 pointeurs sur des entiers
Output : None
Main : Procedure qui trouve la valeur min dans la matrice Inferieur et stocke cette valeur
       dans le pointeur et ces index dans les 2 autres pointeurs
*/
void find_min_index_distance_matrix(int entries, int nb_noeud, float matrice_distance[][entries], float *min, int *i_min, int *j_min)
{
    // TODO -- what is nb_noued for ?

    *min = matrice_distance[1][0];
    *i_min = 1;
    *j_min = 0;

    for (int i = 1; i < entries; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (matrice_distance[i][j] < *min)
            {
                *min = matrice_distance[i][j];
                *i_min = i;
                *j_min = j;
            }
        }
    }
    // Values of i_min and j_min are
    printf("i_min: %d\n", *i_min);
    printf("j_min: %d\n", *j_min);
    printf("min: %f\n", *min);
}

/*--------------------------------
Fonctions de manipulation de noeud
----------------------------------*/
/*
Input : Un Noeud
Output : Entier
Main : Fonction qui retourne 1 si un noeud est une feuille, 0 sinon
*/
int est_feuille(Noeud *e)
{
    if (e->suivant_left == NULL && e->suivant_right == NULL)
    {
        return 1;
    }
    return 0;
}

/*
Input : None
Output : pointeur sur un noeud
Main : qui cree un noeud vide
*/
Noeud *new_noeud()
{
    Noeud *n = (Noeud *)malloc(sizeof(Noeud));
    n->suivant_left = NULL;
    n->suivant_right = NULL;
    n->valeur = NULL;
    n->nb_noeud = 1;
    return n;
}

/*
Input : pointeur sur un noeud
Output : pointeur sur un noeud
Main : qui cree une copie du noeud, en copiant chaque element un par un
*/
Noeud *create_copy(Noeud *e)
{
    Noeud *n = new_noeud();
    n->valeur = e->valeur;
    n->nb_noeud = e->nb_noeud;

    if (e->suivant_left != NULL)
    {
        Noeud *left = create_copy(e->suivant_left);
        n->suivant_left = left;
    }

    if (e->suivant_right != NULL)
    {
        Noeud *right = create_copy(e->suivant_right);
        n->suivant_right = right;
    }
    return n;
}

/*-----------------------------------
Fonctions de manipulation d'affichage
-------------------------------------*/

/*
Input : pointeur sur un arbre
Output : None
Main : procedure qui affiche un arbre
*/
// void new_affichage(Arbre *a)
// {
//     // TODO
//     Noeud *root = a->tete;
//     if (root == NULL)
//         return;
//     printf("%s ", a->tete->valeur);
//     new_affichage(a->tete->suivant_left);
//     new_affichage(a->tete->suivant_right);
// }
void new_affichage_noeud(Noeud *n)
{
    if (n == NULL)
        return;
    printf("%s ", n->valeur);
    new_affichage_noeud(n->suivant_left);
    new_affichage_noeud(n->suivant_right);
}

void new_affichage(Arbre *a)
{
    new_affichage_noeud(a->tete);
} /*
 Input : pointeur sur un noeud
 Output : None
 Main : procedure qui affiche le noeud (d'une maniere plate)
 */
void afficher_elem_plat(Noeud *e)
{
    if (e == NULL)
        return;

    if (est_feuille(e))
        printf("%s", e->valeur);
    else
    {
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
Main : procedure qui affiche un arbre (d'une maniere plate)
*/
void afficher_arbre_plat(Arbre *a)
{
    Noeud *e = a->tete;
    printf("\n");
    afficher_elem_plat(e);
    printf("\n");
}

/*-----------------------------------------
Fonctions de manipulation de liste de noeud
-------------------------------------------*/

/*
Input : pointeur d'une Liste de Noeud
Output : entier
Main : Fonction qui retourne le nombre d'elements dans la liste
*/
int get_nb_noeuds(List_Noeuds *list)
{
    return list->nb_elements;
}

/*
Input : pointeur d'une Liste de Noeud et un entier
Output : Pointeur sur un element
Main : Fonction qui retourne l'element qui se trouve à l'index i
*/
Element *get_element(List_Noeuds *list, int i)
{
    if (i < get_nb_noeuds(list))
    {
        Element *temp_ele = list->head;
        for (int k = 0; k < i; k++)
        {
            temp_ele = temp_ele->next;
        }
        return temp_ele;
    }
}

/*
Input : pointeur d'une Liste de Noeud et un entier
Output : Pointeur sur un noeud
Main : Fonction qui retourne le noeud stocke dans l'element qui se trouve à l'index i
*/
Noeud *get_noeud_from_list(List_Noeuds *list, int i)
{
    return get_element(list, i)->data;
}

/*
Input : pointeur d'une Liste de Noeud et un pointeur sur un noeud
Output : None
Main : Procedure qui cree un nouvel element, stocke le noeud dans l'element et qui
       ajoute l'element à la fin de la liste, en faisant attention de bien modifier la
       taille de la liste.
*/
void add_Noeud(List_Noeuds *list, Noeud *n)
{
    Element *temp = get_element(list, get_nb_noeuds(list) - 1);
    Element *to_add = (Element *)malloc(sizeof(Element));
    to_add->next = NULL;
    to_add->data = n;
    temp->next = to_add;

    list->nb_elements++;
}

/*
Input : pointeur d'une Liste de Noeud et 2 entiers
Output : pointeur sur une liste
Main : Fonction qui regroupe ensemble les deux noeuds qui se trouvent à l'index i et j
       et place cette nouvelle noeud dans un element qui se place au debut d'une
       nouvelle liste. Ainsi les autres elements de la liste originale sont concatenes
       à la nouvelle dans le même ordre. Ainsi taille(nouvelle) = taille(ancienne)-1.
       Elle retourne le pointeur de cette nouvelle liste.
*/
List_Noeuds *group_together(List_Noeuds *list_param, int i, int j)
{
    // TODO
    Noeud *n = new_noeud();
    n->suivant_left = get_noeud_from_list(list_param, i);
    n->suivant_right = get_noeud_from_list(list_param, j);
    n->nb_noeud = n->suivant_left->nb_noeud + n->suivant_right->nb_noeud;
    List_Noeuds *list = (List_Noeuds *)malloc(sizeof(List_Noeuds));
    Element *e = (Element *)malloc(sizeof(Element));
    e->data = n;
    list->head = e;
    // list->head = n;
    list->nb_elements = 1;
    for (int k = 0; k < get_nb_noeuds(list_param); k++)
    {
        if (k != i && k != j)
        {
            add_Noeud(list, get_noeud_from_list(list_param, k));
        }
    }
    return list;
}

/*------------------
Fonctions pour UPGMA
--------------------*/

/*
Input : - taille de la matrice (entier)
        - pointeur d'une Liste de Noeud
        - matrice de float
        - 3 entiers
Output : float
Main : Fonction qui calcule la valeur d'une nouvelle cellule dans la matrice à partir de la formule d_ij,k
*/
float calcule_new_cell(int entries, List_Noeuds *list, float matrice_distance[][entries], int i, int j, int k)
{
    // TODO
    Noeud *node_i = get_noeud_from_list(list, i);
    Noeud *node_j = get_noeud_from_list(list, j);
    float n_i = node_i->nb_noeud;
    float n_j = node_j->nb_noeud;
    float d_ik = matrice_distance[i][k];
    float d_jk = matrice_distance[j][k];

    return (n_i / (n_i + n_j)) * d_ik + (n_j / (n_i + n_j)) * d_jk;
}

/*
Input : - taille de la matrice (entier)
        - pointeur d'une Liste de Noeud
        - matrice de float
Output : pointeur d'une Liste de Noeud
Main : Fonction qui effectue une etape de l'algorithme de UPGMA et qui retourne un pointeur
      sur une nouvelle liste de noeuds
*/
List_Noeuds *fuse_matrice_upgma(int entries, List_Noeuds *list, float matrice_distance[][entries])
{
    // TODO
    int i, j;
    float min;

    // Use find_min_index_distance_matrix to find the pair of nodes with the smallest distance
    find_min_index_distance_matrix(entries, 0, matrice_distance, &min, &i, &j);

    // Create a new node that groups together the nodes at indices i and j
    Noeud *new_node = new_noeud();
    new_node->suivant_left = get_noeud_from_list(list, i);
    new_node->suivant_right = get_noeud_from_list(list, j);
    new_node->nb_noeud = new_node->suivant_left->nb_noeud + new_node->suivant_right->nb_noeud;

    // Create a new distance matrix
    float new_matrice_distance[entries - 1][entries - 1];

    // Fill the new distance matrix
    for (int k = 0; k < entries - 1; k++)
    {
        for (int l = 0; l < entries - 1; l++)
        {
            if (k == l)
            {
                new_matrice_distance[k][l] = 0;
            }
            else if (k == i || k == j || l == i || l == j)
            {
                new_matrice_distance[k][l] = calcule_new_cell(entries, list, matrice_distance, i, j, k);
            }
            else
            {
                new_matrice_distance[k][l] = matrice_distance[k][l];
            }
        }
    }

    // Create a new list of nodes
    List_Noeuds *new_list = group_together(list, i, j);

    return new_list;
}

/*
Input : - taille de la matrice (entier)
        - pointeur d'une Liste de Noeuds
        - matrice de float
Output : Un arbre
Main : Fonction qui effectue l'algorithme de UPGMA et qui retourne un arbre
*/
Arbre UPGMA(int entries, List_Noeuds *list, float matrice_distance[][entries])
{

    int nb_noeuds = get_nb_noeuds(list);
    while (nb_noeuds > 1)
    {
        list = fuse_matrice_upgma(entries, list, matrice_distance);
        nb_noeuds = get_nb_noeuds(list);
    }
    // print out the list nodes
    for (int i = 0; i < nb_noeuds; i++)
    {
        printf("%s\n", get_noeud_from_list(list, i)->valeur);
    }

    Arbre a;
    a.tete = list->head->data;

    return a;
}

/*-----------------------------
Fonctions pour Neighbor Joining
-------------------------------*/

/*
Input : - taille de la matrice (entier)
        - Nombre de noeuds
        - Liste de float
        - matrice de float
Output : None
Main : Procedure qui calcule les S de la matrice de distance donnee en parametre en suivant les regles definies dans le lien
*/
void calcul_S(int entries, int nb_noeuds, float S[nb_noeuds], float matrice[][entries])
{
    // TODO
}

/*
Input : - taille de la matrice (entier)
        - Nombre de noeuds
        - Liste de float
        - matrice de float
        - pointeur sur un float
        - 2 pointeurs sur des entiers
Output : None
Main : Procedure qui calcule le plus petit Mij et qui stocke les i et j dans les pointeurs
*/
void calcule_pair_Mij(int entries, int nb_noeuds, float S[nb_noeuds], float matrice[][entries], float *min_val, int *i_min, int *j_min)
{
    // TODO
}

/*
Input : - taille de la matrice (entier)
        - pointeur d'une Liste de Noeud
        - matrice de float
Output : pointeur d'une Liste de Noeud
Main : Fonction qui effectue une etape de l'algorithme de Neighbor Joining et qui retourne un pointeur
      sur une nouvelle liste de noeuds
*/
List_Noeuds *fuse_matrice_NJ(int entries, List_Noeuds *list, float matrice_distance[][entries])
{
    // TODO
}

/*
Input : - taille de la matrice (entier)
        - pointeur d'une Liste de Noeud
        - matrice de float
Output : Un arbre
Main : Fonction qui effectue l'algorithme de Neighbor Joining et qui retourne un arbre
*/
Arbre Neighbor_Joining(int entries, List_Noeuds *list, float matrice_distance[][entries])
{

    int nb_noeuds = get_nb_noeuds(list);
    printf("Initial number of nodes: %d\n", nb_noeuds);
    while (nb_noeuds > 1)
    {
        list = fuse_matrice_NJ(entries, list, matrice_distance);
        nb_noeuds = get_nb_noeuds(list);
        printf("Number of nodes after fusion: %d\n", nb_noeuds);
        // print_(list);
    }

    Arbre a;
    a.tete = list->head->data;
    return a;
}
void print_tree(Noeud *node)
{
    if (node == NULL)
    {
        return;
    }

    // Print the node value
    printf("%s ", node->valeur);

    // Recur on the left subtree
    print_tree(node->suivant_left);

    // Recur on the right subtree
    print_tree(node->suivant_right);
}
//---------------------------------------------------------------------------------------

/*
Input : - une chaîne de caracteres correspondant à une adresse
        - l'algorithme de construction voulu, un caractere (U ou N)
Output : None
Main : Une procedure qui prend une adresse d'un fichier, le parse, extrait les sequences
       alignees et ensuite construit et affiche l'arbre phylogenetique correspondant
       Soit avec l'algo UPGMA ou Neighbor joining.
*/
void show_tree(char *file_aligne, char Algorithme)
{
    int nb_entries = get_number_entries(file_aligne);
    Sequence tab_sequences_aligne[nb_entries];
    // print tab sequence

    for (int i = 0; i < nb_entries; i++)
    {
        printf("%s\n", tab_sequences_aligne[i].ID);
    }
    parse_file(file_aligne, tab_sequences_aligne);

    float matrice_distance[nb_entries][nb_entries];
    initialise_matrice(nb_entries, matrice_distance);
    fill_distance_matrix(nb_entries, matrice_distance, tab_sequences_aligne);
    // print out the distance matrix
    for (int i = 0; i < nb_entries; i++)
    {
        for (int j = 0; j < nb_entries; j++)
        {
            printf("%f ", matrice_distance[i][j]);
        }
        printf("\n");
    }
    List_Noeuds list;
    list.head = NULL;
    Noeud *n = new_noeud();
    n->valeur = tab_sequences_aligne[0].ID;

    Element *temp = (Element *)malloc(sizeof(Element));
    temp->next = NULL;
    temp->data = n;
    list.head = temp;
    list.nb_elements = 1;

    for (int i = 1; i < nb_entries; i++)
    {
        Noeud *n = new_noeud();
        n->valeur = tab_sequences_aligne[i].ID;
        add_Noeud(&list, n);
    }

    // Print out all the nodes in the list
    for (int i = 0; i < nb_entries; i++)
    {
        printf("%s\n", get_noeud_from_list(&list, i)->valeur);
    }

    Arbre a;

    // check if arbre is NULL
    if (a.tete == NULL)
    {
        printf("Arbre NULL\n");
    }
    else
    {
        printf("Arbre non NULL\n");
        // printf("%s\n", a.tete->valeur);
        printf("----");
    }

    if (Algorithme == 'U')
    {
        printf("Arbre UPGMA construit pour le fichier '%s' :\n", file_aligne);
        a = UPGMA(nb_entries, &list, matrice_distance);
        // print_tree(a.tete);
    }
    // else
    // {
    //     printf("Arbre NEIGHBOR JOINING construit pour le fichier '%s' :\n", file_aligne);
    //     a = Neighbor_Joining(nb_entries, &list, matrice_distance);
    // }
    afficher_arbre_plat(&a);
    // show the arbe A

    // new_affichage(&a);
}

int main()
{

    // Matrix
  
    // Matrix
    char *file = "cat_dna.fasta";
    char *file_aligne = "cat_dna_aligne.fasta";
    printf("----------------");
    printf("UPGMA");
    printf("----------------\n");
    show_tree(file_aligne, 'U');
}
