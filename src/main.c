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


int main() {
    struct element* head = NULL;

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
    
    struct contact data;
    strcpy(data.name, "Test name");
    strcpy(data.surname, "Test surname");
    strcpy(data.phone, "Test phone");
    strcpy(data.group, "Test group");
    append(&head, data);

    printf("Before:\n");
    print_list(head);

    sort_list(&head, 3);

    printf("After:\n");
    print_list(head);

    free_list(&head);

    return 0;
}
