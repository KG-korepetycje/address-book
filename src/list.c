#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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


void append_from_csv(struct element** head, char file_path[]) {
    FILE* p_file;
    char name[30], surname[30], phone[20], group[50];

    p_file = fopen(file_path, "r");
    if (p_file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fscanf(p_file, "%[^;];%[^;];%[^;];%[^\n]\n", name, surname, phone, group) == 4) {
        struct contact data;
        strcpy(data.name, name);
        strcpy(data.surname, surname);
        strcpy(data.phone, phone);
        strcpy(data.group, group);
        append(head, data);
    }

    fclose(p_file);
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


char* to_lower(const char* str) {
    char* lower = strdup(str);
    for(int i = 0; lower[i]; i++) {
        lower[i] = tolower(lower[i]);
    }
    return lower;
}


void sort_list(struct element** head, int sort_type) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    struct element* first_sorted = NULL;

    while (first_sorted == NULL || first_sorted->prev != *head) {
        struct element* current = *head;

        while(current->next != NULL && current->next != first_sorted) {
            char* current_str;
            char* next_str;
            switch (sort_type) {
                case 1: {
                    current_str = to_lower((current->data).name);
                    next_str = to_lower((current->next->data).name);
                    break;
                }
                case 2: {
                    current_str = to_lower((current->data).surname);
                    next_str = to_lower((current->next->data).surname);
                    break;
                }
                case 3: {
                    current_str = to_lower((current->data).group);
                    next_str = to_lower((current->next->data).group);
                }
                default: {
                    break;
                }
            }
            printf("Comparing: %s vs %s\n", current_str, next_str);

            if (strcoll(current_str, next_str) > 0) {
                if (current->prev == NULL) {
                    current->next->prev = NULL;
                    *head = current->next;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                current->prev = current->next;
                current->next = current->next->next;
                current->prev->next = current;
                if (current->next != NULL) {
                    current->next->prev = current;
                }
            }
            else {
                current = current->next;
            }

            free(current_str);
            free(next_str);
        }
        first_sorted = current;
    }
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
