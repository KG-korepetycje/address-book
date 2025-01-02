#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    struct element* head = NULL;
    print_list(head);
    // struct element* head = create_element(123);
    struct element* elem = create_element(999);

    append(&head, elem);
    print_list(head);

    printf("Head: %p\n", head);
    printf("Head->data: %d\n", head->data);
    free_list(&head);
    // head = NULL;
    printf("Head: %p\n", head);

    elem = create_element(999);
    append(&head, elem);
    printf("Head: %p\n", head);
    print_list(head);
    return 0;
}
