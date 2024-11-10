#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro for memory allocation with error checking
#define MALLOC(p, n, type) \
{ \
    p = malloc(n * sizeof(type)); \
    if (p == NULL) { \
        printf("Insufficient memory\n"); \
        exit(0); \
    } \
}

struct Student {
    char name[50];
    char usn[20];
    float cgpa;
    char branch[50];
    struct Student *next;
};

typedef struct Student Student;

Student *head = NULL;

// Function to create a new student node
Student* createStudent() {
    Student *newStudent;
    MALLOC(newStudent, 1, Student);

    printf("Enter student name: ");
    scanf(" %s", newStudent->name);
    printf("Enter student USN: ");
    scanf(" %s", newStudent->usn);
    printf("Enter student CGPA: ");
    scanf("%f", &newStudent->cgpa);
    printf("Enter student branch: ");
    scanf(" %s", newStudent->branch);

    newStudent->next = NULL;
    return newStudent;
}

// Function to add student details
void enterStudentDetails() {
    Student *newStudent = createStudent();
    
    if (head == NULL) {
        head = newStudent;
    } else {
        Student *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
    printf("Student details added successfully.\n\n");
}

// Function to display all students of a specified branch
void displayBranchStudents() {
    if (head == NULL) {
        printf("No student details available.\n\n");
        return;
    }

    char branch[50];
    printf("Enter branch to display: ");
    scanf(" %s", branch);

    Student *temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->branch, branch) == 0) {
            printf("\nStudent Name: %s", temp->name);
            printf("\nUSN: %s", temp->usn);
            printf("\nCGPA: %.2f", temp->cgpa);
            printf("\nBranch: %s\n", temp->branch);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No students found in branch %s.\n\n", branch);
    } else {
        printf("\n");
    }
}

// Function to change branch if CGPA >= 9
void changeBranch() {
    char usn[20];
    printf("Enter the USN of the student to change branch: ");
    scanf("%s", usn);

    Student *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->usn, usn) == 0) {
            if (temp->cgpa >= 9.0) {
                printf("Enter the new branch: ");
                scanf(" %s", temp->branch);
                printf("Branch updated successfully.\n\n");
            } else {
                printf("Branch change not allowed. CGPA is less than 9.\n\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("Student with USN %s not found.\n\n", usn);
}

// Function to display menu
void menu() {
    int choice;
    while (1) {
        printf("1. Enter student details\n");
        printf("2. Display student details of a specific branch\n");
        printf("3. Change branch\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterStudentDetails();
                break;
            case 2:
                displayBranchStudents();
                break;
            case 3:
                changeBranch();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
