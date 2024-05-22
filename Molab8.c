// Brhanselino Satrio Edipurtta
// 2702293922
// LA20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

void clearTerminal()
{
    int jenisOS;
#if _WIN32
    jenisOS = 1;
#elif __APPLE__
    jenisOS = 2;
#elif __linux__
    jenisOS = 3;
#elif __unix__
    jenisOS = 4;
#else
    jenisOS = 5;
#endif

    if (jenisOS == 1)
    {
        system("cls");
    }
    else if (jenisOS == 2 || jenisOS == 3 || jenisOS == 4)
    {
        system("clear");
    }
}

typedef struct data
{
    char gname[26];
    char gtype[26];
    int gstock;
    int height;
    struct data *left;
    struct data *right;
} avl;

avl *oyot = NULL;

int height(avl *N)
{
    if (N == NULL)
    {
        return 0;
    }
    return N->height;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

int getBalance(avl *N)
{
    if (N == NULL)
    {
        return 0;
    }
    return height(N->left) - height(N->right);
}

avl *search(avl *nod, char *key)
{
    if (nod == NULL || strcmp(nod->gname, key) == 0)
    {
        return nod;
    }

    if (strcmp(nod->gname, key) > 0)
    {
        if (nod->left == NULL)
        {
            return nod;
        }
        else
            return search(nod->left, key);
    }
    else
    {
        if (nod->right == NULL)
        {
            return nod;
        }
        else
            return search(nod->right, key);
    }
}

avl *newNode(char *a)
{
    avl *node = (avl *)malloc(sizeof(avl));
    strcpy(node->gname, a);
    do
    {
        printf("Input type[Action][RPG][Adventure][Card Game]: ");
        scanf(" %[^\n]", node->gtype);
    } while (strcmp(node->gtype, "Action") != 0 && strcmp(node->gtype, "Adventure") != 0 && strcmp(node->gtype, "RPG") != 0 && strcmp(node->gtype, "Card Game") != 0);
    do
    {
        printf("Input stock[>= 1]: ");
        scanf("%d", &node->gstock);
    } while (node->gstock < 1);
    node->left = node->right = NULL;
    node->height = 1;
    printf("Insert success !\n");
    return (node);
}

avl *rightRotate(avl *y)
{
    avl *x = y->left;
    avl *z = x->right;

    x->right = y;
    y->left = z;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

avl *leftRotate(avl *y)
{
    avl *x = y->right;
    avl *z = x->left;

    x->left = y;
    y->right = z;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

avl *insert_data(avl *node, char *key)
{
    if (node == NULL)
    {
        return (newNode(key));
    }

    if (strcmp(node->gname, key) > 0)
    {
        node->left = insert_data(node->left, key);
    }
    else if (strcmp(node->gname, key) < 0)
    {
        node->right = insert_data(node->right, key);
    }
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && strcmp(node->left->gname, key) > 0)
        return rightRotate(node);

    if (balance < -1 && strcmp(node->right->gname, key) < 0)
        return leftRotate(node);

    if (balance > 1 && strcmp(node->left->gname, key) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && strcmp(node->right->gname, key) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void insert()
{
    char in_title[26];
    avl *find;

    do
    {
        printf("Input game title[5-25][unique]: ");
        scanf(" %[^\n]", in_title);
        find = search(oyot, in_title);
        if (find != NULL && strcmp(find->gname, in_title) == 0)
        {
            printf("Game title already exists. Please enter a unique title.\n");
            printf("\n");
            printf("-------------------------------------------------------------\n");
            printf("| %-25s | %-13s | %-13s |\n", "Game Title", "Game Genre", "Game Stock");
            printf("-------------------------------------------------------------\n");
            printf("| %-25s | %-13s | %-13d |\n", find->gname, find->gtype, find->gstock);
            printf("-------------------------------------------------------------\n");
            return;
        }
    } while (strlen(in_title) < 5 || strlen(in_title) > 25 || (find != NULL && strcmp(find->gname, in_title) == 0));

    oyot = insert_data(oyot, in_title);
}

void printTree(avl *lumpia)
{
    if (lumpia->left != NULL)
    {
        printTree(lumpia->left);
    }
    printf("| %-25s | %-13s | %-13d |\n", lumpia->gname, lumpia->gtype, lumpia->gstock);
    printf("-------------------------------------------------------------\n");
    if (lumpia->right != NULL)
    {
        printTree(lumpia->right);
    }
}

void view_game()
{
    if (oyot != NULL)
    {
        printf("\nWarehouse List");
        printf("\n");
        printf("-------------------------------------------------------------\n");
        printf("| %-25s | %-13s | %-13s |\n", "Game Title", "Game Genre", "Game Stock");
        printf("-------------------------------------------------------------\n");
        printTree(oyot);
    }
    else
    {
        printf("Werehouse is empty !\n");
        return;
    }
}

avl *minValueNode(avl *node)
{
    avl *current = node;

    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

avl *delete_oyot(avl *root, char *key)
{

    if (root == NULL)
    {
        return root;
    }

    if (strcmp(root->gname, key) < 0)
    {
        root->left = delete_oyot(root->left, key);
    }
    else if (strcmp(root->gname, key) > 0)
    {
        root->right = delete_oyot(root->right, key);
    }
    else
    {

        if ((root->left == NULL) || (root->right == NULL))
        {
            avl *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                root = temp;

            printf("%s is removed from the warehouse\n", temp->gname);
            free(temp);
        }
        else
        {
            avl *temp = minValueNode(root->right);
            root = temp;
            root->right = delete_oyot(root->right, temp->gname);
        }
    }

    if (root == NULL)
        {return root;}

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        {return rightRotate(root);}

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        {return leftRotate(root);}

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void update_stock()
{
    avl *find;
    char key[26];
    char ini[7];
    int tanduk;

    printf("Input game title: ");
    scanf(" %[^\n]", key);
    find = search(oyot, key);
    if (find == NULL || strcmp(find->gname, key) != 0)
    {
        printf("Data not found !\n");
        return;
    }
    printf("Current stock: %d\n", find->gstock);
    do
    {
        printf("\nInput update type[add|remove][case insensitive]: ");
        scanf(" %[^\n]", ini);
    } while (strcasecmp(ini, "add") != 0 && strcasecmp(ini, "remove") != 0);

    if (strcasecmp(ini, "add") == 0)
    {
        do
        {
            printf("Input stock to add[>= 1]: ");
            scanf("%d", &tanduk);
        } while (tanduk < 1);

        find->gstock += tanduk;
        printf("\nData update successfully !\n");
    }
    else if (strcasecmp(ini, "remove") == 0)
    {
        if (find->gstock == 1)
        {
            do
            {
                printf("Input stock to remove[Only 1 left]: ");
                scanf("%d", &tanduk);
            } while (find->gstock < tanduk);
            find->gstock -= tanduk;
            printf("\nData update successfully !\n");
            if (find->gstock == 0)
            {
                oyot = delete_oyot(oyot, key);
            }
        }
        else
        {
            do
            {
                printf("Input stock to remove[1-%d]: ", find->gstock);
                scanf("%d", &tanduk);
            } while (find->gstock < tanduk);
            find->gstock -= tanduk;
            printf("\nData update successfully !\n");
            if (find->gstock == 0)
            {
                oyot = delete_oyot(oyot, key);
            }
        }
    }
}

void clear_Tree(avl *root)
{
    if (root != NULL)
    {
        clear_Tree(root->left);
        clear_Tree(root->right);
        free(root);
    }
}

int main()
{
    int choise;
    do
    {
        system("cls");
        printf("Bluejack GShop\n");
        printf("===============\n");
        printf("1. Insert Game\n");
        printf("2. View Game\n");
        printf("3. Update Stock\n");
        printf("4. Exit\n");
        printf(">> ");
        scanf("%d", &choise);

        switch (choise)
        {
        case 1:
            insert();
            printf("\nPress Enter Key to Continue . . .");
            getchar();
            while (getchar() != '\n')
                ;
            break;
        case 2:
            view_game();
            printf("\nPress Enter Key to Continue . . .");
            getchar();
            while (getchar() != '\n')
                ;
            break;
        case 3:
            update_stock();
            printf("\nPress Enter Key to Continue . . .");
            getchar();
            while (getchar() != '\n')
                ;
            break;
        default:
            break;
        }
    } while (choise != 4);

    clear_Tree(oyot);
    oyot = NULL;

    return 0;
}
// Brhanselino Satrio Edipurtta
// 2702293922
// LA20