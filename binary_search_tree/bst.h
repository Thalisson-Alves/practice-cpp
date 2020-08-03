#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

namespace th
{	
	typedef struct TreeNode {
		int data;
		struct TreeNode *left;
		struct TreeNode *right;
	} TreeNode;
	
	TreeNode *bst_newNode(int value)
	{
		TreeNode *node = new TreeNode;
		
		node->data = value;
		node->left = NULL;
		node->right = NULL;
		
		return node;
	}
	
	void bst_insert(TreeNode **root, int value)
	{
		TreeNode *node = *root;
		if (!node)
			*root = bst_newNode(value);
		else if (node->data < value)
			bst_insert(&node->right, value);
		else if (node->data > value)
			bst_insert(&node->left, value);
		else
			return;
	}
	
	void bst_print(TreeNode *root)
	{
		if (!root)
			return;
		bst_print(root->left);
		std::cout << root->data << '\n';
		bst_print(root->right);
	}
	
	bool bst_empty(TreeNode *root)
	{
		return !root;
	}
	
	int bst_size(TreeNode *root)
	{
		return root ? bst_size(root->left) + bst_size(root->right) + 1 : 0;
	}
	
	void bst_destroy(TreeNode *root)
	{
		if (!root)
			return ;
		bst_destroy(root->left);
		bst_destroy(root->right);
		delete root;
	}
	
	void bst_clear(TreeNode **root)
	{
		bst_destroy(*root);
		*root = NULL;
	}
	
	bool bst_exists(TreeNode *root, int value)
	{
		if (!root)
			return false;
		if (root->data < value)
			return bst_exists(root->right, value);
		if (root->data > value)
			return bst_exists(root->left, value);
		return true;
	}
	
	int bst_height(TreeNode *root)
	{
		if (!root)
			return 0;
		int leftHeight = bst_height(root->left);
		int rightHeight = bst_height(root->right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}
	
	int bst_min(TreeNode *root)
	{
		if (!root)
			return -1;
		while (root->left)
			root = root->left;
		
		return root->data;
	}
	
	int bst_max(TreeNode *root)
	{
		if (!root)
			return -1;
		while (root->right)
			root = root->right;
		
		return root->data;
	}
	
	void bst_deleteValue(TreeNode **root, int value)
	{
		TreeNode *current = *root;
		if (!current)
			return ;
		else if (current->data > value)
			bst_deleteValue(&current->left, value);
		else if (current->data < value)
			bst_deleteValue(&current->right, value);
		// Found
		else {
			int rightHeight = bst_height(current->right);
			int leftHeight = bst_height(current->left);
			if (leftHeight < rightHeight) {
				// right side becomes parent of left side
				*root = current->right;
				// left side becomes the left most child
				TreeNode *tmp = *root;
				while (tmp->left) {
					tmp = tmp->left;
				}
				tmp->left = current->left;
			}
			else if (leftHeight && rightHeight <= leftHeight) {
				// left side becomes parent
				*root = current->left;
				// right side becomes child
				TreeNode *tmp = *root;
				while (tmp->right) {
					tmp = tmp->right;
				}
				tmp->right = current->right;
			}
			// node to be deletede is a leaf
			else {
				*root = NULL;
			}
			delete current;
		}
	}
	
	int bst_nextHighest(TreeNode *root, int value)
	{
		if (!root) {
			return -1;
		}
		else if (root->data <= value) {
			return bst_nextHighest(root->right, value);
		}
		else {
			while (root->left) {
				root = root->left;
			}
			return root->data;
		}
	}
	
	int bst_nextSmaller(TreeNode *root, int value)
	{
		if (!root) {
			return -1;
		}
		else if (root->data >= value) {
			return bst_nextSmaller(root->left, value);
		}
		else {
			while (root->right) {
				root = root->right;
			}
			return root->data;
		}
	}
}

#endif