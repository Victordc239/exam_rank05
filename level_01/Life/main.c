/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 23:41:40 by fbetul            #+#    #+#             */
/*   Updated: 2026/02/24 16:43:59 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void free_board(t_game* game)
{
	if(game->board)
	{
		for(int i = 0; i < game->alto; i++)
		{
			if(game->board[i])
				free(game->board[i]);
		}
		free(game->board);
	}
}

void print(t_game* game)
{
	for(int i = 0; i < game->alto; i++)
	{
		for(int j = 0; j < game->ancho; j++)
		{
			putchar(game->board[i][j]);
		}
		putchar('\n');
	}
}

int init(t_game* game, char* argv[])
{
	game->ancho = atoi(argv[1]);
	game->alto = atoi(argv[2]);
	game->iterations = atoi(argv[3]);
	game->i = 0;
	game->j = 0;
	game->draw = 0;
	game->vivo = '0';
	game->dead = ' ';
	game->board = (char**)malloc((game->alto) * sizeof(char *));
	if(!(game->board))
		return(-1);
	for(int i = 0; i < game->alto; i++)
	{
		game->board[i] = (char *)malloc((game->ancho) * sizeof(char));
		if(!(game->board[i]))
		{
			free_board(game);
			return(-1);
		}
		for(int j = 0; j < game->ancho; j++)
		{
			game->board[i][j] = ' ';
		}
	}
	return(0);
}

void fill(t_game* game)
{
	char buffer;
	int flag;

	while(read(0, &buffer, 1) == 1)
	{
		flag = 0;
		switch (buffer)
		{
			case 'w':
				if(game->i > 0)
					game->i--;
				break;
			case 's':
				if(game->i < (game->alto - 1))
					game->i++;
				break;
			case 'a':
				if(game->j > 0)
					game->j--;
				break;
			case 'd':
				if(game->j < (game->ancho - 1))
					game->j++;
				break;
			case 'x':
				game->draw = !(game->draw);
				break;
			default:
				flag = 1;
				break;
		}
		if(game->draw && (flag == 0))
		{
			if((game->i >= 0 )&& (game->i < game->alto) && (game->j >= 0) && (game->j < game->ancho))
				game->board[game->i][game->j] = game->vivo;
		}
	}
}

int count_vecinos(t_game* game, int i, int j)
{
	int count = 0;
	for(int di = -1; di < 2; di++)
	{
		for(int dj = -1; dj < 2; dj++)
		{
			if((di == 0) && (dj == 0))
				continue;

			int ni = i + di;
			int nj = j + dj;
			if((ni >= 0) && (nj >=0) && (ni < game->alto) && (nj < game->ancho))
			{
				if(game->board[ni][nj] == game->vivo)
					count++;
			}
		}
	}
	return(count);
}

int play(t_game* game)
{
	char** temp = (char**)malloc((game->alto) * sizeof(char *));
	if(!temp)
		return(-1);
	for(int i = 0; i < game->alto; i++)
	{
		temp[i] = (char *)malloc((game->ancho) * sizeof(char));
		if(!(temp[i]))
			return(-1);
	}
	for(int i = 0; i < game->alto; i++)
	{
		for(int j = 0; j < game->ancho; j++)
		{
			int vecinos = count_vecinos(game, i, j);
			if(game->board[i][j] == game->vivo)
			{
				if(vecinos == 2 || vecinos == 3)
					temp[i][j] = game->vivo;
				else
					temp[i][j] = game->dead;
			}
			else
			{
				if(vecinos == 3)
					temp[i][j] = game->vivo;
				else
					temp[i][j] = game->dead;
			}
		}
	}
	free_board(game);
	game->board = temp;
	return(0);
}

int main(int argc, char* argv[])
{
	if(argc != 4)
		return (1);

	t_game game;

	if(init(&game, argv) == -1)
		return(1);
	fill(&game);
	for(int i = 0; i < game.iterations; i++)
	{
		if(play(&game) == -1)
		{
			free_board(&game);
			return(1);
		}
	}
	print(&game);
	free_board(&game);
	return (0);
}
