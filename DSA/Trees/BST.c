//This program creates a BST amd performs inorder , postorder , preorder traversal along with search operation  
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, n, type) \
{ \
    p = (type *)malloc((n) * sizeof(type)); \
    if (p == NULL) { \
        printf("Insufficient memory\n"); \
        exit(0); \
    } \
}

struct node {
    int info;
    struct node *llink;
    struct node *rlink;
};

typedef struct node *Node;

// Function to create a new node with given item
Node createNode(int item) {
    Node temp;
    MALLOC(temp, 1, struct node);
    temp->info = item;
    temp->llink = NULL;
    temp->rlink = NULL;

    return temp;
}

// Function to insert a new node in the BST
Node insert(Node root, int item) {
    if (root == NULL) {
        return createNode(item);
    }
    if (item < root->info) {
        root->llink = insert(root->llink, item);
    } else if (item > root->info) {
        root->rlink = insert(root->rlink, item);
    }
    return root;
}

// Inorder traversal //Left-Root-Right
void inorder(Node root) {
    if (root == NULL) {  // Base case: If the current node is NULL, return
        return;
    }
    inorder(root->llink);  // Recursive case: Traverse the left subtree
    printf("%d ", root->info);  // Visit the root node
    inorder(root->rlink);  // Recursive case: Traverse the right subtree
}
// Preorder traversal // Root-Left-Right
void preorder(Node root) {
    if (root == NULL) {  // Base case: If the current node is NULL, return
        return;
    }
    printf("%d ", root->info);  // Visit the root node
    preorder(root->llink);  // Recursive case: Traverse the left subtree
    preorder(root->rlink);  // Recursive case: Traverse the right subtree
}


// Postorder traversal //Left-Right-Root 
void postorder(Node root) {
    if (root == NULL) {  // Base case: If the current node is NULL, return
        return;
    }
    postorder(root->llink);  // Recursive case: Traverse the left subtree
    postorder(root->rlink);  // Recursive case: Traverse the right subtree
    printf("%d ", root->info);  // Visit the root node
}



// Function to search an item in the BST
Node search(Node root, int key) {
    if (root == NULL || root->info == key) {
        return root;
    }
    if (key < root->info) {
        return search(root->llink, key);
    } else {
        return search(root->rlink, key);
    }
}

int main() {
    Node root = NULL;
    int choice, item, key;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Search\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item to insert: ");
                scanf("%d", &item);
                root = insert(root, item);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                printf("Enter item to search: ");
                scanf("%d", &key);
                Node result = search(root, key);
                if (result != NULL) {
                    printf("Item %d found in the tree.\n", key);
                } else {
                    printf("Item %d not found in the tree.\n", key);
                }
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
