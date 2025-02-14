#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include <stdlib.h> 

#define MAX 9
#define MAX_SIZE 20

/*
For my Project 1, I referred to InsertElement as AddWord I re-used it in this and did not change the function's name.
*/

/* the pseduecode: 
BEGIN 
DEFINE MAX = 9
DEFINE MAX_SIZE = 20
Initialize an array of Dictionary named words with size MAX
Initialize an array named Next with size MAX
SET currentSize to 0
SET startIndex to -1

Function addWord
  IF currentSize == MAX
    PRINT "Dictionary is full"
  IF startIndex == -1
    SET Next at currentSize to -1
    SET startIndex to currentSize
  ELSE
    SET Next at currentSize to startIndex
    SET Next at currentSize - 1 to currentSize
  Increment currentSize

Function mergeDictionaries
  Initialize indexA to 0
  Initialize indexB to 0
  Initialize indexMerged to 0
  WHILE indexA < sizeA and indexB < sizeB
    IF Turkish word in dict1,indexA <= Turkish word in dict2,indexB
      ADD it to mergedDict
      Increment indexA
    ELSE
      Add the dictionary the entry in dict2 to mergedDict
      Increment indexB
    Increment indexMerged

Function ConvertDictToBST
  Initialize root to NULL
  FOR each dictionary entry in dict
    IF the Turkish word != empty
      Insert the dictionary entry into the BST

Function InsertIntoBST
  SET a new node
  If newNode is NULL
    Print "Memory allocation failed"
  STRCPY turkish_word and english_word to newNode
  SET newNode's left and right pointers = NULL

  IF root = NULL
    Return newNode 
  ELSE If turkish_word is <root's turkish_word
    Insert newNode into the left subtree
    Update root's left pointer 
  Else
    Insert newNode into the right subtree
    Update root's right pointer 

  Return rOOT


Function MergeDictionaries3
  If BST1 is not NULL
    Insert the current node of BST1 into BST2
    merge the right subtree of BST1 into BST2
  Return BST2

Function printBST
  If root is NULL
    Return 0
  PRINT the left subtree
  PRINT the turkish_word and english_word of the root node
  Recursively print the right subtree

In main function
    CALL AddWord, dict1
    CALL AddWord, dict2
    CALL ConvertDictToBST for BST1
    CALL ConvertDictToBST fpr BST2
    PRINT MergedBst

END
*/

struct Dictionary {
    char turkish_word[MAX_SIZE];
    char english_word[MAX_SIZE];
};

struct Dictionary dict1[MAX];
struct Dictionary dict2[MAX];
struct Dictionary words[MAX];

// Function declarations
struct BSTNode* InsertIntoBST(struct BSTNode* root, const char* turkish_word, const char* english_word);
void inOrderTraversal(struct BSTNode* root);
int currentSize = 0;
int startIndex = -1;
int Next[MAX];


// ALGORITHM 1 , this is fully taken from project 1 but with a little difference,
//I was asking for entries in project one, in here I have added the entries in the main
//So i deleted the scanf and added strcpy
void addWord(struct Dictionary* dict, const char* turkish_word, const char* english_word) {
    if (currentSize == MAX) {
        printf("The dictionary is full and hence no addition can be made.\n");
        return;
    }
    strcpy(dict[currentSize].turkish_word, turkish_word);
    strcpy(dict[currentSize].english_word, english_word);
    if (startIndex == -1) {
        Next[currentSize] = -1;
        startIndex = currentSize;
    } else {
    Next[currentSize] = startIndex;
    Next[currentSize - 1] = currentSize;
    }
currentSize++;
}

//ALGORITHM 2
void mergeDictionaries(struct Dictionary* dict1, int sizeA, struct Dictionary* dict2, int sizeB, struct Dictionary* mergedDict) {
  int indexA = 0; 
  int indexB = 0; 
  int indexMerged = 0; 

// Merge the dictionaries:
while (indexA < sizeA && indexB < sizeB) {
if (strcmp(dict1[indexA].turkish_word, dict2[indexB].turkish_word) <= 0) {
mergedDict[indexMerged++] = dict1[indexA++];
    } else {
mergedDict[indexMerged++] = dict2[indexB++];
    }
  }
}

//ALGORITHM 3
typedef struct BSTNode {
    char turkish_word[MAX_SIZE];
    char english_word[MAX_SIZE];
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Function to convert a dictionary to a balanced BST
struct BSTNode* ConvertDictToBST(struct Dictionary dict[], int size) {
    struct BSTNode* root = NULL;
    // Insert each dictionary entry into the BST
    for (int i = 0; i < size; i++) {
    if (dict[i].turkish_word[0] != '\0') { 
    root = InsertIntoBST(root, dict[i].turkish_word, dict[i].english_word);
    }
    }
    return root;
}
// Function to insert a node into bst
struct BSTNode* InsertIntoBST(struct BSTNode* root, const char* turkish_word, const char* english_word) {
  // Create a new node
  struct BSTNode* newNode = (struct BSTNode*)malloc(sizeof(struct BSTNode));
  if (newNode == NULL) {
    printf("Memory allocation failed.\n");
    exit(1);
  }
  strcpy(newNode->turkish_word, turkish_word);
  strcpy(newNode->english_word, english_word);
  newNode->left = NULL;
  newNode->right = NULL;
// Recursive insertion based oncomparison
  if (root == NULL) {
    return newNode; // this is for empty tree, new node becomes root
  } else if (strcmp(turkish_word, root->turkish_word) < 0) {
    // Inserting in left subtree
    root->left = InsertIntoBST(root->left, turkish_word, english_word); 
  } else {
    // Insert in right subtree
    root->right = InsertIntoBST(root->right, turkish_word, english_word); 
  }
return root;
}

// Function to merge BST1 into BST2
struct BSTNode* MergeDictionaries3(struct BSTNode* BST1, struct BSTNode* BST2) {
    // In-order traversal of BST1 and insertion into BST2
    if (BST1 != NULL) {
    MergeDictionaries3(BST1->left, BST2);
    // Insert BST1 node into BST2
    BST2 = InsertIntoBST(BST2, BST1->turkish_word, BST1->english_word);
    MergeDictionaries3(BST1->right, BST2); }
    return BST2; // The merged BST is now BST2
}


//function to printit
void printBST(struct BSTNode* root) {
  if (root == NULL) {
    return;
  }
  printBST(root->left);
  printf("%s - %s\n", root->turkish_word, root->english_word);
  printBST(root->right);
}

int main() {

    // Fill dictionaries
    addWord(dict1, "sicak", "hot");
    addWord(dict1, "soğuk", "cold");
    addWord(dict1, "ada", "island");

    addWord(dict2, "komik", "funny");
    addWord(dict2, "araba", "car");
    addWord(dict2, "kalem", "pencil");

    // Convert dictionaries to BSTs
    struct BSTNode* BST1 = ConvertDictToBST(dict1, MAX);
    struct BSTNode* BST2 = ConvertDictToBST(dict2, MAX);

    // Merge BSTs
    struct BSTNode* mergedBST = MergeDictionaries3(BST1, BST2);

    printf("\nMerged Dictionary (In-order Traversal):\n");
    printBST(mergedBST);

    return 0;
}
