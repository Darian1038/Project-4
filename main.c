/* COP 3502C Assignment 4
This program is written by: Darian Torres */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

// maxlength of the input strings of characters
#define MAXLEN 31

// declare files for use
FILE *ifp, *ofp;

// item structure
typedef struct itemNode {
  char name[MAXLEN];
  int count;
  struct itemNode *left, *right;
} itemNode;

// tree name node structure
typedef struct treeNameNode {
  char treeName[MAXLEN];
  struct treeNameNode *left, *right;
  itemNode *theTree;
} treeNameNode;

// creates tree names for each tree name given
// in the input; returns treeNameNode
treeNameNode *createTreeNameNode(char *treeName) {
  // allocate memory
  treeNameNode *node = malloc(sizeof(treeNameNode));

  // inputing tree name
  strcpy(node->treeName, treeName);

  // initialzing left, right, and tree
  node->left = NULL;
  node->right = NULL;
  node->theTree = NULL;

  // returning the node
  return node;
}

treeNameNode *insertTreeName(treeNameNode *root, treeNameNode *element) {
  // Inserting into an empty tree.
  if (root == NULL) {
    return element;
  } else {
    // element should be inserted to the right.
    if (strcmp(element->treeName, root->treeName) > 0) {
      // There is a right subtree to insert the node.
      if (root->right != NULL)
        root->right = insertTreeName(root->right, element);
      // Place the node directly to the right of root.
      else
        root->right = element;
    }
    // element should be inserted to the left.
    else {
      // There is a left subtree to insert the node.
      if (root->left != NULL)
        root->left = insertTreeName(root->left, element);
      // Place the node directly to the left of root.
      else
        root->left = element;
    }
  }
  // Return the root pointer of the updated tree.
  return root;
}

// inserts itemNode into a treeNameNode
itemNode *insertItemNode(itemNode *root, itemNode *element) {
  // Inserting into an empty tree.
  if (root == NULL) {
    return element;
  } 
  else {
    // element should be inserted to the right.
    if (strcmp(element->name, root->name) > 0) {
      // There is a right subtree to insert the node.
      if (root->right != NULL)
        root->right = insertItemNode(root->right, element);
      // Place the node directly to the right of root.
      else
        root->right = element;
    }
    // element should be inserted to the left.
    else {
      // There is a left subtree to insert the node.
      if (root->left != NULL)
        root->left = insertItemNode(root->left, element);
      // Place the node directly to the left of root.
      else
        root->left = element;
    }
  }
  // Return the root pointer of the updated tree.
  return root;
}

// Builds the NameTree using the createNameNode function
treeNameNode *buildNameTree(int N) {
  // temp variable and tree name character array
  treeNameNode *root = NULL;
  char treeName[MAXLEN];

  // take in tree name and makes and node for each name
  for (int i = 0; i < N; i++) {
    fscanf(ifp, "%s", treeName);
    treeNameNode *node = createTreeNameNode(treeName);
    root = insertTreeName(root, node);
  }

  // returning root of the tree
  return root;
}

// searches for and returns a treenamenode
treeNameNode *searchNameNode(treeNameNode *root, char treeName[MAXLEN]) {
  // base case
  if (root == NULL)
    return root;
  // if found
  else if (strcmp(root->treeName, treeName) == 0)
    return root;
  // move left if greater
  else if (strcmp(root->treeName, treeName) > 0)
    return searchNameNode(root->left, treeName);
  // else move right
  else
    return searchNameNode(root->right, treeName);
}

// creates a itemNode
itemNode *itemNodeCreate(char *itemName, int value) {
  // create node
  itemNode *node = malloc(sizeof(itemNode));

  // input data
  strcpy(node->name, itemName);
  node->count = value;
  node->left = NULL;
  node->right = NULL;

  return node;
}

// searches for a given itemnnode in a treenamenode
void search(treeNameNode *node, itemNode *node2, char *string) {
  // base case
  if (node2 == NULL) {
    printf("%s not found in %s\n", string, node->treeName);
    fprintf(ofp, "%s not found in %s\n", string, node->treeName);
    return;
  }
  // if we find the itemnode
  else if (strcmp(string, node2->name) == 0) {
    printf("%d %s found in %s\n", node2->count, node2->name, node->treeName);
    fprintf(ofp, "%d %s found in %s\n", node2->count, node2->name,
            node->treeName);
    return;
  }
  // move left if string compare is less than the current node
  else if (strcmp(string, node2->name) < 0)
    search(node, node2->left, string);
  // vise versa
  else
    search(node, node2->right, string);
}

// counts the items before a specific item node
int item_before(itemNode *root, char *string) {
  // base case
  if (root == NULL)
    return 0;
  // if string less, move left
  else if (strcmp(root->name, string) < 0) {
    return 1 + item_before(root->left, string) +
           item_before(root->right, string);
  }
  // vice versa
  else {
    return item_before(root->left, string);
  }
}

// determines the height of a given tree
int height(itemNode *node) {
  // if height is just the node, return -1
  if (node == NULL) {
    return -1;
  }
  // set left and right, return whichever is higher
  else {
    int l = height(node->left);
    int r = height(node->right);
    if (l > r)
      return l + 1;
    else
      return r + 1;
  }
}

// determines the balance between the left and right side of
// a given tree
void height_balance(itemNode *node, treeNameNode *node2) {
  // initialize variables
  int left = height(node->left);
  int right = height(node->right);

  // specifically asks for abs in instructions
  int difference = abs(left - right);

  // return if null; base case
  if (node == NULL)
    return;

  // print if finding the difference
  printf("%s: left height %d, right height %d, difference %d, ",
         node2->treeName, left, right, difference);
  fprintf(ofp, "%s: left height %d, right height %d, difference %d, ",
          node2->treeName, left, right, difference);
  // if balanced, print
  if (left == right) {
    printf("balanced\n");
    fprintf(ofp, "balanced\n");
  }
  // otherwise not balanced
  else {
    printf("not balanced\n");
    fprintf(ofp, "not balanced\n");
  }
}

// counts the total count of all itemnodes in a given tree
int count(itemNode *node) {
  if (node == NULL)
    return 0;
  else
    return node->count + count(node->left) + count(node->right);
}

// searches for a specific itemNode
itemNode *searchItem(char *string, itemNode *root) {
  // base case
  if (root == NULL) {
    return NULL;
  }

  // if found, return node
  else if (strcmp(string, root->name) == 0) {
    return root;
  }

  // traverse
  else if (strcmp(string, root->name) < 0)
    return searchItem(string, root->left);

  else
    return searchItem(string, root->right);
}

// determines the parents node of a given tree
itemNode *parent(itemNode *root, itemNode *node) {
  // Take care of NULL cases.
  if (root == NULL || root == node)
    return NULL;
  // The root is the direct parent of node.
  if (root->left == node || root->right == node)
    return root;
  // Look for node's parent in the left side of the tree.
  if (strcmp(node->name, root->name) < 0)
    return parent(root->left, node);
  // Look for node's parent in the right side of the tree.
  else if (strcmp(node->name, root->name) > 0)
    return parent(root->right, node);
  return NULL; // Catch any other extraneous cases.
}

// determines the minimum value in a itemnode tree
itemNode *minVal(itemNode *root) {
  // Root stores the minimal value.
  if (root->left == NULL)
    return root;
  // The left subtree of the root stores the minimal value.
  else
    return minVal(root->left);
}

// deletes and traverses a tree
itemNode *delete (itemNode *root, char *value) {
  int saveValue;
  itemNode *delnode, *new_del_node, *save_node;
  itemNode *par;
  char save_val[MAXLEN];
  delnode = searchItem(value, root);
  par = parent(root, delnode);
  if (delnode->left == NULL && delnode->right == NULL) {
    if (par == NULL) {
      free(root);
      return NULL;
    }
    if (strcmp(value, par->name) < 0) {
      free(par->left);
      par->left = NULL;
    }

    else {
      free(par->right);
      par->right = NULL;
    }
    return root;
  }

  if (delnode->left != NULL && delnode->right == NULL) {
    if (par == NULL) {
      save_node = delnode->left;
      free(delnode);
      return save_node;
    }

    if (strcmp(value, par->name) < 0) {
      save_node = par->left;
      par->left = par->left->left;
      free(save_node);
    }

    else {
      save_node = par->right;
      par->right = par->right->left;
      free(save_node);
    }
    return root;
  }

  if (delnode->left == NULL && delnode->right != NULL) {

    if (par == NULL) {
      save_node = delnode->right;
      free(delnode);
      return save_node;
    }
    if (strcmp(value, par->name) < 0) {
      save_node = par->left;
      par->left = par->left->right;
      free(save_node);
    } else {
      save_node = par->right;
      par->right = par->right->right;
      free(save_node);
    }
    return root;
  }

  new_del_node = minVal(delnode->right);
  strcpy(save_val, new_del_node->name);
  saveValue = new_del_node->count;

  root = delete (root, save_val);

  strcpy(delnode->name, save_val);
  delnode->count = saveValue;
  return root;
}

// could be here
itemNode *reduced(treeNameNode *name, itemNode *root, itemNode *node, int reduce) {
  node->count = node->count - reduce;
  if (node->count <= 0) {
    root = delete (root, node->name);
  }
  return root;
}

treeNameNode *parent_tree(treeNameNode *root, treeNameNode *node) {
  // Take care of NULL cases.
  if (root == NULL || root == node)
    return NULL;
  // The root is the direct parent of node.
  if (root->left == node || root->right == node)
    return root;
  // Look for node's parent in the left side of the tree.
  if (strcmp(node->treeName, root->treeName) < 0)
    return parent_tree(root->left, node);
  // Look for node's parent in the right side of the tree.
  else if (strcmp(node->treeName, root->treeName) > 0)
    return parent_tree(root->right, node);
  return NULL; // Catch any other extraneous cases.
}

treeNameNode *minValT(treeNameNode *root) {
  // Root stores the minimal value.
  if (root->left == NULL)
    return root;
  // The left subtree of the root stores the minimal value.
  else
    return minValT(root->left);
}

void free_Tfunction(itemNode *node) {
  if (node != NULL) {
    free_Tfunction(node->left);
    free_Tfunction(node->right);
    free(node);
  }
}

treeNameNode *delete_name(treeNameNode *root, char *value) {
  treeNameNode *delnode, *new_del_node, *save_node;
  treeNameNode *par;
  char save_val[MAXLEN];
  itemNode *stree;

  delnode = searchNameNode(root, value);
  par = parent_tree(root, delnode);

  if (delnode->left == NULL && delnode->right == NULL) {
    if (par == NULL) {
      free_Tfunction(root->theTree);
      free(root);
      return NULL;
    }
    if (strcmp(value, par->treeName) < 0) {
      free_Tfunction(par->left->theTree);
      free(par->left);
      par->left = NULL;
    }

    else {
      free_Tfunction(par->right->theTree);
      free(par->right);
      par->right = NULL;
    }
    return root;
  }

  if (delnode->left != NULL && delnode->right == NULL) {
    if (par == NULL) {
      save_node = delnode->left;
      free_Tfunction(delnode->theTree);
      free(delnode);
      return save_node;
    }

    if (strcmp(value, par->treeName) < 0) {
      save_node = par->left;
      par->left = par->left->left;
      free_Tfunction(save_node->theTree);
      free(save_node);
    }

    else {
      save_node = par->right;
      par->right = par->right->left;
      free_Tfunction(save_node->theTree);
      free(save_node);
    }
    return root;
  }

  if (delnode->left == NULL && delnode->right != NULL) {

    if (par == NULL) {
      save_node = delnode->right;
      free_Tfunction(delnode->theTree);
      free(delnode);
      return save_node;
    }
    if (strcmp(value, par->treeName) < 0) {
      save_node = par->left;
      par->left = par->left->right;
      free_Tfunction(save_node->theTree);
      free(save_node);
    } 
    else {
      save_node = par->right;
      par->right = par->right->right;
      free_Tfunction(save_node->theTree);
      free(save_node);
    }
    return root;
  }

  new_del_node = minValT(delnode->right);
  strcpy(save_val, new_del_node->treeName);
  stree = new_del_node->theTree;
  
  root = delete_name(root, save_val);

  strcpy(delnode->treeName, save_val);
  delnode->theTree = stree;
  return root;
}

void printItem(itemNode *root) {
  if (root == NULL)
    return;
  else {
    printItem(root->left);
    printf("%s ", root->name);
    fprintf(ofp, "%s ", root->name);
    printItem(root->right);
  }
}

void print(treeNameNode *root) {
  if (root == NULL)
    return;
  else {
    print(root->left);
    printf("===%s===\n", root->treeName);
    fprintf(ofp, "===%s===\n", root->treeName);
    printItem(root->theTree);
    printf("\n");
    fprintf(ofp, "\n");
    print(root->right);
  }
}

void inOrderPrint(treeNameNode *root) {
  if (root == NULL)
    return;
  else {
    inOrderPrint(root->left);
    printf("%s ", root->treeName);
    fprintf(ofp, "%s ", root->treeName);
    inOrderPrint(root->right);
  }
}

void traverse_in_traverse(treeNameNode *root) {
  inOrderPrint(root);
  printf("\n");
  fprintf(ofp, "\n");
  print(root);
}

void free_function(treeNameNode *root) {
  if (root != NULL) {
    free_function(root->left);
    free_function(root->right);
    free_Tfunction(root->theTree);
    free(root);
  }
}

// reads the information of the input file
// and return a treename node for the whole tree
void readFileAndOutput() {
  int N, I, Q;

  fscanf(ifp, "%d %d %d", &N, &I, &Q);
  treeNameNode *nameRoot = buildNameTree(N);

  int itemCount;
  char treeName[MAXLEN], itemName[MAXLEN];
  
  for (int i = 0; i < I; i++) {
    fscanf(ifp, "%s %s %d", treeName, itemName, &itemCount);
    itemNode *temp1 = itemNodeCreate(itemName, itemCount);
    treeNameNode *temp2 = searchNameNode(nameRoot, treeName);
    temp2->theTree = insertItemNode(temp2->theTree, temp1);
  }
  
  traverse_in_traverse(nameRoot);
  
  char temp[MAXLEN];
  for (int j = 0; j < Q; j++) {
    fscanf(ifp, "%s", temp);

    if (strcmp(temp, "search") == 0) {
      char tree[MAXLEN], item[MAXLEN];
      fscanf(ifp, "%s %s", tree, item);
      treeNameNode *temp3 = searchNameNode(nameRoot, tree);
      if (temp3 != NULL)
        search(temp3, temp3->theTree, item);
      else {
        printf("%s does not exist\n", tree);
        fprintf(ofp, "%s does not exist\n", tree);
      }
    }
    
    else if (strcmp(temp, "item_before") == 0) {
      char tree[MAXLEN], item[MAXLEN];
      fscanf(ifp, "%s %s", tree, item);
      treeNameNode *temp3 = searchNameNode(nameRoot, tree);
      if (temp3 != NULL) {
        printf("item before %s: %d\n", item, item_before(temp3->theTree, item));
        fprintf(ofp, "item before %s: %d\n", item,
                item_before(temp3->theTree, item));
      } else {
        printf("%s does not exist\n", tree);
        fprintf(ofp, "%s does not exist\n", tree);
      }
    }

    else if (strcmp(temp, "height_balance") == 0) {
      char tree[MAXLEN];
      fscanf(ifp, "%s", tree);
      treeNameNode *temp3 = searchNameNode(nameRoot, tree);
      if (temp3 != NULL) {
        height_balance(temp3->theTree, temp3);
      }
    }

    else if (strcmp(temp, "count") == 0) {
      char tree[MAXLEN];
      fscanf(ifp, "%s", tree);
      treeNameNode *temp3 = searchNameNode(nameRoot, tree);
      if (temp3 != NULL) {
        fprintf(ofp, "%s count %d\n", tree, count(temp3->theTree));
        printf("%s count %d\n", tree, count(temp3->theTree));
      }
    }

    else if (strcmp(temp, "reduce") == 0) {
      char tree[MAXLEN], item[MAXLEN];
      int reduce;
      fscanf(ifp, "%s %s %d", tree, item, &reduce);
      treeNameNode *temp3 = searchNameNode(nameRoot, tree);
      if (temp3 != NULL) {
        itemNode *temp4 = searchItem(item, temp3->theTree);
        temp3->theTree = reduced(temp3, temp3->theTree, temp4, reduce);
        fprintf(ofp, "%s reduced\n", item);
        printf("%s reduced\n", item);
      }
    }
    
    
    else if (strcmp(temp, "delete") == 0) {
      char tree[MAXLEN], item[MAXLEN];
      fscanf(ifp, "%s %s", tree, item);
      treeNameNode *temp3 = searchNameNode(nameRoot, tree);
      if (temp3 != NULL) {
        temp3->theTree = delete (temp3->theTree, item);
        fprintf(ofp, "%s deleted from %s\n", item, temp3->treeName);
        printf("%s deleted from %s\n", item, temp3->treeName);
      }
    }
    
    
    else if (strcmp(temp, "delete_name") == 0) {
      char tree[MAXLEN];
      fscanf(ifp, "%s", tree);
      nameRoot = delete_name(nameRoot, tree);
      fprintf(ofp, "%s deleted\n", tree);
      printf("%s deleted\n", tree);
    }
    
  }
  
  free_function(nameRoot);
}

void main() {
  atexit(report_mem_leak);

  // declaring files to read from and write to
  ifp = fopen("in.txt", "r");
  ofp = fopen("out.txt", "w");

  // reads in input of in.txt and spits out
  readFileAndOutput();

}