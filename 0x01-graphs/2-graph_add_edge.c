#include "graphs.h"
#include <stdlib.h>
#include <string.h>


/**
 * new_vertex - new vertex
 * @src: source
 * @dest: destinaty
 * Return: 1 on success 0 on faiiilllll
 **/
static int new_vertex(vertex_t *src, vertex_t *dest)
{
	edge_t *new, **ma_p;

	if (!dest || !src)
		return (0);

	ma_p = &src->edges;
	while (*ma_p)
	{
		if ((*ma_p)->dest == dest)
			return (0);
		 ma_p = &(*ma_p)->next;
	}

	new = malloc(sizeof(edge_t));
	if (!new)
		return (0);

	new->dest = dest;
	new->next = NULL;

	*ma_p = new;
	src->nb_edges += 1;

	return (1);
}

/**
 * get - gets the vertex
 * @graph: pointer
 * @content: string
 * Return: pointer or null on failure
 **/
static vertex_t *get(graph_t *graph, const char *content)
{
	vertex_t *aux;

	aux = graph->vertices;

	while (aux)
	{
		if (!strcmp(aux->content, content))
			return (aux);

		aux = aux->next;
	}

	return (aux);
}

/**
 * graph_add_edge - adds an edge between two vertices to an existing graph
 * @graph:  pointer
 * @src: string
 * @dest: string
 * @type: type
 * Return: return 1 on success, or 0 on failure.
 **/
int graph_add_edge(
	graph_t *graph, const char *src, const char *dest, edge_type_t type)
{
	vertex_t *source, *destiny;

	if (!graph || !src || !dest || type > BIDIRECTIONAL)
		return (0);

	source = get(graph, src);
	if (!source)
		return (0);

	destiny = get(graph, dest);

	if (!destiny)
		return (0);

	if (type == UNIDIRECTIONAL)
		return (new_vertex(source, destiny));

	new_vertex(source, destiny);

	new_vertex(destiny, source);

	return (1);
}
