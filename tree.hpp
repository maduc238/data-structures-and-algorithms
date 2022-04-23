#include <iostream>
#include "sort.hpp"

/* Binary Tree namespace:
You can use and change these function for Binary tree algorithm */
namespace BiTree{

/*****************************************************************************
 * To run these functions:
 * initial a new root node:
 *      Node* root = add_node(1);
 *      root->left = add_node(2);
 *      root->left->left = add_node(4);
 *      root->left->left->left = add_node(8);
 *      root->left->left->right = add_node(9);
 *      root->left->right = add_node(5);
 *      root->left->right->left = add_node(10);
 *      root->right = add_node(3);
 *      root->right->left = add_node(6);
 *      root->right->right = add_node(7);
 * Preorder, Inorder, Postorder traversal of binary tree:
 *      print_preorder(root); print_inorder(root); print_postorder(root);
 * convert from Binary Tree to Binary Search Tree:
 *      BT_to_BST(root);
 * 
 * New task to do: search, delete edge, ...
*****************************************************************************/

/* A binary tree node has data, pointer to left child and a pointer to right child */
class Node{
    public:
        int data;
        Node *left, *right;
        
        /* A helper function to count nodes in a Binary Tree */
        int count_nodes(){
            if (this == NULL) return 0;
            return this->left->count_nodes() + this->right->count_nodes() + 1;
        }
        
        /* This function help to change a node's name */
        void change_name(int data){
            this->data = data;
        }
};

/* Utility function to create a new tree node
Example: root->left->right = add_node(4) */
Node* add_node(int data){
	Node* temp = new Node();
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

/* Given a binary tree, print its nodes according to the "bottom-up" postorder traversal. */
void print_postorder(Node* node){
	if (node == NULL)
		return;
	print_postorder(node->left);
	print_postorder(node->right);
	cout << node->data << " ";
}

/* Given a binary tree, print its nodes in inorder*/
void print_inorder(Node* node){ 
	if (node == NULL)
		return;
	print_inorder(node->left);
	cout << node->data << " ";
	print_inorder(node->right);
}

/* A helper function that stores inorder traversal of a tree rooted with node */
void store_inorder(Node* node, int inorder[], int* itr){
    if (node == NULL)
        return;
    store_inorder(node->left, inorder, itr);
    // Copy the root's data
    inorder[*itr] = node->data;
	// Increase index for next entry
    (*itr)++;
    store_inorder(node->right, inorder, itr);
}

/* Given a binary tree, print its nodes in preorder */
void print_preorder(Node* node){
	if (node == NULL)
		return;
	cout << node->data << " ";
	print_preorder(node->left);
	print_preorder(node->right);
}

/* A helper function that copies contents of arr[] to Binary Tree.
This function basically does Inorder traversal of Binary Tree and one by one copy arr[] elements to Binary Tree nodes */
void array_to_BST(int* arr, Node* root, int* itr){
    if (root == NULL)
        return;
    array_to_BST(arr, root->left, itr);
    root->data = arr[*itr];
    (*itr)++;
    array_to_BST(arr, root->right, itr);
}

/* This function converts a given Binary Tree to Binary Search Tree.
It's maybe a useful function that help to find a node in Binary Tree, etc... */
void BT_to_BST(Node* root){
    if (root == NULL)
        return;
    int n = root->count_nodes();
    int* arr = new int[n];
	// Variable i only serves to increment the value for the following functions
    int i = 0;
    store_inorder(root, arr, &i);
    // Sort the array using library function: heap sort
	heap_sort(arr, n);
    // Copy array elements back to Binary Tree
    i = 0;
    array_to_BST(arr, root, &i);
    delete[] arr;
}

}