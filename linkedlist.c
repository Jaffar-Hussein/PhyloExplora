#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
} node;

void printlist(node *head)
{
    node *current = head;

    if (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }

    while (current != NULL)
    {
        printf("-%d", current->data);
        current = current->next;
    }

    printf("\n");
}

node *insert(node *head, int data)
{
    node *new_node = malloc(sizeof(node));
    new_node->data = data;
    new_node->next = head;
    // head -> next = NULL;
    head = new_node;
    return head;
}

int main()
{
    node *head = NULL;
    // node n1, n2, n3;
    // n1.data = 1;
    // n2.data = 2;
    // n3.data = 3;

    // head = &n3;
    // n1.next = NULL;
    // n2.next = &n1;

    // n3.next = &n2;
    // node n4;
    // n4.data = 4;
    // n3.next = &n4;
    // n4.next = &n2;

    head = insert(head, 1);
    head = insert(head, 2);
    head = insert(head, 3);

    printlist(head);
}
