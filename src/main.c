#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    struct element* head = create_element(123);
    struct element* second = create_element(999);

    append(head, second);
    print_list(head);

    printf("Head: %p\n", head);
    printf("Head->data: %d\n", head->data);
    free_list(head);
    head = NULL;
    printf("Head: %p\n", head);
    // printf("Head->data: %d\n", head->data);
    return 0;
}
