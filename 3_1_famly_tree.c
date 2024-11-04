#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE 100
#define MAX_NAME 20

typedef struct {
  char *items[MAX_TREE]; // Array representation of the binary tree
  int size;              // Number of actual members in the tree
} FamilyTree;

void initializeTree(FamilyTree *tree);
void insert(FamilyTree *tree, int index, char *name);
void display(FamilyTree *tree);
void displayChildren(FamilyTree *tree, char *name);
void displayParent(FamilyTree *tree, char *name);
void displayGrandparent(FamilyTree *tree, char *name);
int findIndex(FamilyTree *tree, char *name);

int main() {
  FamilyTree tree;
  initializeTree(&tree);

  // Insert initial members (complete binary tree)
  insert(&tree, 0, "John");    // Root
  insert(&tree, 1, "Mary");    // Left child of John
  insert(&tree, 2, "Peter");   // Right child of John
  insert(&tree, 3, "Sarah");   // Left child of Mary
  insert(&tree, 4, "Michael"); // Right child of Mary
  insert(&tree, 5, "Emma");    // Left child of Peter
  insert(&tree, 6, "David");   // Right child of Peter

  int choice;
  char name[MAX_NAME];

  do {
    printf("\n\nFamily Tree Operations:");
    printf("\n1. Display family tree by generations");
    printf("\n2. Find children of a person");
    printf("\n3. Find parent of a person");
    printf("\n4. Find grandparent of a person");
    printf("\n5. Exit");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume newline character

    switch (choice) {
    case 1:
      printf("\nFamily Tree by Generations:\n");
      display(&tree);
      break;

    case 2:
      printf("\nEnter name to find children: ");
      scanf("%s", name);
      displayChildren(&tree, name);
      break;

    case 3:
      printf("\nEnter name to find parent: ");
      scanf("%s", name);
      displayParent(&tree, name);
      break;

    case 4:
      printf("\nEnter name to find grandparent: ");
      scanf("%s", name);
      displayGrandparent(&tree, name);
      break;

    case 5:
      printf("\nExiting...\n");
      break;

    default:
      printf("\nInvalid choice!\n");
    }
  } while (choice != 5);

  // Free allocated memory
  for (int i = 0; i < tree.size; i++) {
    free(tree.items[i]);
  }

  return 0;
}

void initializeTree(FamilyTree *tree) {
  tree->size = 0;
  for (int i = 0; i < MAX_TREE; i++) {
    tree->items[i] = NULL; // Initialize all items to NULL
  }
}

void insert(FamilyTree *tree, int index, char *name) {
  if (index < MAX_TREE) {
    tree->items[index] = malloc(MAX_NAME * sizeof(char));
    strcpy(tree->items[index], name);
    if (index + 1 > tree->size) {
      tree->size = index + 1; // Update the size of the tree
    }
  }
}

void display(FamilyTree *tree) {
  int level = 0;
  int count = 1;

  for (int i = 0; i < tree->size; i++) {
    if (i == count - 1) {
      printf("\n"); // New generation
      count *= 2;   // Move to the next level
      level++;
    }
    if (tree->items[i] != NULL) {
      printf("%s ", tree->items[i]);
    } else {
      printf("NULL ");
    }
  }
  printf("\n");
}

void displayChildren(FamilyTree *tree, char *name) {
  int index = findIndex(tree, name);
  if (index == -1) {
    printf("%s not found in the tree.\n", name);
    return;
  }
  printf("Children of %s: ", name);
  int leftIndex = 2 * index + 1;
  int rightIndex = 2 * index + 2;

  if (leftIndex < tree->size && tree->items[leftIndex] != NULL) {
    printf("%s ", tree->items[leftIndex]);
  }
  if (rightIndex < tree->size && tree->items[rightIndex] != NULL) {
    printf("%s ", tree->items[rightIndex]);
  }
  printf("\n");
}

void displayParent(FamilyTree *tree, char *name) {
  int index = findIndex(tree, name);
  if (index <= 0) {
    printf("%s is the root node or not found, no parent.\n", name);
    return;
  }
  int parentIndex = (index - 1) / 2;
  if (parentIndex < tree->size && tree->items[parentIndex] != NULL) {
    printf("Parent of %s: %s\n", name, tree->items[parentIndex]);
  }
}

void displayGrandparent(FamilyTree *tree, char *name) {
  int index = findIndex(tree, name);
  if (index <= 1) {
    printf("%s has no grandparent or not found.\n", name);
    return;
  }
  int parentIndex = (index - 1) / 2;
  int grandparentIndex = (parentIndex - 1) / 2;
  if (grandparentIndex < tree->size && tree->items[grandparentIndex] != NULL) {
    printf("Grandparent of %s: %s\n", name, tree->items[grandparentIndex]);
  }
}

int findIndex(FamilyTree *tree, char *name) {
  for (int i = 0; i < tree->size; i++) {
    if (tree->items[i] != NULL && strcmp(tree->items[i], name) == 0) {
      return i;
    }
  }
  return -1; // Not found
}
