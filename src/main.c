#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "csv.h"

int main() {
    // struct element* head = NULL;
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
    struct element* head = parse_file_to_list("data/prosta_lista.csv");
    struct contact data;
    strcpy(data.name, "Test name");
    strcpy(data.surname, "Test surname");
    strcpy(data.phone, "Test phone");
    strcpy(data.group, "Test group");
    append(&head, data);
    print_list(head);

    return 0;
}
