#include "rb_trees.h"

/**
 * rot_l - rotates left
 * @tree: Pointer to the root
 * @new: New node
 */
void rot_l(rb_tree_t **tree, rb_tree_t *new)
{
	rb_tree_t *child = new->right;

	if (!child)
		return;

	new->right = child->left;
	if (child->left)
		child->left->parent = new;
	child->left = new;
	child->parent = new->parent;
	if (!new->parent)
		*tree = child;
	else if (new->parent->left == new)
		new->parent->left = child;
	else
		new->parent->right = child;
	new->parent = child;
}

/**
 * rot_r - rotates right
 * @tree: Pointer to the root
 * @new: New node
 */
void rot_r(rb_tree_t **tree, rb_tree_t *new)
{
	rb_tree_t *child = new->left;

	if (!child)
		return;

	new->left = child->right;
	if (child->right)
		child->right->parent = new;
	child->right = new;
	child->parent = new->parent;
	if (!new->parent)
		*tree = child;
	else if (new->parent->left == new)
		new->parent->left = child;
	else
		new->parent->right = child;
	new->parent = child;
}

/**
 * right - repair tree with right uncle
 * @tree: Pointer to the root
 * @new: New node
 * Return: Pointer to the new node
 */
rb_tree_t *right(rb_tree_t **tree, rb_tree_t *new)
{
	rb_tree_t *uncle = new->parent->parent->right;

	if (uncle && uncle->color == RED)
	{
		uncle->color = BLACK;
		new->parent->color = BLACK;
		new->parent->parent->color = RED;
		new = new->parent->parent;
	}
	else
	{
		if (new == new->parent->right)
		{
			new = new->parent;
			rot_l(tree, new);
		}
		new->parent->color = BLACK;
		new->parent->parent->color = RED;
		rot_r(tree, new->parent->parent);
	}
	return (new);
}

/**
 * left - repair tree with left uncle
 * @tree: Pointer to the root
 * @new: New node
 * Return: Pointer to the new node
 */
rb_tree_t *left(rb_tree_t **tree, rb_tree_t *new)
{
	rb_tree_t *uncle = new->parent->parent->left;

	if (uncle && uncle->color == RED)
	{
		uncle->color = BLACK;
		new->parent->color = BLACK;
		new->parent->parent->color = RED;
		new = new->parent->parent;
	}
	else
	{
		if (new == new->parent->left)
		{
			new = new->parent;
			rot_r(tree, new);
		}
		new->parent->color = BLACK;
		new->parent->parent->color = RED;
		rot_l(tree, new->parent->parent);
	}
	return (new);
}

/**
 * check_tree - check if the tree need to by repair
 * @tree: Pointer to root
 * @new: new node
 * Return: Pointer to the new node
 */
rb_tree_t *check_tree(rb_tree_t **tree, rb_tree_t *new)
{
	while (new->parent && new->parent->color == RED)
	{
		if (new->parent->parent->left == new->parent)
			new = right(tree, new);
		else
			new = left(tree, new);
	}

	(*tree)->color = BLACK;
	return (new);
}


/**
 * rb_tree_insert - inserts node
 * @tree: Pointer to root
 * @value: Node value
 * Return: Pointer to the new node
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *prev, *curr, *new;

	prev = NULL;

	if (!tree)
		return (NULL);

	for (curr = *tree; curr;)
	{
		prev = curr;

		if (value < curr->n)
			curr = curr->left;
		else if (value > curr->n)
			curr = curr->right;
		else
			return (NULL);
	}

	new = rb_tree_node(prev, value, RED);
	if (!new)
		return (NULL);
	if (!prev)
	{
		new->color = BLACK;
		*tree = new;
		return (new);
	}
	if (value < prev->n)
		prev->left = new;
	else
		prev->right = new;
	check_tree(tree, new);
	return (new);
}
