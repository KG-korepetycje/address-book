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


char* to_lower(const char* str) {
    char* lower = strdup(str);  // aby nie modyfikowac oryginalu robimy kopie
    for (int i = 0; lower[i]; i++) {
        lower[i] = tolower(lower[i]);
    }
    return lower;
}


void append(struct element** head, struct contact data, int sort_type) {
    struct element* new = create_element(data);
    if (*head == NULL) {
        *head = new;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        return;
    }

    struct element* current = *head;

    if (sort_type == 0) {
        while(current->next != NULL) {
            current = (*current).next;
        }
        // current to teraz ostatni element listy
        current->next = new;
        new->next = NULL;
        new->prev = current;
    }
    else {
        while(1) {
            char* current_str;
            char* new_str;

            switch (sort_type)
            {
                case 1: {
                    current_str = to_lower((current->data).name);
                    new_str = to_lower((new->data).name);  
                    break;
                }
                case 2: {
                    current_str = to_lower((current->data).surname);
                    new_str = to_lower((new->data).surname); 
                    break;
                }
                case 3: {
                    current_str = to_lower((current->data).group);
                    new_str = to_lower((new->data).group); 
                    break;
                }
                default:
                    break;
            }

            printf("Comparing: %s - %s\n", new_str, current_str);
            if (strcoll(new_str, current_str) >= 0) {
                if (current->next == NULL) {
                    current->next = new;
                    new->next = NULL;
                    new->prev = current;

                    free(current_str);
                    free(new_str);
                    return;
                }
                else {
                    current = (*current).next;
                }
            }
            else {
                if (current->prev == NULL) {
                    // poczatek listy
                    current->prev = new;
                    new->next = current;
                    new->prev = NULL;
                    *head = new;
                }
                else {
                    // srodek listy (ale nie koniec!)
                    current->prev->next = new;
                    new->next = current;
                    new->prev = current->prev;
                    current->prev = new;
                }
                free(current_str);
                free(new_str);
                return;
            }
        }
    }
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
        append(head, data, 0);
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


void sort_list(struct element** head, int sort_type) {
    if (*head == NULL || (*head)->next == NULL) {  // Jesli lista pusta lub ma tylko 1 element to wychodzimy
        return;
    }

    struct element* first_sorted = NULL;
    int counter = 1;

    while((*head)->next != first_sorted) {  // Stop jesli drugi element listy jest na swoim miejscu
        struct element* current = *head;

        while(current->next != NULL && current->next != first_sorted) {  // Sprawdzamy czy PRAWY babelek jest NULLem lub jest juz posortowany
            char* current_str;
            char* next_str;

            switch (sort_type)
            {
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
                    break;
                }
                default:
                    break;
            }

            // printf("Comparing: %s - %s\n", current_str, next_str);

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

    // for (int j = 0; j < (size - 1); j++) {
    //     for (int i = 0; i < (size - 1); i++) {
    //         if (t[i] > t[i + 1]) {
    //             int tmp = t[i + 1];
    //             t[i + 1] = t[i];
    //             t[i] = tmp;
    //         }
    //     }
    // }
}


void remove_by_id(struct element** head, int id) {
    struct element* current = *head;
    int counter = 1;
    while((current != NULL) && (id != counter)) {
        current = current->next;
        counter++;
    }
    if (current == NULL) {
        printf("\nNo such contact (id = %d)!\n", id);
        return;
    }
    if (current->prev == NULL) {
        current->next->prev = NULL;
        *head = current->next;
    }
    else {
        if (current->next == NULL) {
            current->prev->next = NULL;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
    }

    printf("\nSuccessfully removed contact (id = %d)!\n", id);
    free(current);
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
