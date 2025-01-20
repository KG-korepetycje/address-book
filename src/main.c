#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "list.h"
// #include "csv.h"

#define MAX_NAME_SIZE 30
#define MAX_SURNAME_SIZE 30
#define MAX_PHONE_SIZE 20
#define MAX_GROUP_SIZE 50
// void bubble_sort() {
//     int t[5] = {6, 4, 3, 8, 2};

//     printf("Before: [ ");
//     for (int i = 0; i < 5; i++) {
//         printf("%d ", t[i]);
//     }
//     printf("]\n");

//     int size = 5;
//     int counter = 1;

//     for (int j = 0; j < (size - 1); j++) {
//         for (int i = 0; i < (size - 1 - j); i++) {
//             printf("Counter: %d\n", counter);
//             counter++;
//             if (t[i] > t[i + 1]) {
//                 int tmp = t[i + 1];
//                 t[i + 1] = t[i];
//                 t[i] = tmp;
//             }
//         }
//     }

//     printf("After: [ ");
//     for (int i = 0; i < 5; i++) {
//         printf("%d ", t[i]);
//     }
//     printf("]\n");
// }

struct contact {
    char name[MAX_NAME_SIZE];
    char surname[MAX_SURNAME_SIZE];
    char phone[MAX_PHONE_SIZE];
    char group[MAX_GROUP_SIZE];
};


struct element {
    struct contact data;

    struct element* prev;
    struct element* next;
};


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


void to_lower_no_copy(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
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


void append_from_csv(struct element** head, char file_path[], int sort_type) {
    FILE* p_file;
    char name[MAX_NAME_SIZE], surname[MAX_SURNAME_SIZE], phone[MAX_PHONE_SIZE], group[MAX_GROUP_SIZE];

    p_file = fopen(file_path, "r");
    if (p_file == NULL) {
        // perror("Error opening file");
        printf("\nError opening file\n\n");
        return;
    }

    while (fscanf(p_file, "%[^;];%[^;];%[^;];%[^\n]\n", name, surname, phone, group) == 4) {
        struct contact data;
        strcpy(data.name, name);
        strcpy(data.surname, surname);
        strcpy(data.phone, phone);
        strcpy(data.group, group);
        append(head, data, sort_type);
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


void filter_list_by_name_surname(struct element* head, char* filter) {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    struct element* current = head;
    int counter = 1;
    while(current != NULL) {
        char* lower_name = to_lower((current->data).name);
        char* lower_surname = to_lower((current->data).surname);

        if (strstr(lower_name, filter) != NULL || strstr(lower_surname, filter) != NULL) {
            printf("\n== %d. CONTACT ==\n", counter);
            printf("Name: %s\n", current->data.name);
            printf("Surname: %s\n", current->data.surname);
            printf("Phone: %s\n", current->data.phone);
            printf("Group: %s\n", current->data.group);
            counter++;
        }

        free(lower_name);
        free(lower_surname);
        current = current->next;
    }
    printf("\n");
}


void filter_list_by_group(struct element* head, char* filter) {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    struct element* current = head;
    int counter = 1;
    while(current != NULL) {
        char* lower_group = to_lower((current->data).group);

        if (strstr(lower_group, filter) != NULL) {
            printf("\n== %d. CONTACT ==\n", counter);
            printf("Name: %s\n", current->data.name);
            printf("Surname: %s\n", current->data.surname);
            printf("Phone: %s\n", current->data.phone);
            printf("Group: %s\n", current->data.group);
            counter++;
        }

        free(lower_group);
        current = current->next;
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


char* get_user_input(char* prompt, int max_length) {
    char* input = NULL;
    int counter = 0;
    while (input == NULL && counter < 3) {
        input = malloc(max_length + 1);
        counter++;
    }
    if (input == NULL) {
        return input;
    }
    printf("%s (max. %d characters): ", prompt, max_length);
    fgets(input, max_length, stdin);
    if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
        input[strlen(input) - 1] = '\0';
    return input;
}


int main() {
    struct element* head = NULL;

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
        printf("[6] Filter list by name or surname\n");
        printf("[7] Filter list by group\n");
        printf("[8] Check current sort type\n");
        printf("\nYour choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
            case 0: {
                break;
            }
            case 1: {
                char prompt[20];

                strcpy(prompt, "Name");
                char* name = get_user_input(prompt, MAX_NAME_SIZE);
                if (name == NULL) {
                    printf("\nFailed to allocate the memory\n");
                    break;
                }

                strcpy(prompt, "Surname");
                char* surname = get_user_input(prompt, MAX_SURNAME_SIZE);
                if (surname == NULL) {
                    printf("\nFailed to allocate the memory\n");
                    break;
                }

                strcpy(prompt, "Phone");
                char* phone = get_user_input(prompt, MAX_PHONE_SIZE);
                if (phone == NULL) {
                    printf("\nFailed to allocate the memory\n");
                    break;
                }

                strcpy(prompt, "Group");
                char* group = get_user_input(prompt, MAX_GROUP_SIZE);
                if (group == NULL) {
                    printf("\nFailed to allocate the memory\n");
                    break;
                }

                struct contact data;
                strcpy(data.name, name);
                strcpy(data.surname, surname);
                strcpy(data.phone, phone);
                strcpy(data.group, group);
                append(&head, data, sort_type);
                
                free(name);
                free(surname);
                free(phone);
                free(group);
                break;
            }
            case 2: {
                char prompt[20];
                strcpy(prompt, "CSV file path");
                char* file_path = get_user_input(prompt, 50);
                if (file_path == NULL) {
                    printf("\nFailed to allocate the memory\n");
                    break;
                }

                append_from_csv(&head, file_path, sort_type);
                free(file_path);
                break;
            }
            case 3: {
                print_list(head);
                break;
            }
            case 4: {
                printf("\nSort type selection:\n");
                printf("[0] No sorting\n");
                printf("[1] By name\n");
                printf("[2] By surname\n");
                printf("[3] By group\n\n");
                printf("Your choice: ");
                scanf("%d", &sort_type);
                sort_list(&head, sort_type);
                break;
            }
            case 5: {
                int id;
                printf("\nContact ID (number from the list): ");
                scanf("%d", &id);
                remove_by_id(&head, id);
                break;
            }
            case 6: {
                char prompt[20];
                strcpy(prompt, "Filter");
                char* filter = get_user_input(prompt, 20);
                if (filter == NULL) {
                    printf("\nFailed to allocate the memory\n");
                    break;
                }
                to_lower_no_copy(filter);
                filter_list_by_name_surname(head, filter);
                free(filter);
                break;
            }
            case 7: {
                char prompt[20];
                strcpy(prompt, "Filter");
                char* filter = get_user_input(prompt, 20);
                if (filter == NULL) {
                    printf("\nFailed to allocate the memory\n");
                    break;
                }
                to_lower_no_copy(filter);
                filter_list_by_group(head, filter);
                free(filter);
                break;
            }
            case 8: {
                switch (sort_type) {
                    case 0: {
                        printf("\nNo sorting is applied (sort_type=0)\n\n");
                        break;
                    }
                    case 1: {
                        printf("\nSorting by name is applied (sort_type=1)\n\n");
                        break;
                    }
                    case 2: {
                        printf("\nSorting by surname is applied (sort_type=2)\n\n");
                        break;
                    }
                    case 3: {
                        printf("\nSorting by group is applied (sort_type=3)\n\n");
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            default: {
                printf("Not valid input!\n");
                break;
            }
        }
    }

    free_list(&head);
    return 0;
}


// int main() {
//     struct element* head = NULL;
//     // print_list(head);
//     // // struct element* head = create_element(123);
//     // struct element* elem = create_element(999);

//     // append(&head, elem);
//     // print_list(head);

//     // printf("Head: %p\n", head);
//     // printf("Head->data: %d\n", head->data);
//     // free_list(&head);
//     // printf("Head: %p\n", head);

//     // elem = create_element(999);
//     // append(&head, elem);
//     // printf("Head: %p\n", head);
//     // print_list(head);

//     // parse_contact("data/prosta_lista.csv");
//     // struct element* head = parse_file_to_list("data/prosta_lista.csv");

//     append_from_csv(&head, "data/prosta_lista.csv");
//     // append_from_csv(&head, "data/rozbudowana_lista.csv");
//     // // append_from_csv(&head, "data/prosta_lista.csv");
//     print_list(head);
//     // int sort_type = 1;
//     // sort_list(&head, sort_type);

//     // struct contact data;
//     // strcpy(data.name, "Zenon");
//     // strcpy(data.surname, "Test surname");
//     // strcpy(data.phone, "Test phone");
//     // strcpy(data.group, "Test group");
//     // append(&head, data, sort_type);

//     // // print_list(head);
//     // remove_by_id(&head);
//     // print_list(head);
//     // menu(&head);

//     free_list(&head);


//     // bubble_sort();

//     return 0;
// }
