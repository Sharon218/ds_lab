#include <stdio.h>
#include <stdlib.h>

// Definition of the node structure
typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

// Function prototypes
Node *createNode(int data);
Node *insert(Node *root, int data);
Node *deleteNode(Node *root, int data);
Node *search(Node *root, int data);
void displayInOrder(Node *root);
Node *minValueNode(Node *node);

int main() {
  Node *root = NULL;
  int choice, data;

  do {
    printf("\nBinary Search Tree Operations:");
    printf("\n1. Insert");
    printf("\n2. Delete");
    printf("\n3. Search");
    printf("\n4. Display (In ascending order)");
    printf("\n5. Exit");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter data to insert: ");
      scanf("%d", &data);
      root = insert(root, data);
      break;
    case 2:
      printf("Enter data to delete: ");
      scanf("%d", &data);
      root = deleteNode(root, data);
      break;
    case 3:
      printf("Enter data to search: ");
      scanf("%d", &data);
      Node *foundNode = search(root, data);
      if (foundNode != NULL) {
        printf("Element %d found in the tree.\n", foundNode->data);
      } else {
        printf("Element %d not found in the tree.\n", data);
      }
      break;
    case 4:
      printf("Contents of the tree in ascending order: ");
      displayInOrder(root);
      printf("\n");
      break;
    case 5:
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice!\n");
    }
  } while (choice != 5);

  return 0;
}

// Create a new node
Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = newNode->right = NULL;
  return newNode;
}

// Insert a node into the BST
Node *insert(Node *root, int data) {
  if (root == NULL) {
    return createNode(data);
  }
  if (data < root->data) {
    root->left = insert(root->left, data);
  } else if (data > root->data) {
    root->right = insert(root->right, data);
  }
  return root; // Return unchanged node pointer
}

// Find the minimum value node in a subtree
Node *minValueNode(Node *node) {
  Node *current = node;
  while (current && current->left != NULL) {
    current = current->left;
  }
  return current;
}

// Delete a node from the BST
Node *deleteNode(Node *root, int data) {
  if (root == NULL) {
    return root; // Element not found
  }

  // Recursively find the node to delete
  if (data < root->data) {
    root->left = deleteNode(root->left, data);
  } else if (data > root->data) {
    root->right = deleteNode(root->right, data);
  } else {
    // Node with only one child or no child
    if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    }

    // Node with two children: Get the inorder successor
    Node *temp = minValueNode(root->right);
    root->data = temp->data; // Copy the inorder successor's data
    root->right =
        deleteNode(root->right, temp->data); // Delete the inorder successor
  }
  return root;
}

// Search for a node in the BST
Node *search(Node *root, int data) {
  if (root == NULL || root->data == data) {
    return root;
  }
  if (data < root->data) {
    return search(root->left, data);
  }
  return search(root->right, data);
}

// Display the tree contents in ascending order (in-order traversal)
void displayInOrder(Node *root) {
  if (root != NULL) {
    displayInOrder(root->left);
    printf("%d ", root->data);
    displayInOrder(root->right);
  }
}
