// #include <stdio.h>
// // #include "utils.h"
// typedef struct Noeud
// {
//     char *valeur;
//     struct Noeud *suivant_left;
//     struct Noeud *suivant_right;
//     int nb_noeud;
// } Noeud;

// typedef struct Element
// {
//     struct Element *next;
//     Noeud *data;
// } Element;

// typedef struct List_Noeuds
// {
//     Element *head;
//     int nb_elements;
// } List_Noeuds;

// typedef struct Arbre
// {
//     Noeud *tete;
// } Arbre;
// // Adds node

// /*

// */
// void add_Noeud(List_Noeuds *list, Noeud *n)
// {
//     Element *temp = get_element(list, get_nb_noeuds(list) - 1);
//     Element *to_add = (Element *)malloc(sizeof(Element));
//     to_add->next = NULL;
//     to_add->data = n;
//     temp->next = to_add;

//     list->nb_elements++;
// }
// // Afficher Arbre plat

// /*
// Input : pointeur sur un arbre
// Output : None
// Main : procedure qui affiche un arbre (d'une maniere plate)
// */
// void afficher_arbre_plat(Arbre *a)
// {
//     Noeud *e = a->tete;
//     printf("\n");
//     afficher_elem_plat(e);
//     printf("\n");
// }
// // UPGMA function

// Arbre UPGMA(int entries, List_Noeuds *list, float matrice_distance[][entries])
// {

//     int nb_noeuds = get_nb_noeuds(list);
//     while (nb_noeuds > 1)
//     {
//         list = fuse_matrice_upgma(entries, list, matrice_distance);
//         nb_noeuds = get_nb_noeuds(list);
//     }

//     Arbre a;
//     a.tete = list->head->data;

//     return a;
// }

// void show_tree(char *file_aligne, char Algorithme)
// {

//     int nb_entries = get_number_entries(file_aligne);
//     Sequence tab_sequences_aligne[nb_entries];
//     parse_file(file_aligne, tab_sequences_aligne);
//     // // show the sequences
//     // for (int i = 0; i < nb_entries; i++) {
//     //     printf("Sequence %d : %s\n", i + 1, tab_sequences_aligne[i].seq);
//     // }
//     float matrice_distance[nb_entries][nb_entries];
//     initialise_matrice(nb_entries, matrice_distance);
//     fill_distance_matrix(nb_entries, matrice_distance, tab_sequences_aligne);

//     // for (int i = 0; i < nb_entries; i++) {
//     //     for (int j = 0; j < nb_entries; j++) {
//     //         printf("%f ", matrice_distance[i][j]);
//     //     }
//     // }
//     List_Noeuds list;
//     list.head = NULL;
//     Noeud *n = new_noeud();
//     n->valeur = tab_sequences_aligne[0].ID;

//     Element *temp = (Element *)malloc(sizeof(Element));
//     temp->next = NULL;
//     temp->data = n;
//     list.head = temp;
//     list.nb_elements = 1;

//     for (int i = 1; i < nb_entries; i++)
//     {
//         Noeud *n = new_noeud();
//         n->valeur = tab_sequences_aligne[i].ID;
//         add_Noeud(&list, n);
//     }

//     Arbre a;
//     if (Algorithme == 'U')
//     {
//         printf("Arbre UPGMA construit pour le fichier '%s' :\n", file_aligne);
//         a = UPGMA(nb_entries, &list, matrice_distance);
//     }
//     // else
//     // {
//     //     printf("Arbre NEIGHBOR JOINING construit pour le fichier '%s' :\n", file_aligne);
//     //     a = Neighbor_Joining(nb_entries, &list, matrice_distance);
//     // }
//     afficher_arbre_plat(&a);
// }
// int main()
// {
//     char* file_aligne = "cat_dna_aligne.fasta";
//     printf("----------------");
//     printf("UPGMA");
//     printf("----------------\n");
//     show_tree(file_aligne, 'U');
// }


// // List_Noeuds
// //   /    \
// // head  nb_elements = 3
// //   |
// // Element
// //  /     \
// // next   data (Noeud)
// //   |
// // Element
// //  /     \
// // next   data (Noeud)
// //   |
// // Element
// //  /     \
// // NULL   data (Noeud)