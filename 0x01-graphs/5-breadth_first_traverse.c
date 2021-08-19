#include "graphs.h"
#define GRAPH const graph_t *graph
#define FUNC void (*func)(const vertex_t *v, size_t depth)


/**
 * breadth_first_traverse - using the breadth-first algorithm.
 * @GRAPH: pointer
 * @FUNC: pointer to function
 * Return: depth or 0
 **/
size_t breadth_first_traverse(GRAPH, FUNC)
{
	size_t depth, size_1, size_2;
	vertex_t **vertex_aux;
	char *track;
	edge_t *aux;
	int i, j;

	if (!graph || !func || graph->nb_vertices == 0)
		return (0);

	track = calloc(graph->nb_vertices, sizeof(char));
	vertex_aux = calloc(graph->nb_vertices + 1, sizeof(vertex_t *));

	vertex_aux[0] = graph->vertices;
	track[0] = 1, depth = 0, j = 1, size_1 = 1, size_2 = 0;

	for (i = 0; vertex_aux[i]; i++)
	{
		func(vertex_aux[i], depth);

		for (aux = vertex_aux[i]->edges; aux; aux = aux->next)
		{
			if (track[aux->dest->index] == 0)
			{
				vertex_aux[j++] = aux->dest, track[aux->dest->index] = 1;
				size_2 += 1;
			}
		}

		if (--size_1 == 0)
		{
			depth++, size_1 = size_2;
			size_2 = 0;
		}
	}
	free(track), free(vertex_aux);

	return (depth - 1);
}
