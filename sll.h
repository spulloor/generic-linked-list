#ifndef _SLINKEDLIST
#define _SLINKEDLIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memcpy

#define ALLOCATE(T, d) \
    (T *)malloc(sizeof(T) * d);

#define ALLOCATE_ELEMENT(T) \
    ALLOCATE(T, 1)

#define DEALLOCATE_NODE(p) \
    free(p->data);         \
    free(p);

#define DEALLOCATE(p) \
    free(p)

/** implementation start here*/

typedef struct Node
{
    int *data;
    int size;
    struct Node *next;
} SLinkedListNode;
typedef struct
{
    SLinkedListNode *start;
    SLinkedListNode *end;
    int length;
} SLinkedList;
SLinkedList *init_list()
{
    SLinkedList *l = ALLOCATE_ELEMENT(SLinkedList);
    l->start = NULL;
    l->end = NULL;
    l->length = 0;
    return l;
}

SLinkedListNode *init_node(int *data, int size)
{
    SLinkedListNode *node = ALLOCATE_ELEMENT(SLinkedListNode);
    node->data = ALLOCATE(int, size);
    node->next = NULL;
    node->size = sizeof(int) * size;
    memcpy(node->data, data, sizeof(int) * size);

    return node;
}
SLinkedListNode *push(SLinkedList *l, int *data, int size)
{
    SLinkedListNode *node = init_node(data, size);
    if (l->length == 0)
    {
        l->start = node;
    }
    else
    {
        l->end->next = node;
        l->end = node;
    }
    l->length++;
    l->end = node;
    return node;
}

SLinkedListNode *pushv(SLinkedList *l, int data)
{
    int *buffer = ALLOCATE_ELEMENT(int);
    *buffer = data;
    // memcpy(buffer, &d, sizeof(int));
    SLinkedListNode *node = push(l, buffer, 1);
    DEALLOCATE(buffer);
}

int *pop(SLinkedList *l, int *buffer)
{
    SLinkedListNode *node = l->start;
    SLinkedListNode *prev_node = NULL;
    for (int i = 1; i < l->length; i++)
    {
        if (i == l->length - 1)
        {
            prev_node = node;
        }
        node = node->next;
    }

    if (prev_node)
    {
        prev_node->next = NULL;
    }
    l->length--;

    if (l->length == 0)
    {
        l->start = l->end = NULL;
    }
    memcpy(buffer, node->data, node->size);
    DEALLOCATE_NODE(node);
    return buffer;
}

SLinkedList *clearl(SLinkedList *l)
{
    SLinkedListNode *temp;
    int i = 1;
    for (SLinkedListNode *node = l->start; node; node = temp, i++)
    {
        temp = node->next;
        DEALLOCATE_NODE(node)
    }

    l->start = l->end = NULL;
    l->length = 0;
    return l;
}

SLinkedListNode *find_node(SLinkedList *l, int *data)
{
    SLinkedListNode *node = l->start;
    for (int i = 1; i <= l->length; i++)
    {
        if (memcmp(node->data, data, node->size) == 0)
        {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

SLinkedListNode *find_nodev(SLinkedList *l, int data)
{
    int *buffer = ALLOCATE_ELEMENT(int);
    *buffer = data;
    // memcpy(buffer, &d, sizeof(int));
    SLinkedListNode *node = find_node(l, buffer);
    DEALLOCATE(buffer);

    return node;
}

SLinkedListNode *find_node_by_index(SLinkedList *l, int index)
{
    SLinkedListNode *node = l->start;
    for (int i = 1; i <= l->length; i++)
    {
        if (i == index)
        {
            return node;
        }
        node = node->next;
    }
    return NULL;
}
int present(SLinkedList *l, int *data)
{
    return find_node(l, data) ? 1 : 0;
}

int presentv(SLinkedList *l, int data)
{
    int *buffer = ALLOCATE_ELEMENT(int);
    *buffer = data;
    int b = present(l, buffer);
    DEALLOCATE(buffer);

    return b;
}

void reverse(SLinkedList *l)
{
    SLinkedListNode *next_node = l->start;
    SLinkedListNode *prev_node = l->start->next;
    next_node->next = NULL;
    l->end = next_node;
    for (int i = 2; i <= l->length && prev_node != NULL; i++)
    {
        SLinkedListNode *prev_prev_node = prev_node->next;
        prev_node->next = next_node;
        next_node = prev_node;
        prev_node = prev_prev_node;
    }
    l->start = next_node;
}

SLinkedList *make_copy(SLinkedList *l)
{

    SLinkedList *lc = init_list();
    for (SLinkedListNode *node = l->start; node; node = node->next)
    {
        push(lc, node->data, node->size);
    }

    return lc;
}

SLinkedListNode *insert_before(SLinkedList *l, int *data, int index, int size)
{

    if (index <= 0)
    {
        return NULL;
    }

    if (index > l->length) {
        return push(l, data, size);
    }
    
    SLinkedListNode *node = init_node(data, size);

    SLinkedListNode *prev_node = l->start;
    SLinkedListNode *next_node = prev_node->next;
    for (int i = 1; i <= l->length; i++)
    {
        if (i == index)
        {
            if (i == 1)
            {
                node->next = prev_node;
                l->start = node;
            }
            else
            {
                prev_node->next = node;
                node->next = next_node;
            }
            break;
        }

        if (i > 1)
        {
            prev_node = next_node;
            next_node = next_node->next;
        }
    }

    l->length++;

    return node;
}

SLinkedListNode *insert_beforev(SLinkedList *l, int data, int index)
{
    int *buffer = ALLOCATE_ELEMENT(int);
    *buffer = data;
    SLinkedListNode *node = insert_before(l, buffer, index, 1);
    DEALLOCATE(buffer);

    return node;
}

SLinkedListNode *insert_after(SLinkedList *l, int *data, int index, int size)
{
    if (index <= 0)
    {
        return NULL;
    }

    if (index > l->length) {
        return push(l, data, size);
    }

    SLinkedListNode *node = init_node(data, size);
    
    SLinkedListNode *prev_node = l->start;
    SLinkedListNode *next_node = prev_node->next;
    for (int i = 1; i <= l->length; i++)
    {
        if (i == index)
        {
            node->next = prev_node->next;
            prev_node->next = node;
            break;
        }
        prev_node = next_node;
        next_node = next_node->next;
    }

    if (l->length == index) {
        l->end = node;
    }

    l->length++;
    return node;
}

SLinkedListNode *insert_afterv(SLinkedList *l, int data, int index)
{
    int *buffer = ALLOCATE_ELEMENT(int);
    *buffer = data;
    SLinkedListNode *node = insert_after(l, buffer, index, 1);
    DEALLOCATE(buffer);

    return node;
}

int *remove_node(SLinkedList *l, int index, int *buffer)
{
    if (index > l->length)
    {
        return pop(l, buffer);
    }
    if (index <= 0)
    {
        return NULL;
    }
    SLinkedListNode *prev_node = l->start;
    SLinkedListNode *next_node = prev_node->next;
    SLinkedListNode *prev_prev_node = NULL;
    for (int i = 1; i <= l->length; i++)
    {
        if (i == index)
        {
            memcpy(buffer, prev_node->data, prev_node->size);
            if (i == 1)
            {
                l->start = next_node;
            }
            else if (i == l->length)
            {
                prev_prev_node->next = NULL;
            }
            else
            {
                prev_prev_node->next = next_node;
            }
            DEALLOCATE_NODE(prev_node);
            l->length--;
            return buffer;
        }

        prev_prev_node = prev_node;
        prev_node = next_node;
        next_node = next_node->next;
    }
    return NULL;
}
void print_list(SLinkedList *l, char *format_specifier)
{
    SLinkedListNode *node = l->start;
    char buffer[20] = "";
    char defaults[20] = "|%p->";
    strcat(buffer, format_specifier);
    strcat(buffer, defaults);
    for (int i = 1; i <= l->length; i++)
    {
        printf(buffer, *(node->data), node);
        if (node->next == NULL)
        {
            printf("NULL");
        }
        node = node->next;
    }
}
void free_list(SLinkedList *l)
{
    SLinkedListNode *node = l->start;
    for (int i = 1; i <= l->length; i++)
    {
        SLinkedListNode *t = node->next;
        DEALLOCATE_NODE(node);
        node = t;
    }
    DEALLOCATE(l);
}

#endif