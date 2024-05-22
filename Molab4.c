#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Brhanselino Satrio E//
#define data 1007

typedef struct Data
{
    char id[30];
    char name[51];
    char manu[100];
    char reg[11];
    int batch;

    struct Data *next;
} Ngobat;

int count = 1;
Ngobat *table[data];

void /*Brhanselino Satrio E*/ making_id(Ngobat *newStruct, char *reg, char *Man, char *Name)
{
    sprintf(newStruct->id, "M%05d-%s-%c%c", count++, reg, toupper(Man[0]), toupper(Name[0]));
}

int hashfunction(char *id)
{
    int sum = 0;
    for (int i = 0; id[i] != '\0'; i++)
    {
        sum += (int)id[i];
    }
    return sum % data;
}

void displaydata()
{
    int empty = 0;
    for (int i = 0; i < data; i++)
    {
        if (table[i] != NULL)
        {
            empty = 1;
        }
    }

    if (!empty)
    {
        printf("There are no medicine(s) !\n");
    }
    else
    {
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-35s| %-30s| %-30s| %-20s| %-20s|\n", "Medicine ID", "Name", "Manufacturer", "Registration Number", "Batch/Lot Number");
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < data; i++)
        {
            Ngobat *newstruct = table[i];
            while (newstruct != NULL)
            {
                printf("| %-35s| %-30s| %-30s| %-20s| %-20d|\n", newstruct->id, newstruct->name, newstruct->manu, newstruct->reg, newstruct->batch);
                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                newstruct = newstruct->next;
            }
        }
    }
}

void insertdata()
{
    Ngobat *newstruct = (Ngobat *)malloc(sizeof(Ngobat));
    int temu;

    do
    {
        printf("Input Medicine Name[5-50][unique]: ");
        scanf(" %[^\n]", newstruct->name);
        temu = 0;
        for (int i = 0; i < data; i++)
        {
            Ngobat *temp = table[i];
            while (temp != NULL)
            {
                if (strcmp(temp->name, newstruct->name) == 0)
                {
                    temu = 1;
                }
                temp = temp->next;
            }
        }
        if (temu == 1)
        {
            printf("Medicine name is already exist.\n");
        }
    } while (strlen(newstruct->name) < 5 || strlen(newstruct->name) > 50 || temu == 1);

    do /*Brhanselino Satrio E*/
    {
        printf("Input Manufacturer Name[3-25][end with Ltd.]: ");
        scanf(" %[^\n]", newstruct->manu);
    } while (strlen(newstruct->manu) < 3 || strlen(newstruct->manu) > 25 || strcmp(newstruct->manu + strlen(newstruct->manu) - 4, "Ltd.") != 0);

    do
    {
        printf("Input Registration No.[10 digit][numeric]: ");
        scanf(" %[^\n]", newstruct->reg);
        temu = 0;
        for (int i = 0; i < strlen(newstruct->reg); i++)
        {
            if (newstruct->reg[i] < '0' || newstruct->reg[i] > '9')
            {
                temu = 1;
            }
        }
    } while (strlen(newstruct->reg) != 10 || temu == 1);

    do
    {
        printf("Input Batch/Lot[>= 16][Number]: ");
        scanf("%d", &newstruct->batch);
    } while (!(newstruct->batch >= 16));

    making_id(newstruct, newstruct->reg, newstruct->manu, newstruct->name);
    int key = hashfunction(newstruct->id);
    printf("Index : %d\n", key);

    if (table[key] == NULL)
    {
        table[key] = newstruct;
        table[key]->next = NULL;
        printf("Insert Medicine Success!\n");
    }
    else
    {
        Ngobat *ptr = table[key];
        while (ptr->next != NULL)
            ptr = ptr->next;

        ptr->next = newstruct;
        printf("Insert Medicine Success!\n");
    }
    newstruct->next = NULL;
    printf("\nMedicine ID: %s\n", newstruct->id);
}

void removedrugs()
{
    char choise2[21];
    char y;
    printf("Input Medicine ID to delete: ");
    scanf(" %[^\n]", choise2);
    int key = hashfunction(choise2);

    Ngobat *ptr = table[key];
    Ngobat *prev = NULL;

    while (ptr != NULL)
    {
        if (strcmp(ptr->id, choise2) == 0)
        {
            printf("\nMedicine ID: %s\n", ptr->id);
            printf("Medicine Name: %s\n", ptr->name);
            printf("Manufacturer: %s\n", ptr->manu);
            printf("Registration Number: %s\n", ptr->reg);
            printf("Lot Number/Batch: %d\n", ptr->batch);

            char confirm;
            printf("Are you sure [y/n]? ");
            scanf(" %c", &confirm);
            getchar();

            if (confirm == 'y')
            {
                if (prev == NULL)
                {
                    table[key] = ptr->next;
                }
                else
                {
                    prev->next = ptr->next;
                }
                free(ptr);
                printf("Medicine deleted!\n");
            }
            else if (confirm == 'n')
            {
                printf("Delete cancelled.\n");
            }
            else
            {
                printf("Invalid input. Deletion cancelled.\n");
            }

            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }

    printf("Medicine not found!\n");
}

void data_be_gone()
{
    Ngobat *newstruct = table[data];
    Ngobat *next;

    for (int i = 0; i < data; i++)
    {
        while (newstruct != NULL)
        {
            next = newstruct->next;
            free(newstruct);
            newstruct = next;
        }
    }
}

int main()
{
    for (int i = 0; i < data; i++)
    {
        table[i] = NULL;
    }

    int choise;
    do
    {
        system("cls");
        printf("Sunib Hospital\n");
        printf("==============\n");
        printf("1. View Medicine\n");
        printf("2. Insert Medicine\n");
        printf("3. Remove Medicine\n");
        printf("4. Exit\n");
        printf(">> ");
        scanf("%d", &choise);
        switch (choise)
        {
        case 1:
            displaydata();
            printf("\nPress Enter Key to Continue . . .");
            getchar();
            while (getchar() != '\n')
                ;
            break;
        case 2:
            insertdata();
            printf("\nPress Enter Key to Continue . . .");
            getchar();
            while (getchar() != '\n')
                ;
            break;
        case 3:
            removedrugs();
            printf("\nPress Enter Key to Continue . . .");
            getchar();
            break;
        default:
            printf("Invalid input. Please try again.\n");
            printf("\nPress Enter Key to Continue . . .");
            getchar();
            while (getchar() != '\n')
                ;
            break;
        }
    } while (choise != 4);
    data_be_gone();
}
