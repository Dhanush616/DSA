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

// Global variables for the circular queue
int *queue;
int front = -1;
int rear = -1;
int maxSize = 0;  // User-defined queue size

// Function to enqueue elements into the circular queue
void enqueue(int data) {
    // Check if the queue is full
    if ((rear + 1) % maxSize == front) {
        printf("Queue is full!\n");
        return;
    }

    // If the queue is empty, initialize front and rear to the first position
    if (front == -1) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % maxSize; // Circular increment
    }
    queue[rear] = data;
    printf("Enqueued: %d\n", data);
}

// Function to dequeue elements from the circular queue
int dequeue() {
    if (front == -1) {
        printf("Queue is empty!\n");
        return -1;
    }

    int data = queue[front];
    // If the last element is dequeued, reset front and rear
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % maxSize; // Circular increment
    }
    return data;
}

// Function to display the queue elements
void displayQueue() {
    if (front == -1) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear) break;
        i = (i + 1) % maxSize; // Circular increment
    }
    printf("\n");
}

// Main function to run the menu-driven program
int main() {
    int choice, numElements, value, numDequeue;

    printf("Enter the size of the queue: ");
    scanf("%d", &maxSize);

    // Allocate memory for the queue using the MALLOC macro
    MALLOC(queue, maxSize, int);

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
                free(queue); // Free the allocated memory
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
