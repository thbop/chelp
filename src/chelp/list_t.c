/*
* Copyright © 2025 Thbop
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the “Software”), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
* of the Software, and to permit persons to whom the Software is furnished to do
* so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "list_t.h"


void *_qalloc(void *value, size_t size) {
    void *v_ptr = malloc(size);
    memcpy(v_ptr, value, size);
    return v_ptr;
}


// Returns an empty new list
list_t new_list() {
    return (list_t){
        .head = NULL,
        .len  = 0,
    };
}


void *_list_append(list_t *list, void *value) {
    l_node *n = (l_node*)malloc(sizeof(l_node));
    n->value = value;
    n->prev  = 
    n->next  = NULL;

    if (list->head == NULL)
        list->head = n;
    else {
        list->head->prev = n;
        n->next = list->head;
        list->head = n;
    }

    list->len++;
    return value;
}


l_node *_list_find(list_t *list, void *value) {
    list_ptr_foreach(list, n) {
        if ( n->value == value ) return n;
    }
    return NULL;
}

// Removes an element from the list, but does not free its value.
// Instead, it returns the value
void *_list_pop( list_t *list, l_node *popped ) {
    if ( popped == NULL ) return NULL;
    
    if ( popped->prev == NULL ) {
        if ( popped->next == NULL )               // PREV = NEXT = NULL
            list->head = NULL;
        else {                                     // PREV = NULL; NEXT = PTR
            list->head = popped->next;
            list->head->prev = NULL;
        }
    }
    else {
        if ( popped->next == NULL )               // PREV = PTR; NEXT = NULL
            ((l_node*)popped->prev)->next = NULL;
        else {                                     // PREV = PTR; NEXT = PTR
            l_node *prev = popped->prev;
            l_node *next = popped->next;

            prev->next = next;
            next->prev = prev;
        }
    }
    list->len--;
    void *value = popped->value;
    free(popped);
    return value;
}

void _list_remove(list_t *list, l_node *removed) {
    void *value = _list_pop( list, removed );
    if ( value != NULL )
        free(value);
}

// Frees the list, but not its elements
void _list_disband( list_t *list ) {
    l_node *node = list->head;
    l_node *n;
    while (node != NULL) {
        n = node->next;
        free(node);
        node = n;
    }
    *list = new_list();
}

void _list_free(list_t *list) {
    list_ptr_foreach( list, it ) {
        free( it->value );
    }
    _list_disband( list );
}