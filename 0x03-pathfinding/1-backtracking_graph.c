#include "pathfinding.h"

static char *track;
static queue_t *graph_path;

static vertex_t const *t_g;
static graph_t *res;

/**
 * aux_bt - DFS tracking
 * @vertex: vertex
 * Return: 1 on succes or 0
 */
int aux_bt(vertex_t const *vertex)
{
	char *p_a;
	edge_t *p_b;

	if (track[vertex->index])
		return (0);

	printf("Checking %s\n", vertex->content);
	track[vertex->index] = 1;
	p_a = strdup(vertex->content);

	if (!p_a)
		exit(1);

	queue_push_front(graph_path, p_a);

	if (vertex == t_g)
		return (1);

	for (p_b = vertex->edges; p_b; p_b = p_b->next)
		if (aux_bt(p_b->dest))
			return (1);

	free(dequeue(graph_path));
	return (0);
}

/**
 * backtracking_graph - backtrking for graph
 * @graph: pointer
 * @start: pointer
 * @target: pointer
 * Return: pointer
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	queue_t *r_p = NULL;

	if (!graph || !start || !target)
		return (NULL);

	setbuf(stdout, NULL);

	track = calloc(graph->nb_vertices, sizeof(*track));

	graph_path = queue_create();
	if (!track || !graph_path)
		exit(1);

	t_g = target;
	res = graph;

	if (aux_bt(start))
	{
		char *p_a;

		r_p = queue_create();

		if (!r_p)
			exit(1);
		for (p_a = dequeue(graph_path); p_a; p_a = dequeue(graph_path))
			if (!queue_push_front(r_p, p_a))
				exit(1);
	}
	queue_delete(graph_path);

	free(track);

	return (r_p);
}
