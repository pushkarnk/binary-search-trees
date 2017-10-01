#include<stdio.h>
#include<stdlib.h>
#include "binary_search_tree.h"

#define START(test) printf("\n"#test" started\n")
#define PASS(test)  printf(#test" passed\n")
#define FAIL(test)  printf(#test" failed\n")

void test_insertion(Tree* t, int array[], int count)
{
    START(test_insertion);
    for(int i = 0; i<count; i++)
        tree_insert(t, array[i]);
    tree_inorder_walk(t);
    PASS(test_insertion);
}

void test_search(Tree* t, int keys[], int results[], int count)
{
    START(test_search);
    for(int i = 0; i<count; i++)
    {
        if ((tree_search(t, keys[i]) != NULL) != results[i])
        {
             FAIL(test_search);
             exit(1);
        }
    }
    PASS(test_search);
}

void test_max_min(Tree* t, int expected_max, int expected_min)
{
    START(test_max_min);
    Node* max = tree_maximum(t);
    Node* min = tree_minimum(t);
   
    if(max && max->value == expected_max && min && min->value == expected_min)
        PASS(test_max_min);
    else
        FAIL(test_max_min);
}

void test_deletion(Tree* t, int remove_keys[], int count)
{
    START(test_deletion); 
    for(int i=0; i<count; i++)
    {
        Node* found = tree_search(t, remove_keys[i]);
        if(found)
            tree_delete(t, found);
    }
    tree_inorder_walk(t);
    PASS(test_deletion);
}
    
int main(int argc, char ** argv)
{
    Tree* t = (Tree*)malloc(sizeof(Tree));
    t->root = NULL;

    test_insertion(t,(int[]){1900, 8276, 89, 18, 28, 3761, 9191, 718, 309, -19}, 10);
    test_search(t, (int[]){18, 718, 301}, (int[]){1,1,0}, 3);
    test_max_min(t, 9191, -19); 
    test_deletion(t, (int []){309, -19, 9191, 3761, 9999}, 5);
    test_max_min(t, 8276, 18);

    return 0;
}
