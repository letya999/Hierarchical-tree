#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>

#define SIZE 100

//External
struct tree
{
    int number;
    char field[SIZE];
    struct tree *parent;
    struct tree *brother;
    struct tree *son;
};

typedef struct tree tree;

typedef enum
{
    SON,
    BROTHER,
    ROOTTYPE
} Type;


// Прототипы функций
void creat_node(tree* begin, int k, int num, int newnum, char* data);
void tree_on_screen tree* node, Type T);
tree *poisk_value(tree* begin, int num);
void del_node (tree* begin, int num, int Iter);
void instructions();

void manager(tree *root)
{
    tree *tmp = NULL;
    int n, num, newnum;
    char field[SIZE];
    while (1)
    {
        instructions ();
        scanf("%d", &n);
        switch (n)
        {
            case 1:
                if (root->son == NULL )
                {
                    printf("Введите данные в поле узла: \n");
                    scanf("%s", field);
                    creat_node(root, 2, 0, 1, field);
                    break;
                }
                printf("Вы хотите создать брата(1) или сына(2) ? \n");
                scanf("%d", &n);
                printf("Введите номер узла к которому хотите добавить:\n");
                scanf("%d", &num);
                printf("Введите номер узла: \n");
                scanf("%d", &newnum);
                printf("Введите данные в поле узла: \n");
                scanf("%s", field);
                creat_node(root, n, num, newnum, field);
            break;
            case 2:
                printf("Введите номер удаляемого узла");
                scanf("%d", &n);
                del_node(root, n, 0);
            break;
            case 3:
                printf("Введите требуемый номер: \n");
                scanf("%d", &n);
                tmp = poisk_value (root, n);
                if (tmp == NULL)
                    printf("Ничего не найдено! \n");
                else
                    printf("%s\n", tmp->field);
            break;
            case 4:
                tree_on_screen(root, ROOTTYPE);
            break;
            case 5:
                exit (0);
            break;
        }
    }
}

void instructions()
{
    printf ("Введите для:\n");
    printf ("Добавления узла    (1)\n");
    printf ("Удаления узла        (2)\n");
    printf ("Поиска по дереву  (3)\n");
    printf ("Печати списка       (4)\n");
    printf ("Выхода                   (5)\n");
}

tree* poisk_value(tree *begin, int num)
{
    tree* result = NULL;
    if (begin == NULL)
        return NULL;
    if (begin->number == num)
        return begin;
    if (begin->son != NULL)
        result = poisk_value(begin->son, num);
    if (result != NULL)
        return result;
    if (begin->brother != NULL)
        result = poisk_value(begin->brother, num);
    if (result != NULL)
        return result;
    return NULL;
}

void del_node(tree* begin, int num, int Iter)
{
    tree *node = NULL;
    if (begin == NULL)
       return;
    node = poisk_value(begin, num);
    if (node == NULL)
        return;
    if (node->son != NULL)
        del_node(node->son, node->son->number, Iter + 1);
    if (Iter == 0)
        if (node->brother != NULL)
        {
            node->parent->brother = node->brother;
            node->brother->parent = node->parent;
            free(node);
            return;
        }
    if (node->brother != NULL)
        del_node(node->brother, node->brother->number, Iter + 1);
    if (node->parent == NULL)
        return;
    if (node->parent->son != NULL)
        node->parent->son = NULL;
    else if (node->brother != NULL)
            node->parent->brother = NULL;
    else
        return;
    free(node);
}

void creat_node(tree* begin, int k, int num, int newnum, char* data)
{
    tree *tmp;
    if (poisk_value(begin, num) == NULL)
    {
        printf("Такой номер не существует \n");
        return;
    }
    if (poisk_value(begin, newnum) != NULL)
    {
        printf("Такой новый номер уже имеется в дереве \n");
        return;
    }
    begin = poisk_value(begin, num);
    switch (k)
    {
        case 1:
            tmp = (tree*)malloc(sizeof(tree));
            while (begin->brother != NULL)
                begin = begin->brother;
            tmp->parent = begin;
            tmp->number = newnum;
            tmp->brother = NULL;
            tmp->son = NULL;
            if (data != NULL)
                memcpy(tmp->field, data, SIZE);
            begin->brother = tmp;
        break;
        case 2:
            tmp = malloc(sizeof(tree));
            while (begin->son != NULL)
                begin = begin->son;
            tmp->brother = NULL;
            tmp->number = newnum;
            tmp->parent = begin;
            tmp->son = NULL;
            if (data != NULL)
                memcpy(tmp->field, data, SIZE);
            begin->son = tmp;
        break;
    }
}

void tree_on_screen(tree* node, Type T)
{
    if (node != NULL)
    {
        if (T == SON)
        {
            printf(“Узел %d %s сын узла  %d\n", node->number, node->field, node->parent->number);
        }
        else if (T == BROTHER)
        {
            printf("Узел %d %s брат узла %d\n", node->number,  node->field, node->parent->number);
            printf("%s \n", node->field);
        }
    else
        printf("Корень: каталог записи \n");
    tree_on_screen (node->brother, BROTHER);
    tree_on_screen (node->son, SON);
    }
}

int main()
{
    tree root = {0};
    setlocale (LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    manager(&root);
    getch();
    return 0;
}
