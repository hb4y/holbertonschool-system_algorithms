#include "nary_trees.h"

/**
* recursive_path - find path
* @root: pointer
* @path: list
* Return: 1 OR 0
*/
int recursive_path(nary_tree_t const *root, char const * const *path)
{
	nary_tree_t const *n = NULL;

	if (*path == NULL)
		return (1);
	if (root == NULL)
		return (0);
	n = root;
	while (n)
	{
		if (strcmp(*path, n->content) == 0)
			if (recursive_path(n->children, path + 1) == 1)
				return (1);
		n = n->next;
	}
	return (0);
}

/**
* path_exists - search path
* @root: pointer
* @path: list
* Return: 1 OR 0
*/
int path_exists(nary_tree_t const *root, char const * const *path)
{
	if (root == NULL || path == NULL)
		return (0);
	return (recursive_path(root, path));
}
