#include "nary_trees.h"

/**
* nary_tree_delete - delete
* @tree: pointer
*/
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *n = NULL, *children = NULL;

	if (tree == NULL)
		return;
	children = tree->children;
	while (children)
	{
		nary_tree_delete(children->children);
		free(children->content);
		n = children->next;
		free(children);
		children = n;
	}

	free(tree->content);

	free(tree);

}
