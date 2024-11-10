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

// Structure definition for queue nodes
struct node {
    int info;            // Data part
    struct node* next;   // Pointer to the next node
};

// Typedef for easier usage of Node type
typedef struct node* Node;

// Global pointers for the circular queue
Node front = NULL;
Node rear = NULL;

// Function to create a new node
Node createNode(int data) {
    Node newNode;
    MALLOC(newNode, 1, struct node); // Using the MALLOC macro
    newNode->info = data;
    newNode->next = NULL;
    return newNode;
}

// Function to enqueue elements into the circular queue
void enqueue(int data) {
    Node newNode = createNode(data);
    if (rear == NULL) {
        front = rear = newNode;
        newNode->next = newNode; // Point to itself
    } else {
        rear->next = newNode;
        rear = newNode;
        newNode->next = front; // Maintain circular property
    }
}

// Function to dequeue elements from the circular queue
int dequeue() {
    if (front == NULL) {
        printf("Queue is empty!\n");
        return -1;
    }

    Node temp = front;
    int data = temp->info;

    // If there's only one node
    if (front == rear) {
        front = rear = NULL;
    } else {
        front = front->next;
        rear->next = front; // Maintain circular property
    }
    free(temp);
    return data;
}

// Function to display the queue elements
void displayQueue() {
    if (front == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    Node temp = front;
    printf("Queue elements: %d ", temp->info); // Print the first element

    // Use while loop to print the rest of the elements
    temp = temp->next;
    while (temp != front) {
        printf("%d ", temp->info);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to run the menu-driven program
int main() {
    int choice, numElements, value, numDequeue;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of elements to insert: ");
                scanf("%d", &numElements);
                for (int i = 0; i < numElements; i++) {
                    printf("Enter value to enqueue: ");
                    scanf("%d", &value);
                    enqueue(value);
                }
                break;
            case 2:
                printf("Enter the number of elements to dequeue: ");
                scanf("%d", &numDequeue);
                for (int i = 0; i < numDequeue; i++) {
                    value = dequeue();
                    if (value != -1) {
                        printf("Dequeued: %d\n", value);
                    } else {
                        printf("No more elements to dequeue!\n");
                        break; // Exit the loop if the queue is empty
                    }
                }
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
    