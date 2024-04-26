
SLinkedList *(*init_list)();                                                                \
                                                                          \
    SLinkedListNode *(*init_node)(T *data, int size);                                                          \
    SLinkedListNode *(*push)(SLinkedList *l, T *data, int size);                                                            \
                                                                          \
    SLinkedListNode *(*push_s)(SLinkedList *l, char *data);                                           \
                                                                          \
    SLinkedListNode *(*pushv)(SLinkedList *l, T data);                                                               \
                                                                          \
    T *(*pop)(SLinkedList *l, T *buffer);                                                                   \
                                                                          \
    SLinkedList *(*clearl)(SLinkedList *l);                                                                 \
                                                                          \
    SLinkedListNode *(*find_node)(SLinkedList *l, T *data);                                                              \
                                                                          \
    SLinkedListNode *(*find_nodev)(SLinkedList *l, int data);                                                                 \
                                                                          \
    SLinkedListNode *(*find_node_by_index)(SLinkedList *l, int index);                                                                  \
    int (*present)(SLinkedList *l, T *data);                                             \
                                                                          \
    int (*presentv)(SLinkedList *l, int data);                                                                  \
                                                                          \
    void (*reverse)(SLinkedList *l);                                                                    \
                                                                          \
    SLinkedList *(*make_copy)(SLinkedList *l);                                                                   \
                                                                          \
    SLinkedListNode *(*insert_before)(SLinkedList *l, T *data, int index,    \
                                   int size);                                                                  \
                                                                          \
    /** only use when init c-string lists */                              \
    SLinkedListNode *(*insertb_s)(SLinkedList *l, char *data, int index);                                           \
                                                                          \
    SLinkedListNode *(*insert_beforev)(SLinkedList *l, T data, int index);                                                             \
                                                                          \
    SLinkedListNode *(*insert_after)(SLinkedList *l, T *data, int index,     \
                                  int size);                                                                 \
                                                                          \
    /** only use when init c-string lists */                              \
    SLinkedListNode *(*inserta_s)(SLinkedList *l, char *data, int index);                           \
                                                                          \
    SLinkedListNode *(*insert_afterv)(SLinkedList *l, T data, int index);                                                                 \
                                                                          \
    T *(*remove_node)(SLinkedList *l, int index, T *buffer);                                                                 \
    void (*print_list)(SLinkedList *l, char *format_specifier);                                                              \
    void (*free_list)(SLinkedList *l);