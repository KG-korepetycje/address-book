#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct element* create_element(int data) {
    struct element* p_element = malloc(sizeof(struct element));
    if (p_element != NULL) {
        p_element->data = data;
        p_element->next = NULL;
        p_element->prev = NULL;
    }
    return p_element;
}


void append(struct element** head, struct element* element) {
    if (*head == NULL) {
        *head = element;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        return;
    }

    struct element* current = *head;
    while(current->next != NULL) {
        current = (*current).next;
    }
    // current to teraz ostatni element listy
    // (*current).next = element;
    current->next = element;
    element->next = NULL;
    element->prev = current;
}


void print_list(struct element* head) {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    struct element* current = head;
    int counter = 1;
    while(current != NULL) {
        printf("\n== %d. ELEMENT ==\n", counter);
        printf("Data: %d\n", current->data);
        current = current->next;
        // counter = counter + 1;
        counter++;
    }
    printf("\n");
}


void free_list(struct element** head) {
    struct element* current = *head;
    while(current != NULL) {
        struct element* tmp = current->next;
        free(current);
        current = tmp;
    }

    *head = NULL;
}
