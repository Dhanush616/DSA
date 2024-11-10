#include <stdio.h>
#include <stdlib.h>

// Macro for memory allocation with error checking
#define MALLOC(p, n, type) \
{ \
    p = malloc(n * sizeof(type)); \
    if (p == NULL) { \
        printf("Insufficient memory\n"); \
        exit(0); \
    } \
}

// Structure definition for stack nodes
struct node {
    int info;            // Data part
    struct node* next;   // Pointer to the next node
};

// Typedef for easier usage of Node type
typedef struct node* Node;

// Function to push an element onto the stack
void push(Node* top, int value) {
    Node newNode;
    MALLOC(newNode, 1, struct node); // Allocate memory for the new node
    newNode->info = value; // Set node value
    newNode->next = *top; // Link new node to previous top
    *top = newNode; // Update top pointer
    printf("%d pushed to stack\n", value);
}

// Function to pop an element from the stack
int pop(Node* top, int* underflowFlag) {
    if (*top == NULL) { // Check for underflow
        if (*underflowFlag == 0) {
            printf("Stack underflow\n"); // Print underflow message
            *underflowFlag = 1; // Set flag
        }
        return -1; // Return -1 on failure
    }
    *underflowFlag = 0; // Reset flag for successful pop
    Node temp = *top;
    int poppedValue = temp->info; // Store popped value
    *top = (*top)->next; // Move top pointer down
    free(temp); // Free popped node
    return poppedValue; // Return popped value
}

// Function to display all elements in the stack
void display(Node top) {
    if (top == NULL) { // Check if empty
        printf("Stack is empty\n");
        return;
    }
    Node temp = top;
    printf("Stack elements: ");
    while (temp != NULL) {
        printf("%d ", temp->info); // Print each element
        temp = temp->next; // Move to next node
    }
    printf("\n"); // Newline for formatting
}

// Function to display the menu of operations
void menu() {
    printf("\nSTACK OPERATIONS USING LINKED LIST\n");
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Display\n");
    printf("4. Exit\n");
}

int main() {
    Node top = NULL; // Initialize stack
    int choice, value, numPush, numPop, i;
    int underflowFlag = 0; // Flag for underflow message

    while (1) { // Loop for menu
        menu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice); // Get user choice

        switch (choice) { // Process choice
            case 1: // Push operation
                printf("Number of values you want to push into the stack: ");
                scanf("%d", &numPush);
                for (i = 0; i < numPush; i++) {
                    scanf("%d", &value); // Get value
                    push(&top, value); // Push value onto stack
                }
                break;
            case 2: // Pop operation
                printf("Number of values you want to pop from the stack: ");
                scanf("%d", &numPop);
                for (i = 0; i < numPop; i++) {
                    value = pop(&top, &underflowFlag); // Pop value from stack
                    if (value != -1) {
                        printf("Popped value: %d\n", value);
                    }
                }
                break;
            case 3: // Display operation
                display(top); // Show stack contents
                break;
            case 4: // Exit operation
                printf("Exiting program...\n");
                exit(0); // Exit the program
                break;
            default: // Invalid choice
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0; // Return success
}