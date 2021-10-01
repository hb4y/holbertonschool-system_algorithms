#include "pathfinding.h"

static int *wei;

static vertex_t **org;

#define DUP(mystr) ((s = strdup(mystr)) ? s : (exit(1), NULL))

static vertex_t **corn;



/**
 * dijkstra_graph - Dijkstra
 * @graph: pointer
 * @start: pointer
 * @target: pointer
 * Return: path o null
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	ssize_t o, f, k = -1;
	vertex_t *ver;
	edge_t *ed;
	queue_t *res = queue_create();
	char *s;

	if (!graph || !start || !target || !res)
		return (NULL);

	wei = calloc(graph->nb_vertices, sizeof(*wei));
	org = calloc(graph->nb_vertices, sizeof(*org));

	corn = calloc(graph->nb_vertices, sizeof(*corn));

	if (!wei || !org || !corn || !res)
		return (NULL);

	for (ver = graph->vertices; ver; ver = ver->next)
		corn[ver->index] = ver, wei[ver->index] = INT_MAX;

	wei[start->index] = 0, org[start->index] = NULL;
	while (k != (ssize_t)target->index)
	{
		for (f = INT_MAX, k = -1, o = 0; o < (ssize_t)graph->nb_vertices; o++)
			if (wei[o] >= 0 && wei[o] < f)
				f = wei[o], k = o;
		if (k == -1)
			break;

		printf("Checking %s, distance org %s is %f\n",
			corn[k]->content, start->content, wei[k]);

		for (ed = corn[k]->edges; ed; ed = ed->next)
			if (wei[ed->dest->index] >= 0 &&
				wei[k] + ed->weight < wei[ed->dest->index])
				wei[ed->dest->index] = wei[k] + ed->weight,
					org[ed->dest->index] = corn[k];
		wei[k] = -1;
	}

	if (k != -1)
		for (queue_push_front(res, DUP(corn[k]->content));
			k != (ssize_t)start->index; k = org[k]->index)
			queue_push_front(res, DUP(org[k]->content));
	else
		res = (free(res), NULL);

	free(wei), free(org), free(corn);

	return (res);

}
