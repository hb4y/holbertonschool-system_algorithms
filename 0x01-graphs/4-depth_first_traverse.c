#include "graphs.h"
#define GRAPH_AUX const graph_t *graph
#define FUNC void (*func)(const vertex_t *aux_v, size_t depth)

/**
 * depth - get the depth
 * @aux_v: vertex
 * @func: func to take on vertex
 * @track: keeps track
 * @n_depth: current depth
 * Return: depth
 **/
size_t depth(const vertex_t *aux_v, func_t func, char *track, size_t n_depth)
{
	edge_t *c_edge;
	size_t aux_depth, max_d = 0;

	if (track[aux_v->index])
		return (n_depth - 1);

	func(aux_v, n_depth);

	track[aux_v->index] = 1;
	c_edge = aux_v->edges;

	while (c_edge)
	{
		aux_depth = depth(c_edge->dest, func, track, n_depth + 1);

		if (aux_depth > max_d)
			max_d = aux_depth;

		c_edge = c_edge->next;
	}

	return (max_d);
}

/**
 * depth_first_traverse - depth-first algorithm.
 * @GRAPH_AUX: pointer
 * @FUNC: pointer
 * Return: depth
 **/
size_t depth_first_traverse(GRAPH_AUX, FUNC)
{
	char *track;
	size_t max_depth = 0;

	if (!graph)
		return (0);

	if (graph->nb_vertices)
	{
		track = calloc(graph->nb_vertices, sizeof(char));
		max_depth = depth(graph->vertices, func, track, max_depth);

		free(track);
	}

	return (max_depth);
}
