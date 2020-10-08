#include "rb_trees.h"

/**
 * array_to_rb_tree - array to RB tree
 * @array: array of int
 * @size: size of the array
 * Return: Pointer to head of the tree
 */

rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	int i;
	rb_tree_t *tree;

	tree = NULL;

	for (i = 0; i < (int) size; i++)
		rb_tree_insert(&tree, array[i]);

	return (tree);
}
