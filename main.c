#include <stdio.h>
#include <assert.h>
#include "slinkedlist.h"

INIT_SLLIST_TYPE(float)

#include "sll.h"

int main()
{
    float a = 56;
    int choice;
    SLinkedList *l = init_list();
    int* buffer = ALLOCATE_ELEMENT(int);
    SLinkedListNode* node = NULL;

    do
    {

        printf("\n\n1.Push\n");
        printf("2.Pop\n");
        printf("3.Find Node\n");
        printf("4.Find Node By Index\n");
        printf("5.Present\n");
        printf("6.Reverse\n");
        printf("7.Insert Before\n");
        printf("8.Insert After\n");
        printf("9.Remove Node\n");
        printf("10.Print List\n");
        printf("11.Exit\n");
        scanf("%d", &choice);

        int n;

        switch (choice)
        {
        case 1:
            printf("How many elements: ");
            scanf("%d", &n);
            while (n-- > 0)
            {
                printf("Enter some data: ");
                scanf("%f", &a);
                pushv(l, a);
            }
            break;
        case 2:
            pop(l, buffer);
            break;
        case 3:
            printf("Enter some data: ");
            scanf("%d", &a);
            node =  find_node(l, &a);
            printf("%d\n", *(node->data));
            break;
        case 4:
            printf("Enter index: ");
            scanf("%d", &a);
            node =  find_node_by_index(l, a);
            printf("%d\n", *(node->data));
            break;
        case 5:
            printf("Enter some data: ");
            scanf("%d", &a);
            push(l, &a, sizeof(int));
            break;
        case 6:
            printf("Enter some data: ");
            scanf("%d", &a);
            push(l, &a, sizeof(int));
            break;
        case 7:
            printf("Enter some data: ");
            scanf("%d", &a);
            push(l, &a, sizeof(int));
            break;
        case 8:
            printf("Enter some data: ");
            scanf("%d", &a);
            push(l, &a, sizeof(int));
            break;
        case 9:
            printf("Enter some data: ");
            scanf("%d", &a);
            push(l, &a, sizeof(int));
            break;

        case 10:
            print_list(l, "%.2f");
            break;

        case 11:

            free_list(l);
            system("exit");
            break;

        default:
            printf("Wrong choice! try again!\n");
            break;
        }


        // if (choice != 10) {
        //     system("clear");
        // }

    } while (choice != 11);

    return 0;
}