#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct element* create_element(struct contact data) {
    struct element* p_element = malloc(sizeof(struct element));
    if (p_element != NULL) {
        p_element->data = data;
        p_element->next = NULL;
        p_element->prev = NULL;
    }
    return p_element;
}


void append(struct element** head, struct contact data) {
    struct element* p_element = create_element(data);
    if (*head == NULL) {
        *head = p_element;
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
    current->next = p_element;
    p_element->next = NULL;
    p_element->prev = current;
}


void print_list(struct element* head) {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    struct element* current = head;
    int counter = 1;
    while(current != NULL) {
        printf("\n== %d. CONTACT ==\n", counter);
        printf("Name: %s\n", current->data.name);
        printf("Surname: %s\n", current->data.surname);
        printf("Phone: %s\n", current->data.phone);
        printf("Group: %s\n", current->data.group);
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
