#include "graphs.h"

/**
 * graph_delete - delete and free
 * @graph: pointer
 */
void graph_delete(graph_t *graph)
{
	vertex_t *curr_v, *aux_v;
	edge_t *curr_e, *aux_e;

	if (!graph)
		return;

	curr_v = graph->vertices;

	while (curr_v)
	{
		free(curr_v->content);
		curr_e = curr_v->edges;

		while (curr_e)
		{
			aux_e = curr_e;
			curr_e = curr_e->next;
			free(aux_e);
		}

		aux_v = curr_v;
		curr_v = curr_v->next;

		free(aux_v);
	}

	free(graph);
}
