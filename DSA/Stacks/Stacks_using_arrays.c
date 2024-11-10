#include <stdio.h>
#include <stdlib.h>

// Macro for memory allocation with error checking
#define MALLOC(p, n, type) \
{ \
    p = (type *)malloc(n * sizeof(type)); \
    if (p == NULL) { \
        printf("Insufficient memory\n"); \
        exit(0); \
    } \
}

// Global variables for the stack
int *stack;
int top = -1;
int maxSize = 0;  // User-defined stack size

// Function to push an element onto the stack
void push(int data) {
    // Check if the stack is full
    if (top == maxSize - 1) {
        printf("Stack is full!\n");
        return;
    }

    stack[++top] = data;
    printf("Pushed: %d\n", data);
}

// Function to pop an element from the stack
int pop() {
    if (top == -1) {
        printf("Stack is empty!\n");
        return -1;
    }

    int data = stack[top--];
    return data;
}

// Function to display the stack elements
void displayStack() {
    if (top == -1) {
        printf("Stack is empty!\n");
        return;
    }

    printf("Stack elements: ");
    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// Main function to run the menu-driven program
int main() {
    int choice, numElements, value, numPop;

    printf("Enter the size of the stack: ");
    scanf("%d", &maxSize);

    // Allocate memory for the stack using the MALLOC macro
    MALLOC(stack, maxSize, int);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display Stack\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of elements to push: ");
                scanf("%d", &numElements);
                for (int i = 0; i < numElements; i++) {
                    printf("Enter value to push: ");
                    scanf("%d", &value);
                    push(value);
                }
                break;
            case 2:
                printf("Enter the number of elements to pop: ");
                scanf("%d", &numPop);
                for (int i = 0; i < numPop; i++) {
                    value = pop();
                    if (value != -1) {
                        printf("Popped: %d\n", value);
                    } else {
                        printf("No more elements to pop!\n");
                        break; // Exit the loop if the stack is empty
                    }
                }
                break;
            case 3:
                displayStack();
                break;
            case 4:
                printf("Exiting program.\n");
                free(stack); // Free the allocated memory
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
