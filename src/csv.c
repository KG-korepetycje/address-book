#include <stdio.h>
#include <string.h>
#include "list.h"


struct element* parse_file_to_list(char file_path[]) {
    FILE* p_file;
    struct element* head = NULL;
    char name[30], surname[30], phone[20], group[50];

    p_file = fopen(file_path, "r");
    if (p_file == NULL) {
        perror("Error opening file");
        return head;
    }

    while (fscanf(p_file, "%[^;];%[^;];%[^;];%[^\n]\n", name, surname, phone, group) == 4) {
        struct contact data;
        strcpy(data.name, name);
        strcpy(data.surname, surname);
        strcpy(data.phone, phone);
        strcpy(data.group, group);
        append(&head, data);
    }

    fclose(p_file);
    return head;
}
