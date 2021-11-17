#include "nary_trees.h"

/**
* new_nary - new node
* Return: pointer
*/
nary_tree_t *new_nary(void)
{
	nary_tree_t *new_node = NULL;

	new_node = malloc(sizeof(nary_tree_t));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->content = NULL;
	new_node->parent = NULL;
	new_node->nb_children = 0;
	new_node->children = NULL;
	new_node->next = NULL;

	return (new_node);
}

/**
* nary_tree_insert - insert
* @parent: parent
* @str: str
* Return: pointer
*/
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node = NULL;

	new_node = new_nary();
	if (new_node == NULL)
		return (NULL);
	new_node->content = strdup(str);
	if (parent == NULL)
		return (new_node);
	new_node->parent = parent;
	new_node->next = parent->children;
	parent->children = new_node;
	parent->nb_children++;

	return (new_node);
}
