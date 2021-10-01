#include "pathfinding.h"

/**
 * track - backtrack
 * @map: map
 * @rows: row
 * @cols: col
 * @target: target
 * @x: coord
 * @y: coord
 * @route: path
 * Return: 1 on succes or 0
 */
int track(char **map, int rows, int cols, point_t const *target,
	int x, int y, queue_t *route)
{
	point_t *xy;

	if (x < 0 || x >= cols || y < 0 || y >= rows || map[y][x] != '0')
		return (0);

	map[y][x] = '1';
	xy = calloc(1, sizeof(*xy));

	if (!xy)
		exit(1);

	xy->x = x;
	xy->y = y;
	queue_push_front(route, xy);
	printf("Checking coordinates [%d, %d]\n", x, y);
	if (x == target->x && y == target->y)
		return (1);

	if (track(map, rows, cols, target, x + 1, y, route) ||
		track(map, rows, cols, target, x, y + 1, route) ||
		track(map, rows, cols, target, x - 1, y, route) ||
		track(map, rows, cols, target, x, y - 1, route))
		return (1);

	free(dequeue(route));


	return (0);
}

/**
 * backtracking_array - uses backtracking to find route
 * @map: map
 * @rows: row
 * @cols: col
 * @start: coord
 * @target: target
 * Return: queuie
 */
queue_t *backtracking_array(char **map, int rows, int cols,
	point_t const *start, point_t const *target)
{
	int i;
	char **p;
	queue_t *route = queue_create();
	queue_t *reverse_path = queue_create();
	point_t *xy;

	if (!route || !reverse_path)
		return (NULL);

	p = malloc(rows * sizeof(char *));

	if (!p)
		exit(1);

	for (i = 0; i < rows; i++)
	{
		p[i] = malloc(cols + 1);
		if (!p[i])
			exit(1);
		strcpy(p[i], map[i]);
	}

	if (track(p, rows, cols, target, start->x, start->y, route))
	{
		while ((xy = dequeue(route)))
			queue_push_front(reverse_path, xy);
		free(route);
	}
	else
	{
		free(route);
		free(reverse_path);
		reverse_path = NULL;
	}
	for (i = 0; i < rows; i++)
		free(p[i]);
free(p);

	return (reverse_path);
}
