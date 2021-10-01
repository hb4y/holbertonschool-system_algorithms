#include "pathfinding.h"

static int *l;
static int *fs;

static vertex_t **orgn;
static vertex_t **points;

#define DUP(x) ((str = strdup(x)) ? str : (exit(1), NULL))

#define H(a) ((int)sqrt(pow((a->x - target->x), 2) + \
	pow((a->y - target->y), 2)))


#define PLACE_MEM \
	do { \
		l = calloc(graph->nb_vertices, sizeof(*l)); \
		fs = calloc(graph->nb_vertices, sizeof(*fs)); \
		orgn = calloc(graph->nb_vertices, sizeof(*orgn)); \
		points = calloc(graph->nb_vertices, sizeof(*points)); \
	} while (0)

/**
 * a_star_graph - uses A* algo to find optimal path
 * @graph: pointer
 * @start: pointer
 * @target: pointeR
 * Return: path
 */
queue_t *a_star_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	ssize_t i, d, j = -1;
	vertex_t *v;
	edge_t *e;
	queue_t *m_P = queue_create();
	char *str;

	if (!graph || !start || !target || !m_P)
		return (NULL);
	PLACE_MEM;
	if (!l || !fs || !orgn || !points || !m_P)
		return (NULL);
	for (v = graph->vertices; v; v = v->next)
		points[v->index] = v, l[v->index] = fs[v->index] = INT_MAX;
	l[start->index] = 0, orgn[start->index] = NULL;
	fs[start->index] = H(start);
	while (j != (ssize_t)target->index)
	{
		for (d = INT_MAX, j = -1, i = 0; i < (ssize_t)graph->nb_vertices; i++)
			if (fs[i] >= 0 && fs[i] < d)
				d = fs[i], j = i;
		if (j == -1)
			break;
		printf("Checking %s, distance to %s is %d\n",
			points[j]->content, target->content, H(points[j]));
		for (e = points[j]->edges; e; e = e->next)
			if (l[e->dest->index] >= 0 &&
				l[j] + e->weight < l[e->dest->index])
				l[e->dest->index] = l[j] + e->weight,
				orgn[e->dest->index] = points[j],
				fs[e->dest->index] = l[e->dest->index] + H(e->dest);
		fs[j] = -1;
	}
	if (j != -1)
		for (queue_push_front(m_P, DUP(points[j]->content));
			j != (ssize_t)start->index; j = orgn[j]->index)
			queue_push_front(m_P, DUP(orgn[j]->content));
	else
		m_P = (free(m_P), NULL);
free(l), free(fs), free(orgn), free(points);
return (m_P);
}
