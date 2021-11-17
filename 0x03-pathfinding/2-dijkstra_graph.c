#include "pathfinding.h"

static int *l;

static vertex_t **orgn;
static vertex_t **points;


#define DUP(x) ((str = strdup(x)) ? str : (exit(1), NULL))

/**
 * dijkstra_graph - dijkstra
 * @graph: pointer
 * @start: pointer
 * @target: pointer
 * Return: path
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	char *str;
	ssize_t i, d, j;
	vertex_t *v;
	edge_t *e;
	queue_t *route = queue_create();

	if (!graph || !start || !target || !route)
		return (NULL);
	l = calloc(graph->nb_vertices, sizeof(*l));
	orgn = calloc(graph->nb_vertices, sizeof(*orgn));
	points = calloc(graph->nb_vertices, sizeof(*points));
	j = -1;
	if (!l || !orgn || !points || !route)
		return (NULL);
	for (v = graph->vertices; v; v = v->next)
		points[v->index] = v, l[v->index] = INT_MAX;
	l[start->index] = 0, orgn[start->index] = NULL;
	while (j != (ssize_t)target->index)
	{
		for (d = INT_MAX, j = -1, i = 0; i < (ssize_t)graph->nb_vertices; i++)
			if (l[i] >= 0 && l[i] < d)
				d = l[i], j = i;
		if (j == -1)
			break;
		printf("Checking %s, distance from %s is %d\n",
			points[j]->content, start->content, l[j]);
		for (e = points[j]->edges; e; e = e->next)
			if (l[e->dest->index] >= 0 && l[j] + e->weight < l[e->dest->index])
				l[e->dest->index] = l[j] + e->weight, orgn[e->dest->index] = points[j];
		l[j] = -1;
	}
	if (j != -1)
		for (queue_push_front(route, DUP(points[j]->content));
			j != (ssize_t)start->index; j = orgn[j]->index)
			queue_push_front(route, DUP(orgn[j]->content));
	else
		route = (free(route), NULL);

	free(l), free(orgn), free(points);
	return (route);
}
