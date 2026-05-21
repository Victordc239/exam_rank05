/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:21:24 by ksudyn            #+#    #+#             */
/*   Updated: 2026/04/23 10:02:53 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void printboard(char *board, int ancho, int alto)
{
	int y;
	int x;

	y = 0;
	while (y < alto)
	{
		x = 0;
		while (x < ancho)
		{
			if (board[y * ancho + x])
				putchar('0');
			else
				putchar(' ');
			x++;
		}
		putchar('\n');
		y++;
	}
}

int count_vecino(char *board, int ancho, int alto, int x, int y)
{
	int count;
	int dy;
	int dx;
	int vecino_x;
	int vecino_y;

	count = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (dy == 0 && dx == 0)
			{
				dx++;
				continue;
			}
			vecino_x = x + dx;
			vecino_y = y + dy;
			if (vecino_x >= 0 && vecino_x < ancho && vecino_y >= 0 && vecino_y < alto)
				count += board[vecino_y * ancho + vecino_x];
			dx++;
		}
		dy++;
	}
	return count;
}

void step(char *board, char *next_board, int ancho, int alto)
{
	int y;
	int x;
	int n;

	y = 0;
	while (y < alto)
	{
		x = 0;
		while (x < ancho)
		{
			n = count_vecino(board, ancho, alto, x, y);
			if (board[y * ancho + x])
			{
				if (n == 2 || n == 3)
					next_board[y * ancho + x] = 1;
				else
					next_board[y * ancho + x] = 0;
			}
			else
			{
				if (n == 3)
					next_board[y * ancho + x] = 1;
				else
					next_board[y * ancho + x] = 0;
			}
			x++;
		}
		y++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 4)
		return 1;

	int ancho = atoi(argv[1]);
	int alto = atoi(argv[2]);
	int iter = atoi(argv[3]);
	int x = 0;
	int y = 0;
	int pencil = 0;
	int i = 0;
	char *tmp;
	char *board;
	char *next_board;	
	char c;

	board = calloc(ancho * alto, 1);
	next_board = calloc(ancho * alto, 1);
	if (!board || !next_board)
		return 1;

	while (read(0, &c, 1) > 0)
	{
		if (c == 'x')
			pencil = !pencil;
		if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < ancho - 1)
			x++;
		else if (c == 'w' && y > 0)
			y--;
		else if (c == 's' && y < alto - 1)
			y++;
		if (pencil)
			board[y * ancho + x] = 1;
	}

	i = 0;
	while (i < iter)
	{
		step(board, next_board, ancho, alto);
		tmp = board;
		board = next_board;
		next_board = tmp;
		i++;
	}
	printboard(board, ancho, alto);
	free(board);
	free(next_board);
	return 0;
}
