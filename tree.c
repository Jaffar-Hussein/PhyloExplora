#include "utils.h"

/*
--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------
*/

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
Main : Procedure qui copie l'ancienne matrice dans la nouvelle
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

void set_new(int entries, float old_tab[][entries], float new_tab[][entries - 1], int idr, int idc)
{
    int ptr = 0;
    int ptrl;
    for (int i = 0; i <= entries; i++)
    {
        ptrl = ptr + 1;
        for (int j = (i + 1); j <= entries; j++)
        {
            if (ptrl < (entries))
            {
                if ((i != (idr + 1) && i != (idc + 1)) && (j != (idr + 1) && j != (idc + 1)))
                {

                    if (ptr == 0)
                    {
                        new_tab[ptrl][ptr] = 0.0;
                    }
                    else
                    {
                        new_tab[ptrl][ptr] = old_tab[j - 1][i - 1];
                    }
                    ptrl++;
                }
            }
        }
        if (i != idr && i != idc)
        {
            ptr++;
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
    // Check if the matrix has at least one entry
    if (entries > 0)
    {
        for (int i = 0; i < entries; i++)
        {
            for (int j = (i + 1); j < entries; j++)
            {
                // If it's the first pair of elements, initialize min, i_min, and j_min
                if (i == 0 && j == 1)
                {
                    *min = matrice_distance[j][i];
                    *i_min = i;
                    *j_min = j;
                }
                // If the current element is smaller than min, update min, i_min, and j_min
                else if (*min > matrice_distance[j][i])
                {
                    *min = matrice_distance[j][i];
                    *i_min = i;
                    *j_min = j;
                }
            }
        }
    }
    else
    {
        printf("La matrice n'est pas de dimension correcte pour une recherche de valeur minimale !");
    }
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

void new_affichage(Noeud *a, int *step, char mark)
{
    static int root = 0;
    static int evtime = 0;
    int b = 0;
    if (a == NULL)
    {
        return;
    }

    if (est_feuille(a))
    {
        if (*step > evtime)
        {
            evtime = *step;
        }

        for (int i = 1; i <= evtime; i++)
        {
            if (i == (evtime))
            {
                printf(COLOR_BLUE "----|" COLOR_GREEN " %d %s\n" COLOR_RESET, *step, a->valeur);
            }
            else
            {
                if (*step != evtime && i >= *step)
                {
                    if (b == 0)
                    {
                        printf(COLOR_BLUE "|----" COLOR_RESET);
                        b = 1;
                    }
                    else
                    {
                        printf(COLOR_BLUE "-----" COLOR_RESET);
                    }
                }
                else
                {
                    printf("     ");
                }
            }
        }

        *step -= 1;
    }
    else
    {
        *step += 1;
        mark = 'l';
        new_affichage(a->suivant_left, step, mark);
        for (int i = 0; i < *step; i++)
        {
            if (i == (*step - 1))
            {
                printf(COLOR_YELLOW "|----|\n" COLOR_RESET);
            }
            else
            {
                printf("     ");
            }
        }
        *step += 1;
        mark = 'r';
        new_affichage(a->suivant_right, step, mark);
        *step -= 1;
    }
}

/*
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
        printf(COLOR_PURPLE "(" COLOR_RESET);
        afficher_elem_plat(e->suivant_left);
        printf(COLOR_PURPLE ", " COLOR_RESET);
        afficher_elem_plat(e->suivant_right);
        printf(COLOR_PURPLE ")" COLOR_RESET);
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
        if (temp_ele == NULL)
        {
            printf("NULL pointer\n");
        }
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
       et place ce nouveau noeud dans un element qui se place au debut d'une
       nouvelle liste. Ainsi les autres elements de la liste originale sont concatenes
       à la nouvelle dans le même ordre. Ainsi taille(nouvelle) = taille(ancienne)-1.
       Elle retourne le pointeur de cette nouvelle liste.
*/
List_Noeuds *group_together(List_Noeuds *list_param, List_Noeuds *newl, int i, int j)
{
    // TODO
    Noeud *tempi = get_noeud_from_list(list_param, i);
    Noeud *tempj = get_noeud_from_list(list_param, j);
    Noeud *newn = new_noeud();
    newn->suivant_left = tempi;
    newn->suivant_right = tempj;
    newn->nb_noeud = (tempi->nb_noeud) + (tempj->nb_noeud);
    newn = create_copy(newn);
    Element *head = (Element *)malloc(sizeof(Element));
    head->data = newn;
    newl->head = head;
    newl->nb_elements = 1;

    for (int z = 0; z < get_nb_noeuds(list_param); z++)
    {

        if (z != i && z != j)
        {

            add_Noeud(newl, get_noeud_from_list(list_param, z));
        }
    }
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
    float res;
    if (k >= i)
    {
        if (k < j)
        {
            res = (((float)(get_noeud_from_list(list, (i))->nb_noeud) * matrice_distance[k][i]) + ((float)(get_noeud_from_list(list, (j))->nb_noeud) * matrice_distance[j][k])) / (float)((get_noeud_from_list(list, (i))->nb_noeud) + (get_noeud_from_list(list, (j))->nb_noeud));
        }
        else if (k >= j)
        {
            res = (((float)(get_noeud_from_list(list, (i))->nb_noeud) * matrice_distance[k][i]) + ((float)(get_noeud_from_list(list, (j))->nb_noeud) * matrice_distance[k][j])) / (float)((get_noeud_from_list(list, (i))->nb_noeud) + (get_noeud_from_list(list, (j))->nb_noeud));
        }
    }
    else
    {
        res = (((float)(get_noeud_from_list(list, (i))->nb_noeud) * matrice_distance[i][k]) + ((float)(get_noeud_from_list(list, (j))->nb_noeud) * matrice_distance[j][k])) / (float)((get_noeud_from_list(list, (i))->nb_noeud) + (get_noeud_from_list(list, (j))->nb_noeud));
    }
    return res;
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
    // Allocate memory for a new list of nodes
    List_Noeuds *newl = (List_Noeuds *)malloc(sizeof(List_Noeuds));

    float min;
    float newdv;
    int k = 0;
    int ptr = 1;
    int j_min;
    int i_min;

    find_min_index_distance_matrix(entries, list->nb_elements, matrice_distance, &min, &i_min, &j_min);

    group_together(list, newl, (i_min), (j_min));

    float matrice_distance_new[entries - 1][entries - 1];

    set_new(entries, matrice_distance, matrice_distance_new, j_min, i_min);

    while (k < entries)
    {
        if (k != i_min && k != j_min)
        {
            newdv = calcule_new_cell(entries, list, matrice_distance, i_min, j_min, k);

            matrice_distance_new[ptr][0] = newdv;

            ptr++;
        }

        k++;
    }

    set_copy(newl->nb_elements, matrice_distance, matrice_distance_new);

    return newl;
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
        list = fuse_matrice_upgma(list->nb_elements, list, matrice_distance);
        nb_noeuds = get_nb_noeuds(list);
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
    float sum;
    int c;
    int j;
    if (entries > 2)
    {
        for (int i = 0; i < entries; i++)
        {
            sum = 0;
            j = i + 1;
            c = 0;
            while (c++ < (entries - 1))
            {
                if (j < entries)
                {
                    sum += matrice[j][i];
                }
                else if (j >= entries)
                {
                    sum += matrice[i][j - entries];
                }
                j++;
            }
            S[i] = (sum) / ((float)(nb_noeuds - 2));
        }
    }
    else
    {
        S[0] = matrice[1][0];
    }
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
    float m;
    for (int i = 0; i < (entries - 1); i++)
    {
        for (int j = (i + 1); j < entries; j++)
        {
            if (i == 0 && j == 1)
            {
                m = matrice[j][i] - S[i] - S[j];
                *min_val = m;
                *i_min = i;
                *j_min = j;
            }
            else
            {
                m = matrice[j][i] - S[i] - S[j];
                if (*min_val > m)
                {
                    *min_val = m;
                    *i_min = i;
                    *j_min = j;
                }
            }
        }
    }
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
    List_Noeuds *newList = (List_Noeuds *)malloc(sizeof(List_Noeuds));
    float newDistanceValue;
    float minValue;
    int iMin, jMin;
    int index = 0;
    int ptr = 1;
    float S[list->nb_elements];

    calcul_S(entries, list->nb_elements, S, matrice_distance);
    calcule_pair_Mij(entries, list->nb_elements, S, matrice_distance, &minValue, &iMin, &jMin);
    group_together(list, newList, iMin, jMin);

    float newDistanceMatrix[entries - 1][entries - 1];
    set_new(entries, matrice_distance, newDistanceMatrix, jMin, iMin);

    while (index < entries)
    {
        if (index != iMin && index != jMin)
        {
            if (index >= iMin)
            {
                if (index < jMin)
                {
                    newDistanceValue = (matrice_distance[index][iMin] + matrice_distance[jMin][index] - matrice_distance[jMin][iMin]) / 2.0;
                }
                else if (index >= jMin)
                {
                    newDistanceValue = (matrice_distance[index][iMin] + matrice_distance[index][jMin] - matrice_distance[jMin][iMin]) / 2.0;
                }
            }
            else
            {
                newDistanceValue = (matrice_distance[iMin][index] + matrice_distance[jMin][index] - matrice_distance[jMin][iMin]) / 2.0;
            }
            newDistanceMatrix[ptr][0] = newDistanceValue;
            ptr++;
        }
        index++;
    }

    set_copy(newList->nb_elements, matrice_distance, newDistanceMatrix);

    return newList;
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
    while (nb_noeuds > 1)
    {
        list = fuse_matrice_NJ(list->nb_elements, list, matrice_distance);
        nb_noeuds = get_nb_noeuds(list);
    }

    Arbre a;
    a.tete = list->head->data;
    return a;
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
    parse_file(file_aligne, tab_sequences_aligne);

    float matrice_distance[nb_entries][nb_entries];
    initialise_matrice(nb_entries, matrice_distance);
    fill_distance_matrix(nb_entries, matrice_distance, tab_sequences_aligne);

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

    Arbre a;
    if (Algorithme == 'U')
    {
        printf("Arbre UPGMA construit pour le fichier '%s' :\n", file_aligne);
        a = UPGMA(nb_entries, &list, matrice_distance);
    }
    else
    {
        printf("Arbre NEIGHBOR JOINING construit pour le fichier '%s' :\n", file_aligne);
        a = Neighbor_Joining(nb_entries, &list, matrice_distance);
    }
    afficher_arbre_plat(&a);
    int step = 1;
    char mark = 'l';
    printf("\n");
    new_affichage(a.tete, &step, mark);
    printf("\n");
}
