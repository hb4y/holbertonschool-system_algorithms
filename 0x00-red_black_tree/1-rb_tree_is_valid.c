#include "rb_trees.h"

/**
 * is_valid - Check if it is a valid RD tree
 * Every node has a color either red or black.
 * Root of tree is always black.
 * There are no two adjacent red nodes.
 * Every path from root to a NULL node has same number of black nodes.
 * @tree: root of tree
 * @_black: count black nodes
 * Return: 1 if valid 0 if not
 */
int is_valid(const rb_tree_t *tree, int *_black)
{
	int _right = 0;

	if (!tree)
	{
		*_black = 1;
		return (*_black);
	}

	if (tree->color != RED && tree->color != BLACK)
		return (0);

	if (tree->color == RED)
	{
		if (tree->left && tree->left->color == RED)
			return (0);
		if (tree->right && tree->right->color == RED)
			return (0);
	}

	if (!is_valid(tree->left, _black) || !is_valid(tree->right, &_right) ||
	    *_black != _right)
		return (0);

	if (tree->color == BLACK)
		*_black += 1;

	return (1);
}

/**
 * rb_tree_is_valid - valildates RB tree properties
 * @tree: pointer to root of tree to validate
 * Return: 1 if valid else 0
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int _black = 0;

	if (!tree || tree->color == RED)
		return (0);

	return (is_valid(tree, &_black));
}
