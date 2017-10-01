//Definitions of the Node and Tree types

typedef struct Node
{
    int value;                //TODO: make this generic
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

//API
Node* predecessor(Node* node);
Node* successor(Node* node);

//Helpers
void inorder_tree_walk(Node* root);
void preorder_tree_walk(Node* root);
void postorder_tree_walk(Node* root);
void insert(int key, Node* root, Node* parent);
Node* search(Node* root, int key);
Node* minimum(Node* root);
Node* maximum(Node* root);

//Tree - a simple but necessary wrapper around the root Node
typedef struct Tree {
    Node* root;
} Tree;

//Tree API
void tree_inorder_walk(Tree* tree);
void tree_preorder_walk(Tree* tree);
void tree_postorder_walk(Tree* tree);
Node* tree_search(Tree* tree, int key);
Node* tree_minimum(Tree* tree);
Node* tree_maximum(Tree* tree);
void tree_insert(Tree* tree, int key);
void tree_delete(Tree* tree, Node* node);
