#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
// #include "slinkedlist.h"

// INIT_SLLIST_TYPE(int)

#include "sll.h"


void push_elements(SLinkedList* l)
{
    pushv(l, 23);
    pushv(l, 1);
    pushv(l, 5);
    pushv(l, 4);
}

void test_push(SLinkedList* l)
{
    pushv(l, 23);
    assert(*(l->end->data) == 23);
    pushv(l, 67);
    assert(*(l->end->data) == 67);
    pushv(l, 34);
    assert(*(l->end->data) == 34);
    pushv(l, 89);
    assert(*(l->end->data) == 89);
}

void test_pop(SLinkedList* l)
{
    clearl(l);
    push_elements(l);
    int* buffer = ALLOCATE_ELEMENT(int);
    pop(l, buffer);
    assert((*(buffer)) == 4);
    pop(l, buffer);
    assert((*(buffer)) == 5);
    pop(l, buffer);
    assert((*(buffer)) == 1);
    pop(l, buffer);
    assert((*(buffer)) == 23);
}

void test_find_node(SLinkedList* l)
{
    clearl(l);
    push_elements(l);
    SLinkedListNode* node = find_nodev(l, 5);
    assert(*(node->data) == 5);
    assert(*(find_nodev(l, 1)->data) == 1);
    assert(*(find_nodev(l, 23)->data) == 23);
    assert(*(find_nodev(l, 4)->data) == 4);

    node = find_nodev(l, 76);
    assert(node == NULL);
}


void test_find_node_by_index(SLinkedList* l)
{
    clearl(l);
    push_elements(l);
    SLinkedListNode* node = find_node_by_index(l, 1);
    assert(*(node->data) == 23);

    node = find_node_by_index(l, 2);
    assert(*(node->data) == 1);

    node = find_node_by_index(l, 3);
    assert(*(node->data) == 5);

    node = find_node_by_index(l, 4);
    assert(*(node->data) == 4);

    node = find_node_by_index(l, -1);
    assert(node == NULL);

    node = find_node_by_index(l, 5);
    assert(node == NULL);
}


void test_present(SLinkedList* l)
{
    clearl(l);
    push_elements(l);
    int b = presentv(l, 5);
    assert(b);

    b = presentv(l, 23);
    assert(b);

    b = presentv(l, 1);
    assert(b);

    b = presentv(l, 4);
    assert(b);

    b = presentv(l, -1);
    assert(!b);
}

void test_reverse(SLinkedList* l)
{
    clearl(l);
    push_elements(l);

    SLinkedList* lc = make_copy(l);
    int start_value = *(lc->start->data);
    int second_value = *(lc->start->next->data);

    int second_last_value = *(lc->start->next->data);

    reverse(l);

    int last_value;
    pop(l, &last_value);
    assert(last_value == start_value);

    // check second last value
    pop(l, &last_value);
    assert(last_value == second_last_value);

    
}


void test_insert_before(SLinkedList* l)
{
    clearl(l);
    push_elements(l);

    SLinkedListNode* node = insert_beforev(l, 90, 1);
    assert(*(node->data) == *(l->start->data));
    node = insert_beforev(l, 91, 2);
    assert(*(node->data) == *(l->start->next->data));
    node = insert_beforev(l, 92, 3);
    assert(*(node->data) == *(l->start->next->next->data));
    node = insert_beforev(l, 100, 7);
    assert(*(node->data) == *(l->start->next->next->next->next->next->next->data));

    node = insert_beforev(l, 93, 0);
    assert(node == NULL);

    node = insert_beforev(l, 94, 9);
    assert(*(node->data) == *(l->end->data));


    // insert in an empty list
    clearl(l);
    node = insert_beforev(l, 12, -1);
    assert(node == NULL);
    
    clearl(l);
    node = insert_beforev(l, 12, 0);
    assert(node == NULL);

}

void test_insert_after(SLinkedList* l)
{
    clearl(l);
    push_elements(l);

    SLinkedListNode* node = insert_afterv(l, 90, 1);
    assert(*(node->data) == *(l->start->next->data));
    node = insert_afterv(l, 91, 2);
    assert(*(node->data) == *(l->start->next->next->data));
    node = insert_afterv(l, 92, 3);
    assert(*(node->data) == *(l->start->next->next->next->data));
    node = insert_afterv(l, 100, 7);
    assert(*(node->data) == *(l->start->next->next->next->next->next->next->next->data));

    node = insert_afterv(l, 93, 0);
    assert(node == NULL);

    node = insert_afterv(l, 94, 9);
    assert(*(node->data) == *(l->end->data));


    // insert in an empty list
    clearl(l);
    node = insert_afterv(l, 12, -1);
    assert(node == NULL);
    
    clearl(l);
    node = insert_afterv(l, 12, 0);
    assert(node == NULL);

}

void test_remove_node(SLinkedList* l)
{
    clearl(l);
    push_elements(l);

    int a = 0;
    remove_node(l, -1, &a);
    assert(a == 0);

    remove_node(l, 0, &a);
    assert(a == 0);

    remove_node(l, 1, &a);
    assert(a == 23);

    remove_node(l, 1, &a);
    assert(a == 1);

    remove_node(l, 1, &a);
    assert(a == 5);

    remove_node(l, 1, &a);
    assert(a == 4);
    

    clearl(l);
    push_elements(l);

    remove_node(l, 2, &a);
    assert(a == 1);

    remove_node(l, 3, &a);
    assert(a == 4);

    remove_node(l, 100, &a);
    assert(a == 5);
}


int main()
{
    SLinkedList *l = init_list();

    test_push(l);
    test_pop(l);
    test_find_node(l);
    test_find_node_by_index(l);
    test_present(l);
    test_reverse(l);
    test_insert_before(l);
    test_insert_after(l);
    test_remove_node(l);

    free_list(l);
    
    return 0;
}