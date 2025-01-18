#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
// #include "csv.h"


void bubble_sort() {
    int t[5] = {6, 4, 3, 8, 2};

    printf("Before: [ ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", t[i]);
    }
    printf("]\n");

    int size = 5;
    int counter = 1;

    for (int j = 0; j < (size - 1); j++) {
        for (int i = 0; i < (size - 1 - j); i++) {
            printf("Counter: %d\n", counter);
            counter++;
            if (t[i] > t[i + 1]) {
                int tmp = t[i + 1];
                t[i + 1] = t[i];
                t[i] = tmp;
            }
        }
    }

    printf("After: [ ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", t[i]);
    }
    printf("]\n");
}


void menu(struct element** head) {
    int choice = -1;
    int sort_type = 0;

    while (choice != 0) {
        // printf("\033[H\033[J");  // nie na windowsa
        printf("Adrress book menu:\n");
        printf("[0] Exit\n");
        printf("[1] Append new element\n");
        printf("[2] Append from csv\n");
        printf("[3] Print list\n");
        printf("[4] Sort list\n");
        printf("[5] Remove from list by ID\n");
        printf("\nYour choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 0: {
                return;
            }
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                print_list(*head);
                break;
            }
            case 4: {
                printf("\nSort type selection: ");
                scanf("%d", &sort_type);
                sort_list(head, sort_type);
                break;
            }
            case 5: {
                int id;
                printf("\nContact ID (number from the list): ");
                scanf("%d", &id);
                remove_by_id(head, id);
                break;
            }
            default: {
                printf("Not valid input!\n");
                break;
            }
        }
    }
}


int main() {
    struct element* head = NULL;
    // print_list(head);
    // // struct element* head = create_element(123);
    // struct element* elem = create_element(999);

    // append(&head, elem);
    // print_list(head);

    // printf("Head: %p\n", head);
    // printf("Head->data: %d\n", head->data);
    // free_list(&head);
    // printf("Head: %p\n", head);

    // elem = create_element(999);
    // append(&head, elem);
    // printf("Head: %p\n", head);
    // print_list(head);

    // parse_contact("data/prosta_lista.csv");
    // struct element* head = parse_file_to_list("data/prosta_lista.csv");

    append_from_csv(&head, "data/prosta_lista.csv");
    // // append_from_csv(&head, "data/prosta_lista.csv");
    int sort_type = 1;
    sort_list(&head, sort_type);

    // struct contact data;
    // strcpy(data.name, "Zenon");
    // strcpy(data.surname, "Test surname");
    // strcpy(data.phone, "Test phone");
    // strcpy(data.group, "Test group");
    // append(&head, data, sort_type);

    // // print_list(head);
    // remove_by_id(&head);
    // print_list(head);
    menu(&head);

    free_list(&head);


    // bubble_sort();

    return 0;
}
