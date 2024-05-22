#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
// Brhanselino Satrio Edipurtta
// 2702293922
typedef struct Medicine
{
    int id;
    char name[51];
    int price;
    int quanttit;
} obat;

typedef struct tree
{
    int visit;
    char phoneNum[15];
    char name[26];
    char email[21];

    struct tree *left;
    struct tree *right;
} data;

data *oyot = NULL;
obat tombo[5] = {
    {1, "Pracetamol", 5000},
    {2, "Diabet", 7000},
    {3, "Oralit", 3500},
    {4, "Paratusin", 5500},
    {5, "OB Herbal", 6000}};

void Order()
{
    char yon;
    int demeks, aowkowakokafeowkoawekoafweo, total = 0;
    printf("----------------------------------\n");
    printf("| %-2s | %-15s | %-7s |\n", "No", "Medicine", "Price");
    printf("----------------------------------\n");
    for (int i = 0; i < 5; i++)
    {
        printf("| %-2d | %-15s | %-7d |\n", tombo[i].id, tombo[i].name, tombo[i].price);
    }
    printf("----------------------------------\n");
    do
    {
        do
        {
            printf("Input Medicine[1-5]: ");
            scanf("%d", &demeks);
        } while (demeks < 1 || demeks > 5);

        do
        {
            printf("Input Quantity[>=1]: ");
            scanf("%d", &aowkowakokafeowkoawekoafweo);
        } while (aowkowakokafeowkoawekoafweo < 1);

        for (int i = 0; i < 5; i++)
        {
            if (tombo[i].id == demeks)
            {
                tombo[i].quanttit += aowkowakokafeowkoawekoafweo;
            }
        }

        total += tombo[demeks - 1].price * aowkowakokafeowkoawekoafweo;

        printf("Do you want to buy other medicine?[y/n]: ");
        scanf(" %c", &yon);

    } while (yon == 'y');

    printf("Order summary:\n");

    for (int i = 0; i < 5; i++)
    {
        if (tombo[i].quanttit > 0)
        {
            printf("%-15s          - %dx = %d\n", tombo[i].name, tombo[i].quanttit, tombo[i].price * tombo[i].quanttit);
        }
    }
    printf("Total: %d\n", total);

    for (int i = 0; i < 5; i++)
    {
        if (tombo[i].quanttit > 0)
        {
            tombo[i].quanttit = 0;
        }
    }
}

data *insertoyot(data *oyot, data *neW)
{
    if (oyot == NULL)
    {
        return neW;
    }
    else if (strcmp(oyot->phoneNum, neW->phoneNum) > 0)
    {
        oyot->left = insertoyot(oyot->left, neW);
    }
    else
    {
        oyot->right = insertoyot(oyot->right, neW);
    }
    // Brhanselino Satrio Edipurtta
    // 2702293922
    return oyot;
}

data *search_oyot(data *oyot, char *key)
{
    if (oyot == NULL || strcmp(oyot->phoneNum, key) == 0)
    {
        return oyot;
    }
    else if (strcmp(oyot->phoneNum, key) > 0)
    {
        if (oyot->left == NULL)
        {
            return oyot;
        }
        else
            return search_oyot(oyot->left, key);
    }
    else
    {
        if (oyot->right == NULL)
        {
            return oyot;
        }
        else
            return search_oyot(oyot->right, key);
    }
}

void input_coy()
{
    char nohp[15], yon;
    int temu;
    do
    {
        printf("Input phone number[13][numeric]: ");
        scanf(" %[^\n]", nohp);
        temu = 0;
        for (int i = 0; i < strlen(nohp); i++)
        {
            if (nohp[i] < '0' || nohp[i] > '9')
            {
                temu = 1;
            }
        }
    } while (strlen(nohp) < 10 || strlen(nohp) > 13 || temu == 1);

    data *oyothsl = search_oyot(oyot, nohp);

    if (oyothsl == NULL || strcmp(oyothsl->phoneNum, nohp) != 0)
    {
        printf("Do you want to join membership?[y/n]: ");
        scanf(" %c", &yon);
        if (yon == 'y')
        {
            data *newStruct = (data *)malloc(sizeof(data));
            strcpy(newStruct->phoneNum, nohp);
            newStruct->right = NULL;
            newStruct->left = NULL;
            do
            {
                printf("Input name [5-25] [Mr.   /Mrs.   ]: ");
                scanf(" %[^\n]", newStruct->name);
            } while (strncmp(newStruct->name, "Mr.", 3) != 0 && strncmp(newStruct->name, "Mrs.", 4) != 0);

            do
            {
                printf("Input email[10-20][email format]: ");
                scanf(" %[^\n]", newStruct->email);
                temu = 0;
                for (int i = 0; i < strlen(newStruct->email); i++)
                {
                    if (newStruct->email[i] == '@')
                    {
                        temu = 1;
                        break;
                    }
                }
            } while (temu == 0 || (strlen(newStruct->email) < 10 || strlen(newStruct->email) > 20) || (strcmp(newStruct->email + strlen(newStruct->email) - 6, ".co.id") != 0 && strcmp(newStruct->email + strlen(newStruct->email) - 4, ".com") != 0));
            // ((temu == 0 && (strcmp(newStruct->email + strlen(newStruct->email) - 6, ".co.id") != 0 || strcmp(newStruct->email + strlen(newStruct->email) - 4, ".com") != 0))  || strlen(newStruct->email) < 10 || strlen(newStruct->email) > 20);
            newStruct->visit = 1;
            oyot = insertoyot(oyot, newStruct);
            // system("cls");
            printf("\n\nNumber of visits : %d\n", newStruct->visit);
        }
    }
    else
    {
        oyothsl->visit++;
        printf("\n\nNumber of visits: %d\n", oyothsl->visit);
    }
    Order();
}

void view_inorder(data *oyot)
{
    if (oyot != NULL)
    {
        if (oyot->left != NULL)
        {
            view_inorder(oyot->left);
        }
        printf("| %-25s | %-17s | %-21s | %-7d |\n", oyot->name, oyot->phoneNum, oyot->email, oyot->visit);
        printf("-----------------------------------------------------------------------------------\n");
        if (oyot->right != NULL)
        {
            view_inorder(oyot->right);
        }
    }
}
// Brhanselino Satrio Edipurtta
// 2702293922
void view()
{
    if (oyot == NULL)
    {
        printf("There is no data\n");
        return;
    }
    printf("-----------------------------------------------------------------------------------\n");
    printf("| %-25s | %-17s | %-21s | %-7s |\n", "Name", "Phone Number", "Email", "Visit");
    printf("-----------------------------------------------------------------------------------\n");
    view_inorder(oyot);
}

void remove_oyot(data **oyot, char *key)
{
    if ((*oyot) == NULL)
    {
        printf("Phone number not found\n");
    }
    else if (strcmp((*oyot)->phoneNum, key) > 0)
    {
        remove_oyot(&(*oyot)->left, key);
    }
    else if (strcmp((*oyot)->phoneNum, key) < 0)
    {
        remove_oyot(&(*oyot)->right, key);
    }

    else if ((*oyot)->left == NULL && (*oyot)->right == NULL)
    {
        free(*oyot);
        *oyot = NULL;
        printf("\nDelete success\n\n");
    }
    else if ((*oyot)->left == NULL)
    {
        data *temp = *oyot;
        *oyot = (*oyot)->right;
        free(temp);
        printf("\nDelete success\n\n");
    }
    else if ((*oyot)->right == NULL)
    {
        data *temp = *oyot;
        *oyot = (*oyot)->left;
        free(temp);
        printf("\nDelete success\n\n");
    }
    else
    {
        data *temp = (*oyot)->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        strcpy((*oyot)->phoneNum, temp->phoneNum);
        strcpy((*oyot)->name, temp->name);
        strcpy((*oyot)->email, temp->email);
        (*oyot)->visit = temp->visit;
        remove_oyot(&(*oyot)->right, temp->phoneNum);
    }

    // data *temp = *oyot;
    // data *parent = NULL;
    // while (temp != NULL && strcmp(temp->phoneNum, key) != 0)
    // {
    //     parent = temp;
    //     if (strcmp(temp->phoneNum, key) > 0)
    //     {
    //         temp = temp->left;
    //     }
    //     else
    //     {
    //         temp = temp->right;
    //     }
    // }

    // if (temp == NULL)
    // {
    //     printf("Data not found\n");
    // }
    // else
    // {
    //     if (temp->left == NULL && temp->right == NULL)
    //     {
    //         if (parent == NULL)
    //         {
    //             *oyot = NULL;
    //         }
    //         else if (parent->left == temp)
    //         {
    //             parent->left = NULL;
    //         }
    //         else
    //         {
    //             parent->right = NULL;
    //         }
    //         free(temp);
    //     }
    //     else if (temp->left == NULL)
    //     {
    //         if (parent == NULL)
    //         {
    //             *oyot = temp->right;
    //         }
    //         else if (parent->left == temp)
    //         {
    //             parent->left = temp->right;
    //         }
    //         else
    //         {
    //             parent->right = temp->right;
    //         }
    //         free(temp);
    //     }
    //     else if (temp->right == NULL)
    //     {
    //         if (parent == NULL)
    //         {
    //             *oyot = temp->left;
    //         }
    //         else if (parent->left == temp)
    //         {
    //             parent->left = temp->left;
    //         }
    //         else
    //         {
    //             parent->right = temp->left;
    //         }
    //         free(temp);
    //     }
    //     else
    //     {
    //         data *temp2 = temp->right;
    //         data *parent2 = temp;
    //         while (temp2->left != NULL)
    //         {
    //             parent2 = temp2;
    //             temp2 = temp2->left;
    //         }
    //         strcpy(temp->phoneNum, temp2->phoneNum);
    //         strcpy(temp->name, temp2->name);
    //         strcpy(temp->email, temp2->email);
    //         temp->visit = temp2->visit;
    //         if (parent2->left == temp2)
    //         {
    //             parent2->left = temp2->right;
    //         }
    //         else
    //         {
    //             parent2->right = temp2->right;
    //         }
    //         free(temp2);
    //     }
    // }
}

void Remove()
{
    char nohp[15];
    int temu;

    if (oyot == NULL)
    {
        printf("There is no data\n");
        return;
    }
    else
    {
        printf("Input phone number[13][numeric]: ");
        scanf(" %[^\n]", nohp);
        remove_oyot(&oyot, nohp);
    }
}

void clear_Tree(data *oyot)
{
    if (oyot != NULL)
    {
        clear_Tree(oyot->left);
        clear_Tree(oyot->right);
        free(oyot);
    }
}

// Brhanselino Satrio Edipurtta
// 2702293922
int main()
{
    int choise;
    do
    {
        system("cls");
        printf("Sunib Pharmacy\n");
        printf("=====================\n");
        printf("1. Process Order\n");
        printf("2. View All Customer\n");
        printf("3. Remove Customer\n");
        printf("4. Exit\n");
        printf(">> ");
        scanf("%d", &choise);
        switch (choise)
        {
        case 1:
            input_coy();
            printf("Press enter to continue...\n");
            getch();
            break;
        case 2:
            view();
            printf("Press enter to continue...\n");
            getch();
            break;
        case 3:
            Remove();
            printf("Press enter to continue...\n");
            getch();
            break;
        default:
            break;
        }
    } while (choise != 4);
    clear_Tree(oyot);
    system("cls");
    printf("\nThank you for running this program\n\n");
    return 0;
}