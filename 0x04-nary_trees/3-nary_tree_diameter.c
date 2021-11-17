#include "nary_trees.h"

/**
 * c_max - max int
 * @a: a
 * @b: b
 * Return: max
 */
 int c_max(int a, int b)
 {
	if (a > b)
		return(a);
	return(b);
 }

/**
 * t_d - test diameter
 * @root: root
 * @d: diameter
 * Return: depth
 */
int t_d(nary_tree_t *root, int *d)
{
	int m_a = 0;
	int m_b = 0;
	int d_a = 0;
	int d_b = 0;
	nary_tree_t *children = NULL;

	if (root == NULL)
		return (-1);

	children = root->children;
	while (children)
	{
		d_b = t_d(children, d);
		d_a = c_max(d_a, d_b);
		if (d_b > m_a)
		{
			m_b = m_a;
			m_a = d_b;
		}
		else if (d_b > m_b)
		{
			m_b = d_b;
		}
		children = children->next;
	}
	*d = c_max((m_a + m_b + 1), *d);

	return (d_a + 1);
}

/**
 * nary_tree_diameter - daiameter
 * @root: root
 * Return: diameter
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	int d = 0;

	if (root == NULL)
		return (0);
	t_d((nary_tree_t *) root, &d);
	return (d);
}
