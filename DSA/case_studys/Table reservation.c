//This program uses arrays to carry out table reservation in a restaurant
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CALLOC(p, n, type) \
{ \
    p = (type *)calloc((n), sizeof(type)); \
    if (p == NULL) { \
        printf("Insufficient memory\n"); \
        exit(0); \
    } \
}

typedef struct {
    int table_number;
    int capacity;
    int is_available;
} Table;

void initialize_tables(Table *tables, int num_tables) {
    for (int i = 0; i < num_tables; i++) {
        tables[i].table_number = i + 1;
        printf("Enter the capacity for Table %d: ", tables[i].table_number);
        scanf("%d", &tables[i].capacity);
        tables[i].is_available = 1;
    }
}

void print_available_tables(Table *tables, int num_tables) {
    printf("Available Tables:\n");
    for (int i = 0; i < num_tables; i++) {
        if (tables[i].is_available) {
            printf("Table %d (Capacity: %d)\n", tables[i].table_number, tables[i].capacity);
        }
    }
}

void book_table(Table *tables, int table_number, int num_guests, char *name, char *phone, int num_tables) {
    if (table_number < 1 || table_number > num_tables) {
        printf("Invalid table number.\n");
        return;
    }
    if (tables[table_number - 1].is_available && tables[table_number - 1].capacity >= num_guests) {
        tables[table_number - 1].is_available = 0;
        printf("Table %d booked for %s (%s)\n", table_number, name, phone);
    } else {
        printf("Table not available or capacity insufficient.\n");
    }
}

void cancel_reservation(Table *tables, int table_number, int num_tables) {
    if (table_number < 1 || table_number > num_tables) {
        printf("Invalid table number.\n");
        return;
    }
    if (!tables[table_number - 1].is_available) {
        tables[table_number - 1].is_available = 1;
        printf("Reservation for Table %d canceled.\n", table_number);
    } else {
        printf("No reservation found for Table %d.\n");
    }
}

int main() {
    Table *tables;
    int num_tables;

    printf("Enter the number of tables in the restaurant: ");
    scanf("%d", &num_tables);

    // Allocate memory for the specified number of tables
    CALLOC(tables, num_tables, Table);

    // Initialize tables with user-defined capacities
    initialize_tables(tables, num_tables);

    int choice;
    while (1) {
        printf("\n1. Print Available Tables\n2. Book a Table\n3. Cancel a Reservation\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_available_tables(tables, num_tables);
                break;
            case 2: {
                int table_number, num_guests;
                char name[50], phone[20];
                printf("Enter table number, number of guests, name, and phone number: ");
                scanf("%d %d %s %s", &table_number, &num_guests, name, phone);
                book_table(tables, table_number, num_guests, name, phone, num_tables);
                break;
            }
            case 3: {
                int table_number;
                printf("Enter table number to cancel reservation: ");
                scanf("%d", &table_number);
                cancel_reservation(tables, table_number, num_tables);
                break;
            }
            case 4:
                free(tables);  // Free the allocated memory before exiting
                printf("Exiting the system. Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
