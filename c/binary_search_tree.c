#include<stdio.h>
#include<stdlib.h>
#include "binary_search_tree.h"

void tree_inorder_walk(Tree* tree) {
    inorder_tree_walk(tree->root);
}

void tree_preorder_walk(Tree* tree) {
    preorder_tree_walk(tree->root);
}

void tree_postorder_walk(Tree* tree) {
    postorder_tree_walk(tree->root);
}

Node* tree_search(Tree* tree, int key) {
    return search(tree->root, key);
}

Node* tree_minimum(Tree* tree) {
    return minimum(tree->root);
}

Node* tree_maximum(Tree* tree) {
    return maximum(tree->root);
}

//TODO: Include iterative version
void inorder_tree_walk(Node* root) {
    if (root != NULL) {
        inorder_tree_walk(root->left);
        printf("%d\n", root->value);    //TODO: Make visiting a generic thing, we may take a function pointer
        inorder_tree_walk(root->right);
    }
}

//TODO: Include iterative version
void preorder_tree_walk(Node* root) {
    if (root != NULL) {
        printf("%d\n", root->value); //TODO: Make visiting a generic thing, we may take a function pointer
        preorder_tree_walk(root->left);
        preorder_tree_walk(root->right);
    }
}

//TODO: Include iterative version
void postorder_tree_walk(Node* root) {
    if(root != NULL) {
        postorder_tree_walk(root->left);
        postorder_tree_walk(root->right);
        printf("%d\n", root->value);
    }
}

//TODO: Include iterative version
Node* search(Node* root, int key) {   //TODO: the key should actually be a predicate, and we find the first key that satisfies the predicate
    if(root == NULL || root->value == key)
        return root;    

    if(key < root->value)           //TODO: the predicate needs to be complemented by a comparator too!
        return search(root->left, key);

    return search(root->right, key);
}

//TODO: Include iterative version
Node* minimum(Node* root) {
    if(root->left != NULL)
        return minimum(root->left);
    return root;
}

//TODO: Include iterative version
Node* maximum(Node* root) {
    if(root->right != NULL)
        return maximum(root->right);
    return root;
}

int is_left_child(Node* node) {
    return node->parent != NULL && node == node->parent->left;
}

int is_right_child(Node* node) {
    return node->parent != NULL && node == node->parent->right;
}

Node* successor(Node* node) {
   if(node->right != NULL)
       return minimum(node->right);
   while(is_right_child(node))
        node = node->parent; 
   return node->parent;
}

Node* predecessor(Node* node) {
    if(node->left != NULL) 
        return maximum(node->left);
    while(is_left_child(node))
        node = node->parent;   
    return node->parent;
}

Node* create_node(int value, Node* parent) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->parent = parent;
    new_node->value = value;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void tree_insert(Tree* tree, int key) {
    if(tree->root == NULL)
        tree->root = create_node(key, NULL);
    else
        insert(key, tree->root, NULL);
}

void insert(int key, Node* root, Node* parent) {
    if(key < root->value) {
        if(root->left == NULL)
            root->left = create_node(key, root);
        else
            insert(key, root->left, root);
    }
    else {
        if(root->right == NULL)
            root->right = create_node(key, root);
        else
            insert(key, root->right, root);
    }
} 

void transplant(Tree* tree, Node* old, Node* new) {
    if(old->parent == NULL)
        tree->root = new;
    else if(old == old->parent->left)
        old->parent->left = new;
    else
        old->parent->right = new;
    if(new != NULL)
        old->parent = new->parent;  
}

void tree_delete(Tree* tree, Node* node) {
    if(node->left == NULL)
        transplant(tree, node, node->right);
    
    else if(node->right == NULL)
        transplant(tree, node, node->left);

    else {
        Node* successor_node = successor(node);
        if(successor_node != node->right) {
            transplant(tree, successor_node, successor_node->right);
            successor_node->right = node->right;
            node->right->parent = successor_node;
        }
        transplant(tree, node, successor_node);    
        successor_node->left = node->left;
        successor_node->left->parent = successor_node;
    }   
    free(node);
}
