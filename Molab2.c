#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char nama[69];
    struct Node *next;
};

struct Node *cuy = NULL;

struct Node *createNode(struct Node *node, char *n)
{
    struct Node *new_Node;
    new_Node = (struct Node *)malloc(sizeof(struct Node));
    if (new_Node == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_Node->nama, n);
    new_Node->next = node;
    return new_Node;
}

void display(struct Node *cuy)
{
    int i = 1;
    struct Node *temp = cuy;
    while (temp != NULL)
    {
        printf("Take Medicine #%d: %s\n", i++, temp->nama);
        temp = temp->next;
    }
}

int main()
{
    char obat[50];
    char choise[5];
    int count = 0;
    printf("Sunib Hospital\n");
    printf("===============\n");
    do
    {
        while (1)
        {
            printf("Enter the medicine name [minimum 5 medicines] ('done' to finish): ");
            scanf(" %[^\n]", obat);
            if (strcasecmp("done", obat) == 0)
            {
                if (count < 5)
                {
                    printf("At least 5 medicines are required.\n");
                    continue;
                }
                else
                {
                    break;
                }
            }
            cuy = createNode(cuy, obat);
            printf("Medicine %s is added to the prescription.\n", obat);
            count++;
        }
        printf("Medicine Prescription:\n");
        display(cuy);
        printf("Do you want to continue (yes/no)? ");
        scanf(" %[^\n]", choise);
    } while (strcasecmp(choise, "yes") == 0);
}