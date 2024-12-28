#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct element* create_element(struct contact* contact_data) {
    struct element* new_element = malloc(sizeof(struct element));
    if (new_element != NULL) {
        new_element->data = contact_data;
        new_element->prev = NULL;
        new_element->next = NULL;
    }
    return new_element;
}

void insert_element(struct list* list, struct element* element) {
    if (list->head == NULL || list->tail == NULL) {
        list->head = element;
        list->tail = element;
        return;
    }

    if (element != NULL) {
        list->tail->next = element;
        element->prev = list->tail;
        list->tail = element;
    }
}

void print_list(struct list* list) {
    struct element* current = list->head;
    int counter = 1; 
    while (current != NULL) {
        printf("\n== %d. CONTACT ==\n", counter);
        print_contact(current->data);
        printf("\n");

        current = current->next;
        counter++;
    }
}

void cleanup(struct list* list) {
    struct element* current = list->head;
    
    while (current != NULL) {
        struct element* to_free = current;
        current = current->next;
        free(to_free->data);
        free(to_free);
    }
    
    list->head = NULL;
    list->tail = NULL;
}
