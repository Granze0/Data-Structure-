#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
// Brhanselino Satrio Edipurtta
// 2702293922
typedef struct Data
{
    char name[26], Id[6], Des[100], Code[100];
    int age, lvl;
    struct Data *next;
    struct Data *prev;
} Node;

void InsertPatient(Node **head, Node **tail)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *temp = *head;
    int find;

    do
    {
        printf("Input patient name[4-25]: ");
        scanf(" %[^\n]", newNode->name);
    } while (strlen(newNode->name) < 4 || strlen(newNode->name) > 25);
    do
    {
        printf("Input patient age[>= 0]: ");
        scanf("%d", &newNode->age);
    } while (newNode->age < 0);
    do
    {
        find = 0;
        printf("Input patient ID[5]: ");
        scanf(" %s", newNode->Id);
        while (temp != NULL)
        {
            if (strcmp(temp->Id, newNode->Id) == 0)
            {
                find = 1;
            }
            temp = temp->next;
        }
        if (find == 1)
        {
            printf("ID already exist!\n");
        }
    } while (strlen(newNode->Id) != 5 || find == 1);
    do
    {
        printf("Input description: ");
        scanf(" %[^\n]", newNode->Des);
    } while (strlen(newNode->Des) < 6);
    do
    {
        printf("Input code[Red|Yellow|Green]: ");
        scanf(" %s", newNode->Code);
        if (strcmp(newNode->Code, "Red") == 0)
        {
            newNode->lvl = 3;
        }
        else if (strcmp(newNode->Code, "Yellow") == 0)
        {
            newNode->lvl = 2;
        }
        else if (strcmp(newNode->Code, "Green") == 0)
        {
            newNode->lvl = 1;
        }
    } while (strcmp(newNode->Code, "Red") != 0 && strcmp(newNode->Code, "Yellow") != 0 && strcmp(newNode->Code, "Green") != 0);

    printf("\nInsert success !");

    newNode->next = NULL;
    newNode->prev = NULL;

    if (*tail == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else
    {
        if ((*head)->next == NULL && ((*head)->lvl) > (newNode->lvl))
        {
            newNode->prev = *tail;
            (*tail)->next = newNode;
            *tail = newNode;
        }
        else if ((*head)->next == NULL && ((*head)->lvl) < (newNode->lvl))
        {
            newNode->next = *head;
            (*head)->prev = newNode;
            *head = newNode;
        }
        else
        {
            Node *temp = *head;
            while (temp->next != NULL && (temp->next->lvl) >= newNode->lvl)
            {
                temp = temp->next;
            }
            if (temp->next != NULL)
            {
                newNode->next = temp->next;
                newNode->prev = temp;
                temp->next = newNode;
                temp->next->prev = newNode;
            }
            else
            {
                newNode->prev = temp;
                temp->next = newNode;
                *tail = newNode;
            }
        }
    }
}

void View(Node *head)
{
    int i = 1;

    if (head == NULL)
    {
        printf("\nNULL\n");
        return;
    }

    printf("Patient List:\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-25s | %-7s | %-4s | %-35s | %-8s |\n", "No", "Name", "ID", "age", "Description", "Code");
    printf("-------------------------------------------------------------------------------------------------------\n");
    while (head != NULL)
    {
        printf("| %-5d | %-25s | %-7s | %-4d | %-35s | %-8s |\n", i++, head->name, head->Id, head->age, head->Des, head->Code);
        head = head->next;
    }
    printf("-------------------------------------------------------------------------------------------------------\n");
}

void next(Node **lokygskrg)
{
    printf("The next patient is:\n");
    printf("Name        : %s\n", (*lokygskrg)->name);
    printf("age         : %d\n", (*lokygskrg)->age);
    printf("ID          : %s\n", (*lokygskrg)->Id);
    printf("Description : %s\n", (*lokygskrg)->Des);
    printf("Code        : %s\n", (*lokygskrg)->Code);
    *lokygskrg = (*lokygskrg)->next;
}

void /*THIO PUNYA JAJAJAJAJAJAJA*/ freedata(Node **head)
{
    Node *hapus = *head;

    *head = (*head)->next;
    free(hapus);
}

void freeList(Node **head)
{
    Node *current = *head;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main()
{
    Node *head = NULL;
    Node *tail = NULL;
    Node *check = NULL;
    char choise[50];
    do
    {
        printf("\e[1;1H\e[2J");
        printf("Sunib Patient Entry\n");
        printf("===================\n");
        printf("[1] Insert Patient\n");
        printf("[2] View List\n");
        printf("[3] Next Queue\n");
        printf("[4] Exit\n");
        printf(">>> ");
        scanf(" %[^\n]", choise);
        // Pake if else biar user tidak hanya harus memasukkan angka untuk bisa menggunakan menu
        if (strcasecmp(choise, "Insert Patient") == 0 || strcasecmp(choise, "Insert") == 0 || strcasecmp(choise, "Patient") == 0 || strcmp(choise, "1") == 0)
        {
            InsertPatient(&head, &tail);
            check = head;
            printf("\nPress Any Key to Continue . . .");
            while (!kbhit()) // any key
                ;
            getchar();
            system("cls");
        }
        else if (strcasecmp(choise, "View List") == 0 || strcasecmp(choise, "View") == 0 || strcasecmp(choise, "List") == 0 || strcmp(choise, "2") == 0)
        {
            View(head);
            printf("\nPress Any Key to Continue . . .");
            while (!kbhit()) // any key
                ;
            getchar();
            system("cls");
        }
        else if (strcasecmp(choise, "Next Queue") == 0 || strcasecmp(choise, "Next") == 0 || strcasecmp(choise, "Queue") == 0 || strcmp(choise, "3") == 0)
        {
            if (check != NULL)
            {
                next(&check);
                freedata(&head);
            }
            else
                printf("Not Data\n");
            printf("\nPress Any Key to Continue . . .");
            while (!kbhit()) // any key
                ;
            getchar();
            system("cls");
        }
        else if (strcasecmp(choise, "Exit") == 0 || strcmp(choise, "4") == 0)
        {
            printf("Thanks\n");
            break;
        }
        else
        {
            printf("Invalid input\n");
            printf("\nPress Any Key to Continue . . .");
            while (!kbhit()) // any key
                ;
            getchar();
            system("cls");
        }
        // Thio Punya
    } while (strcasecmp(choise, "4") != 0 || strcasecmp(choise, "Exit") != 0);
    freeList(&head);
    return 0;
}