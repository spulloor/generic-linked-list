#ifndef _SLINKEDLIST
#define _SLINKEDLIST

#include <stdlib.h>
#include <string.h>  // for memcpy

#define ALLOCATE(T, d) (T *)malloc(sizeof(T) * d)

#define ALLOCATE_ELEMENT(T) ALLOCATE(T, 1)

#define DEALLOCATE_NODE(p) \
    free(p->data);         \
    free(p)

#define DEALLOCATE(p) free(p)

/** implementation start here*/

#define INIT_SLLIST_TYPE(T)                                               \
                                                                          \
    typedef struct Node {                                                 \
        T *data;                                                          \
        int size;                                                         \
        struct Node *next;                                                \
    } SLinkedListNode;                                                    \
                                                                          \
    typedef struct SSList {                                               \
        SLinkedListNode *start;                                           \
        SLinkedListNode *end;                                             \
        struct SSList *this;                                              \
        int length;                                                       \
                                                                          \
        SLinkedList *(*init_list)();                                      \
        SLinkedListNode *(*init_node)(T * data, int size);                \
        SLinkedListNode *(*push)(T * data, int size);                     \
        SLinkedListNode *(*push_s)(char *data);                           \
        SLinkedListNode *(*pushv)(T data);                                \
        T *(*pop)(T * buffer);                                            \
        SLinkedList *(*clearl)();                                         \
        SLinkedListNode *(*find_node)(T * data);                          \
        SLinkedListNode *(*find_nodev)(int data);                         \
        SLinkedListNode *(*find_node_by_index)(int index);                \
        int (*present)(T * data);                                         \
        int (*presentv)(int data);                                        \
        void (*reverse)();                                                \
        SLinkedList *(*make_copy)();                                      \
        SLinkedListNode *(*insert_before)(T * data, int index, int size); \
        SLinkedListNode *(*insertb_s)(char *data, int index);             \
        SLinkedListNode *(*insert_beforev)(T data, int index);            \
        SLinkedListNode *(*insert_after)(T * data, int index, int size);  \
        SLinkedListNode *(*inserta_s)(char *data, int index);             \
        SLinkedListNode *(*insert_afterv)(T data, int index);             \
        T *(*remove_node)(int index, T *buffer);                          \
        void (*print_list)(char *format_specifier);                       \
        void (*free_list)();                                              \
                                                                          \
    } SLinkedList;                                                        \
                                                                          \
    SLinkedList *init_list() {                                            \
        SLinkedList *l = ALLOCATE_ELEMENT(SLinkedList);                   \
        l->start = NULL;                                                  \
        l->end = NULL;                                                    \
        l->length = 0;                                                    \
        l->this = l;                                                      \
                                                                          \
        /** assign all the functions to func ptrs in our list struct*/    \
                                                                          \
        l->init_list = init_list;                                         \
        l->init_node = init_node;                                         \
        l->push = push;                                                   \
        l->push_s = push_s;                                               \
        l->pushv = pushv;                                                 \
        l->pop = pop;                                                     \
        l->clearl = clearl;                                               \
        l->find_node = find_node;                                         \
        l->find_nodev = find_nodev;                                       \
        l->find_node_by_index = find_node_by_index;                       \
        l->present = present;                                             \
        l->presentv = presentv;                                           \
        l->reverse = reverse;                                             \
        l->make_copy = make_copy;                                         \
        l->insert_before = insert_before;                                 \
        l->insertb_s = insertb_s;                                         \
        l->insert_beforev = insert_beforev;                               \
        l->insert_after = insert_after;                                   \
        l->inserta_s = inserta_s;                                         \
        l->insert_afterv = insert_afterv;                                 \
        l->remove_node = remove_node;                                     \
        l->print_list = print_list;                                       \
        l->free_list = free_list;                                         \
        return l;                                                         \
    }                                                                     \
                                                                          \
    SLinkedListNode *init_node(T *data, int size) {                       \
        SLinkedListNode *node = ALLOCATE_ELEMENT(SLinkedListNode);        \
        node->data = ALLOCATE(T, size);                                   \
        node->next = NULL;                                                \
        node->size = sizeof(T) * size;                                    \
        memcpy(node->data, data, node->size);                             \
                                                                          \
        return node;                                                      \
    }                                                                     \
    SLinkedListNode *push(SLinkedList *l, T *data, int size) {            \
        SLinkedListNode *node = init_node(data, size);                    \
        if (l->length == 0) {                                             \
            l->start = node;                                              \
        } else {                                                          \
            l->end->next = node;                                          \
            l->end = node;                                                \
        }                                                                 \
        l->length++;                                                      \
        l->end = node;                                                    \
        return node;                                                      \
    }                                                                     \
                                                                          \
    /** only use when init c-string lists */                              \
    SLinkedListNode *push_s(SLinkedList *l, char *data) {                 \
        return push(l, data, strlen(data));                               \
    }                                                                     \
                                                                          \
    SLinkedListNode *pushv(SLinkedList *l, T data) {                      \
        T *buffer = ALLOCATE_ELEMENT(T);                                  \
        *buffer = data;                                                   \
        SLinkedListNode *node = push(l, buffer, 1);                       \
        DEALLOCATE(buffer);                                               \
    }                                                                     \
                                                                          \
    T *pop(SLinkedList *l, T *buffer) {                                   \
        SLinkedListNode *node = l->start;                                 \
        SLinkedListNode *prev_node = NULL;                                \
        for (int i = 1; i < l->length; i++) {                             \
            if (i == l->length - 1) {                                     \
                prev_node = node;                                         \
            }                                                             \
            node = node->next;                                            \
        }                                                                 \
                                                                          \
        if (prev_node) {                                                  \
            prev_node->next = NULL;                                       \
        }                                                                 \
        l->length--;                                                      \
                                                                          \
        if (l->length == 0) {                                             \
            l->start = l->end = NULL;                                     \
        }                                                                 \
        memcpy(buffer, node->data, node->size);                           \
        DEALLOCATE_NODE(node);                                            \
        return buffer;                                                    \
    }                                                                     \
                                                                          \
    SLinkedList *clearl(SLinkedList *l) {                                 \
        SLinkedListNode *temp;                                            \
        int i = 1;                                                        \
        for (SLinkedListNode *node = l->start; node; node = temp, i++) {  \
            temp = node->next;                                            \
            DEALLOCATE_NODE(node);                                        \
        }                                                                 \
                                                                          \
        l->start = l->end = NULL;                                         \
        l->length = 0;                                                    \
        return l;                                                         \
    }                                                                     \
                                                                          \
    SLinkedListNode *find_node(SLinkedList *l, T *data) {                 \
        SLinkedListNode *node = l->start;                                 \
        for (int i = 1; i <= l->length; i++) {                            \
            if (memcmp(node->data, data, node->size) == 0) {              \
                return node;                                              \
            }                                                             \
            node = node->next;                                            \
        }                                                                 \
        return NULL;                                                      \
    }                                                                     \
                                                                          \
    SLinkedListNode *find_nodev(SLinkedList *l, int data) {               \
        T *buffer = ALLOCATE_ELEMENT(int);                                \
        *buffer = data;                                                   \
        SLinkedListNode *node = find_node(l, buffer);                     \
        DEALLOCATE(buffer);                                               \
                                                                          \
        return node;                                                      \
    }                                                                     \
                                                                          \
    SLinkedListNode *find_node_by_index(SLinkedList *l, int index) {      \
        SLinkedListNode *node = l->start;                                 \
        for (int i = 1; i <= l->length; i++) {                            \
            if (i == index) {                                             \
                return node;                                              \
            }                                                             \
            node = node->next;                                            \
        }                                                                 \
        return NULL;                                                      \
    }                                                                     \
    int present(SLinkedList *l, T *data) {                                \
        return find_node(l, data) ? 1 : 0;                                \
    }                                                                     \
                                                                          \
    int presentv(SLinkedList *l, int data) {                              \
        T *buffer = ALLOCATE_ELEMENT(int);                                \
        *buffer = data;                                                   \
        int b = present(l, buffer);                                       \
        DEALLOCATE(buffer);                                               \
                                                                          \
        return b;                                                         \
    }                                                                     \
                                                                          \
    void reverse(SLinkedList *l) {                                        \
        SLinkedListNode *next_node = l->start;                            \
        SLinkedListNode *prev_node = l->start->next;                      \
        next_node->next = NULL;                                           \
        l->end = next_node;                                               \
        for (int i = 2; i <= l->length && prev_node != NULL; i++) {       \
            SLinkedListNode *prev_prev_node = prev_node->next;            \
            prev_node->next = next_node;                                  \
            next_node = prev_node;                                        \
            prev_node = prev_prev_node;                                   \
        }                                                                 \
        l->start = next_node;                                             \
    }                                                                     \
                                                                          \
    SLinkedList *make_copy(SLinkedList *l) {                              \
        SLinkedList *lc = init_list();                                    \
        for (SLinkedListNode *node = l->start; node; node = node->next) { \
            push(lc, node->data, node->size);                             \
        }                                                                 \
                                                                          \
        return lc;                                                        \
    }                                                                     \
                                                                          \
    SLinkedListNode *insert_before(SLinkedList *l, T *data, int index,    \
                                   int size) {                            \
        if (index <= 0) {                                                 \
            return NULL;                                                  \
        }                                                                 \
                                                                          \
        if (index > l->length) {                                          \
            return push(l, data, size);                                   \
        }                                                                 \
                                                                          \
        SLinkedListNode *node = init_node(data, size);                    \
                                                                          \
        SLinkedListNode *prev_node = l->start;                            \
        SLinkedListNode *next_node = prev_node->next;                     \
        for (int i = 1; i <= l->length; i++) {                            \
            if (i == index) {                                             \
                if (i == 1) {                                             \
                    node->next = prev_node;                               \
                    l->start = node;                                      \
                } else {                                                  \
                    prev_node->next = node;                               \
                    node->next = next_node;                               \
                }                                                         \
                break;                                                    \
            }                                                             \
                                                                          \
            if (i > 1) {                                                  \
                prev_node = next_node;                                    \
                next_node = next_node->next;                              \
            }                                                             \
        }                                                                 \
                                                                          \
        l->length++;                                                      \
                                                                          \
        return node;                                                      \
    }                                                                     \
                                                                          \
    /** only use when init c-string lists */                              \
    SLinkedListNode *insertb_s(SLinkedList *l, char *data, int index) {   \
        return insert_before(l, data, index, strlen(data));               \
    }                                                                     \
                                                                          \
    SLinkedListNode *insert_beforev(SLinkedList *l, T data, int index) {  \
        T *buffer = ALLOCATE_ELEMENT(T);                                  \
        *buffer = data;                                                   \
        SLinkedListNode *node = insert_before(l, buffer, index, 1);       \
        DEALLOCATE(buffer);                                               \
                                                                          \
        return node;                                                      \
    }                                                                     \
                                                                          \
    SLinkedListNode *insert_after(SLinkedList *l, T *data, int index,     \
                                  int size) {                             \
        if (index <= 0) {                                                 \
            return NULL;                                                  \
        }                                                                 \
                                                                          \
        if (index > l->length) {                                          \
            return push(l, data, size);                                   \
        }                                                                 \
                                                                          \
        SLinkedListNode *node = init_node(data, size);                    \
                                                                          \
        SLinkedListNode *prev_node = l->start;                            \
        SLinkedListNode *next_node = prev_node->next;                     \
        for (int i = 1; i <= l->length; i++) {                            \
            if (i == index) {                                             \
                node->next = prev_node->next;                             \
                prev_node->next = node;                                   \
                break;                                                    \
            }                                                             \
            prev_node = next_node;                                        \
            next_node = next_node->next;                                  \
        }                                                                 \
                                                                          \
        if (l->length == index) {                                         \
            l->end = node;                                                \
        }                                                                 \
                                                                          \
        l->length++;                                                      \
        return node;                                                      \
    }                                                                     \
                                                                          \
    /** only use when init c-string lists */                              \
    SLinkedListNode *inserta_s(SLinkedList *l, char *data, int index) {   \
        return insert_after(l, data, index, strlen(data));                \
    }                                                                     \
                                                                          \
    SLinkedListNode *insert_afterv(SLinkedList *l, T data, int index) {   \
        T *buffer = ALLOCATE_ELEMENT(T);                                  \
        *buffer = data;                                                   \
        SLinkedListNode *node = insert_after(l, buffer, index, 1);        \
        DEALLOCATE(buffer);                                               \
                                                                          \
        return node;                                                      \
    }                                                                     \
                                                                          \
    T *remove_node(SLinkedList *l, int index, T *buffer) {                \
        if (index > l->length) {                                          \
            return pop(l, buffer);                                        \
        }                                                                 \
        if (index <= 0) {                                                 \
            return NULL;                                                  \
        }                                                                 \
        SLinkedListNode *prev_node = l->start;                            \
        SLinkedListNode *next_node = prev_node->next;                     \
        SLinkedListNode *prev_prev_node = NULL;                           \
        for (int i = 1; i <= l->length; i++) {                            \
            if (i == index) {                                             \
                memcpy(buffer, prev_node->data, prev_node->size);         \
                if (i == 1) {                                             \
                    l->start = next_node;                                 \
                } else if (i == l->length) {                              \
                    prev_prev_node->next = NULL;                          \
                } else {                                                  \
                    prev_prev_node->next = next_node;                     \
                }                                                         \
                DEALLOCATE_NODE(prev_node);                               \
                l->length--;                                              \
                return buffer;                                            \
            }                                                             \
                                                                          \
            prev_prev_node = prev_node;                                   \
            prev_node = next_node;                                        \
            next_node = next_node->next;                                  \
        }                                                                 \
        return NULL;                                                      \
    }                                                                     \
    void print_list(SLinkedList *l, char *format_specifier) {             \
        SLinkedListNode *node = l->start;                                 \
        char buffer[20] = "";                                             \
        char defaults[20] = "|%p->";                                      \
        strcat(buffer, format_specifier);                                 \
        strcat(buffer, defaults);                                         \
        for (int i = 1; i <= l->length; i++) {                            \
            printf(buffer, *(node->data), node);                          \
            if (node->next == NULL) {                                     \
                printf("NULL");                                           \
            }                                                             \
            node = node->next;                                            \
        }                                                                 \
    }                                                                     \
    void free_list(SLinkedList *l) {                                      \
        SLinkedListNode *node = l->start;                                 \
        for (int i = 1; i <= l->length; i++) {                            \
            SLinkedListNode *t = node->next;                              \
            DEALLOCATE_NODE(node);                                        \
            node = t;                                                     \
        }                                                                 \
        DEALLOCATE(l);                                                    \
    }

#endif
