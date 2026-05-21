/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:42:46 by vdiez-cu          #+#    #+#             */
/*   Updated: 2026/05/21 20:11:52 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int loadElements(FILE* file, t_elements* elements)
{
	int ret = fscanf(file, "%d %c %c %c", &(elements->n_lines), &(elements->empty), &(elements->obstacle), &(elements->full));

	if((ret != 4))
		return(-1);

	if(elements->n_lines <= 0)
		return(-1);
	if(elements->empty == elements->obstacle || elements->empty == elements->full || elements->obstacle == elements->full)
		return(-1);
	if(elements->empty < 32 || elements->empty > 126)
		return(-1);
	if(elements->obstacle < 32 || elements->obstacle > 126)
		return(-1);
	if(elements->full < 32 || elements->full > 126)
		return(-1);

	return(0);
}

char* ft_substr(char* arr, int start, int len)
{
	char* str = (char*)malloc(len + 1);
	if (!str)
		return (NULL);
	int i = 0;
	int j = 0;
	while (arr[i])
	{
		if ((i >= start) && (j < len))
		{
			str[j] = arr[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return(str);
}

void free_map(char** arr)
{
	int	i = 0;
	if(arr)
	{
		while (arr[i] != NULL)
		{
			if(arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void print(char** arr)
{
	int i = 0;
	while(arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	printf("\n");
}

int element_control(char** map, char c1, char c2)
{
	int i = 0;
	while(map[i])
	{
		int j = 0;
		while(map[i][j] != '\0')
		{
			if((map[i][j] != c1) && (map[i][j] != c2))
				return(-1);
			j++;
		}
		i++;
	}
	return(0);
}

int loadMap(FILE* file, t_map* map, t_elements* elements)
{
	int i;
	int read;
	char* line = NULL;
	size_t len = 0;

	map->height = elements->n_lines;
	map->grid = (char**)malloc((map->height + 1) * (sizeof(char *)));
	map->grid[map->height] = NULL;

	if (getline(&line, &len, file) == -1)
	{
		free_map(map->grid);
		return (-1);
	}
	i = 0;
	while (i < map->height)
	{
		read = getline(&line, &len, file);
		if (read == -1)
		{
			free(line);
			free_map(map->grid);
			return (-1);
		}
		if (line[read - 1] == '\n')
			read--;
		else
		{
			free(line);
			free_map(map->grid);
			return (-1);
		}
		map->grid[i] = ft_substr(line, 0, read);
		if (!(map->grid[i]))
		{
			free(line);
			free_map(map->grid);
			return (-1);
		}
		if (i == 0)
			map->width = read;
		else
		{
			if (map->width != read)
			{
				free(line);
				free_map(map->grid);
				return (-1);
			}
		}
		i++;
	}
	if (element_control(map->grid, elements->empty, elements->obstacle) == -1)
	{
		free(line);
		free_map(map->grid);
		return (-1);
	}
	free(line);
	return (0);
}

int find_min(int n1, int n2, int n3)
{
	int min = n1;

	if(n2 < min)
		min = n2;
	if(n3 < min)
		min = n3;
	return(min);
}

void find_big_square(t_map* map, t_square* square, t_elements* elements)
{
	int matrix[map->height][map->width];
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == elements->obstacle)
				matrix[i][j] = 0;
			else if (i == 0 || j == 0)
				matrix[i][j] = 1;
			else
			{
				int min = find_min(matrix[i - 1][j], matrix[i - 1][j - 1], matrix[i][j - 1]);
				matrix[i][j] = min + 1;
			}

			if (matrix[i][j] > square->size)
			{
				square->size = matrix[i][j];
				square->i = i - matrix[i][j] + 1;
				square->j = j - matrix[i][j] + 1;
			}
			j++;
		}
		i++;
	}
}

void print_filled_square(t_map* map, t_square* square, t_elements* elements)
{
	int i;
	int j;

	i = square->i;
	while (i < square->i + square->size)
	{
		j = square->j;
		while (j < square->j + square->size)
		{
			if ((i < map->height) && (j < map->width))
				map->grid[i][j] = elements->full;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		fprintf(stdout, "%s\n", map->grid[i]);
		i++;
	}
}

int execute_bsq(FILE* file)
{
	t_elements elements;
	if(loadElements(file, &elements) == -1)
		return(-1);

	t_map map;
	if(loadMap(file, &map, &elements) == -1)
		return(-1);

	t_square square;
	square.size = 0;
	square.i = 0;
	square.j = 0;
	find_big_square(&map, &square, &elements);
	print_filled_square(&map, &square, &elements);
	free_map(map.grid);
	return(0);
}

int convert_file_pointer(char* name)
{
	FILE* file = fopen(name, "r");
	if(!file)
		return(-1);
	int ret = 0;
	ret = execute_bsq(file);
	fclose(file);
	return(ret);
}

int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		if(execute_bsq(stdin) == -1)
			fprintf(stderr, "map error\n");
	}
	else if(argc == 2)
	{
		if(convert_file_pointer(argv[1]) == -1)
			fprintf(stderr, "map error\n");
	}
	else
	{
		int i = 1;
		while(i < argc)
		{
			if(convert_file_pointer(argv[i]) == -1)
				fprintf(stderr, "map error\n");
			i++;
			if(i < argc - 1)
				fprintf(stdout, "\n");

		}
	}
	return(0);
}