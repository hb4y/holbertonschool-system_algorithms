#include "nary_trees.h"

/**
 * dep - max depth
 * @root: root
 * @n: depth
 * @action: func pointer
 * Return: depth
 */
size_t dep(nary_tree_t const *root, size_t n,
		void (*action)(nary_tree_t const *node, size_t depth))
{
	nary_tree_t *children = NULL;
	size_t m = 0;
	size_t min = 0;

	action(root, n);
	children = root->children;
	m = n;

	while (children)
	{
		min = dep(children, n + 1, action);
		if (min > m)
			m = min;
		children = children->next;
	}
	return (m);
}

/**
 * nary_tree_traverse - traverse
 * @root: root
 * @action: func pinter
 * Return: depth
 */
size_t nary_tree_traverse(nary_tree_t const *root,
		void (*action)(nary_tree_t const *node, size_t depth))
{
	if (root == NULL)
		return (0);
	return (dep(root, 0, action));
}
