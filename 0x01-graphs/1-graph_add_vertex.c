#include "graphs.h"
#include <stdlib.h>
#include <string.h>

/**
 * new_vertex - new vertex to graph
 * @str: string
 * @index: index
 * Return: pointer or null on error
 **/
static vertex_t *new_vertex(const char *str, size_t index)
{
	vertex_t *vertex_aux = NULL;

	vertex_aux = malloc(sizeof(vertex_t));

	if (!vertex_aux)
		return (NULL);

	vertex_aux->content = strdup(str);
	vertex_aux->nb_edges = 0;

	vertex_aux->edges = NULL;
	vertex_aux->next = NULL;

	vertex_aux->index = index;

	return (vertex_aux);
}

/**
 * graph_add_vertex - adds a vertex to an existing graph
 * @graph: pointer to the graph to add the vertex to
 * @str: string to store in the new vertex
 * Return: return a pointer to the created vertex, or NULL on failure
 **/
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t **new;

	if (!graph || !str)
		return (NULL);
	new = &graph->vertices;
	while (*new != NULL)
	{
		if (strcmp(str, (*new)->content) == 0)
			return (NULL);
		new = &(*new)->next;
	}

	*new = new_vertex(str, graph->nb_vertices);
	graph->nb_vertices += 1;
	return (*new);
}
