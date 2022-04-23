#include "tree.hpp"

int main()
{
	BiTree::Node* root = BiTree::add_node(1);
	root->left = BiTree::add_node(2);
	root->left->left = BiTree::add_node(4);
	root->left->left->left = BiTree::add_node(8);
	root->left->left->right = BiTree::add_node(9);
    root->left->right = BiTree::add_node(5);
    root->left->right->left = BiTree::add_node(10);
	root->right = BiTree::add_node(3);
    root->right->left = BiTree::add_node(6);
    root->right->right = BiTree::add_node(7);

	cout << "\nPreorder traversal of binary tree is \n";
	BiTree::print_preorder(root);
	cout << "\nInorder traversal of binary tree is \n";
	BiTree::print_inorder(root);
	cout << "\nPostorder traversal of binary tree is \n";
	BiTree::print_postorder(root);

	// Binary Tree to Binary Search Tree Conversion
	BiTree::BT_to_BST(root);

	cout << "\nInorder traversal of binary search tree is \n";
	BiTree::print_inorder(root);

	return 0;
}